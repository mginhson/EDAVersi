/**
 * @brief Implements the Reversi game AI
 * @author Marc S. Ressl
 * @modifiers Sosa Mateo, Ginhson Matteo
 * @copyright Copyright (c) 2023-2024
 */

#include <cstdlib>
#include <limits>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "ai.h"
#include "controller.h"
#include "model.h"


#define MAX_NODE_COUNT 1000000
#define MAX_DEPTH 8
#define MINUS_INFINITY_FLOAT ( (float)-1 * std::numeric_limits<float>::infinity()) 
#define PLUS_INFINITY_FLOAT ( (float)std::numeric_limits<float>::infinity())

 // Values to game piecies
const int CORNER_VALUE = 125;
const int EDGE_VALUE = 10;
const int PIECE_VALUE = 1;
//Global node count
unsigned int nodeCount = 0;


bool isCorner(int row, int col);
bool isEdge(int row, int col);


Square getBestMove(GameModel& model);
double evaluateGameState(GameModel& state);
double evaluateGameStateWithTable(GameModel& state);

/**
 * This is the kind of data the minMax functions will return,
 * it contains both the best movement it can be made from the
 * give position, plus it's evaluation value.
 */
typedef struct {
	float value;
	Square movement;
}Pruning_t;


static Pruning_t minMaxTraverse(GameModel model, float alpha, float beta, int remainingLevels);
/**
 * @brief returns the best evaluated movement for a given position. It does so by
 *        traversing a game tree
 *
 * @param model, describes a specific game situation
 * @param alpha, value of the alpha-beta prunning that should be increased
 * @param beta, value of the alpha-beta prunning that should be decreased
 * @param remainingLevels, counter of how deep we have to go
 */
static Pruning_t minMaxTraverse(GameModel model, float alpha, float beta, int remainingLevels)
{
	nodeCount += 1;

	Pruning_t proposedPlay;
	Pruning_t bestScore;

	/**
	 * There are two base cases (Exit conditions). Either we reached the maximum
	 * depth we should be analyzing, or the game just ended and the node can't be
	 * evaluated any furter. We check for these two first.
	 */



	 /**
	  * Game over, we return -inf if the human won, +inf if the AI won,
	  * 0 in case of a tie.
	  */
	if (model.gameOver == true)
	{

		//The .movement member won't be used on this case
		bestScore.movement = GAME_INVALID_SQUARE;

		unsigned int aiScore, humanScore;
		aiScore = getScore(model, model.aiPlayer);
		humanScore = getScore(model, model.humanPlayer);

		if (aiScore > humanScore) bestScore.value = PLUS_INFINITY_FLOAT;
		else if (humanScore > aiScore) bestScore.value = MINUS_INFINITY_FLOAT;
		else bestScore.value = (float)0;

		return bestScore;

	}

	/**
	 * If we reached the desired depth, we should prune it too.
	 */
	if (remainingLevels == 0 || nodeCount >= MAX_NODE_COUNT)
	{
		//The .movement member won't be used on this case
		bestScore.movement = GAME_INVALID_SQUARE;
		if (model.originalCurrentPlayer == model.humanPlayer) {
			bestScore.value = evaluateGameStateWithTable(model);
		}
		else if (model.originalCurrentPlayer == model.aiPlayer) {
			bestScore.value = evaluateGameState(model);

		}


		return bestScore;
	}

	/**
	 * If none of the above conditions are met, we keep
	 * on traversing the tree.
	 */

	Moves validMovements;
	getValidMoves(model, validMovements);
	bestScore.movement = validMovements.front();

	if (model.currentPlayer == model.humanPlayer)
	{
		/**
		 * In this case, we want to minimize the value
		 */
		GameModel copiedModel = model;

		bestScore.value = PLUS_INFINITY_FLOAT;


		for (auto movement : validMovements)
		{

			copiedModel = model;
			playMove(copiedModel, movement);
			proposedPlay = minMaxTraverse(copiedModel, alpha, beta, remainingLevels - 1);

			if (proposedPlay.value < bestScore.value)
			{
				bestScore.value = proposedPlay.value;
				bestScore.movement = movement;
			}

			if (beta > bestScore.value)
				beta = bestScore.value;

			//AlphaBeta condition, this branch won't be chosen, no need to keep evaluating.
			if (alpha > beta)
				break;


		}
	}
	else //We have to maximize, it's AI player
	{


		bestScore.value = MINUS_INFINITY_FLOAT;

		GameModel copiedModel;
		for (auto movement : validMovements)
		{
			copiedModel = model;
			playMove(copiedModel, movement);
			proposedPlay = minMaxTraverse(copiedModel, alpha, beta, remainingLevels - 1);


			if (proposedPlay.value > bestScore.value)
			{
				bestScore.value = proposedPlay.value;
				bestScore.movement = movement;
			}

			if (bestScore.value > alpha)
				alpha = bestScore.value;

			//AlphaBeta condition, this branch won't be chosen, no need to keep evaluating.
			if (alpha > beta)
				break;

		}
	}

	return bestScore;
}
// Look up table which provides every cell a value
int squareValues[8][8] = {
	{ 125, -10,	10, 10,	10,	10, -10, 125 },
	{ -10, -50,	1, 1, 1, 1, -50, -10},
	{ 10, 1, 5,	5, 5, 5, 1,	10 },
	{ 10, 1, 5,	30,	30,	5, 1, 10},
	{ 10, 1, 30, 30, 5, 5, 1, 10 },
	{ 10, 1, 5,	5, 5, 5, 1, 10},
	{ -10, -50,	1, 1, 1, 1, -50, -10 },
	{ 125, -10,	10,	10,	10,	10, -10, 125 }
};

/**
 * @brief Returns a specific value from a look up table
 * @param square, has te position of the look up table
 */
double getSquareValue(Square square) {
	return squareValues[square.x][square.y];

}
/**
 * @brief provides a score to a game situation using a look up table
 * @param state, specific game situation to analyze
 */
double evaluateGameStateWithTable(GameModel& state) {
	int score = 0;
	Player originalPlayer = state.originalCurrentPlayer;
	Piece actualPiece = (originalPlayer == PLAYER_BLACK) ? PIECE_BLACK : PIECE_WHITE;
	Piece opponentPiece = originalPlayer == PLAYER_BLACK ? PIECE_WHITE : PIECE_BLACK;

	// We provide add or substract according to the piecies on the board and their importance
	for (int row = 0; row < BOARD_SIZE; row++) {
		for (int col = 0; col < BOARD_SIZE; col++) {
			Square position = { row, col };
			if (getBoardPiece(state, position) == actualPiece) {
				score += getSquareValue(position);
			}
			else if (getBoardPiece(state, position) == opponentPiece) {
				score -= getSquareValue(position);
			}
		}
	}
	return score;
}

/**
 * @brief Given a situation, provides the best move
 * @param model, specific game situation to analyze
 */
Square getBestMove(GameModel& model)
{
	nodeCount = 0;
	Pruning_t bestMove;
	bestMove = minMaxTraverse(model, MINUS_INFINITY_FLOAT, PLUS_INFINITY_FLOAT, MAX_DEPTH);
	return bestMove.movement;

}

/**
 * @brief Checks if a given coordinate is a corner on the board
 * @param row: the given row
 * @param column: the given column
 * @return true if the square is a corner on the board
 */
bool isCorner(int row, int col) {
	return (row == 0 && col == 0) || (row == 0 && col == BOARD_SIZE - 1) ||
		(row == BOARD_SIZE - 1 && col == 0) || (row == BOARD_SIZE - 1 && col == BOARD_SIZE - 1);
}

/**
 * @brief Checks if a given coordinate is a edge (not corner) on the board
 * @param row: the given row
 * @param column: the given column
 * @return true if the square is a corner on the board
 */
bool isEdge(int row, int col) {
	return (row == 0 || row == BOARD_SIZE - 1 || col == 0 || col == BOARD_SIZE - 1);
}
/**
 * @brief provides a score to a game situation.
 * @param state, specific game situation to analyze
 */
double evaluateGameState(GameModel& state) {
	int score = 0;
	Player originalPlayer = state.originalCurrentPlayer;
	Piece actualPiece = (originalPlayer == PLAYER_BLACK) ? PIECE_BLACK : PIECE_WHITE;
	Piece opponentPiece = originalPlayer == PLAYER_BLACK ? PIECE_WHITE : PIECE_BLACK;
	// We add or substract to the score by the importance of the position
	for (int row = 0; row < BOARD_SIZE; row++) {
		for (int col = 0; col < BOARD_SIZE; col++) {
			Square position = { row, col };
			if (getBoardPiece(state, position) == actualPiece) {
				if (isCorner(row, col)) {
					score += CORNER_VALUE;  // Mayor value to corners
				}
				else if (isEdge(row, col)) {
					score += EDGE_VALUE;    // Less value to edges
				}
				else {
					score += PIECE_VALUE;   // Basic value to a common piece
				}
			}
			else if (getBoardPiece(state, position) == opponentPiece) {
				// We substract the opponent piecies
				if (isCorner(row, col)) {
					score -= CORNER_VALUE;
				}
				else if (isEdge(row, col)) {
					score -= EDGE_VALUE;
				}
				else {
					score -= PIECE_VALUE;
				}
			}
		}
	}
	return score;
}
