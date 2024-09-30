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


#define MAX_NODE_COUNT 100000
#define MAX_DEPTH 7
#define MINUS_INFINITY_FLOAT ( (float)-1 * std::numeric_limits<float>::infinity()) 
#define PLUS_INFINITY_FLOAT ( (float)std::numeric_limits<float>::infinity())



unsigned int nodeCount = 0;

bool isCorner(int row, int col);
bool isEdge(int row, int col);
double evaluateGameState(GameModel& state);


typedef struct {
	float value;
	Square movement;
}Pruning_t;

static Pruning_t minMaxTraverse(GameModel model, float alpha, float beta, int remainingLevels);

static Pruning_t minMaxTraverse(GameModel model, float alpha, float beta, int remainingLevels)
{


	nodeCount += 1; //We are traversing a new node

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
	 * We need to end the traverse
	 */
	if (remainingLevels == 0 || nodeCount >= MAX_NODE_COUNT)
	{
		//The .movement member won't be used on this case
		bestScore.movement = GAME_INVALID_SQUARE;
		bestScore.value = evaluateGameState(model);

		return bestScore;
	}



	/**
	 * If neither condition was met, we keep on traversing the tree
	 */

	 /**
	  * If the game hasn't ended, but the player supposed to play doesn't have
	  * any available movement, we have to give control back to the opposing player
	  */
	  //CHECK THIS, because the player is automatically swapped again on playMove


	  /**
	   * If none of the above conditions are met, we keep on traversing the tree
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

			//AlphaBeta condition
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

			if (alpha > beta)
				break;

		}



	}
	
	return bestScore;
}


// Definimos algunos pesos para los distintos factores
const int CORNER_VALUE = 300;
const int EDGE_VALUE = 1;
const int PIECE_VALUE = 5;
const int MOBILITY_VALUE = 5;



// Función para verificar si una posición es una esquina
bool isCorner(int row, int col) {
	return (row == 0 && col == 0) || (row == 0 && col == BOARD_SIZE - 1) ||
		(row == BOARD_SIZE - 1 && col == 0) || (row == BOARD_SIZE - 1 && col == BOARD_SIZE - 1);
}

// Función para verificar si una posición es un borde
bool isEdge(int row, int col) {
	return (row == 0 || row == BOARD_SIZE - 1 || col == 0 || col == BOARD_SIZE - 1);
}
int squareValues[8][8] = {
					{ 100, -10,	10,	10,	10,	10, -10,100 },
					{-10 ,-50,	1,	1,	1,	1, -50, -10},
					{ 10,	1,	5,	5,	5,	5,	1,	10 },
					{10,	1,	5,	5,	5,	5,	1,	10},
					{ 10,	1,	5,	5,	5,	5,	1,	10 },
					{10,	1,	5,	5,	5,	5,	1,	10},
					{ -10 - 50,	1,	1,	1,	1 - 50 - 10 },
					{ 100, -10,	10,	10,	10,	10, -10,100 }
};
double getSquareValue(Square square) {
	return squareValues[square.x][square.y];
	
} 
double evaluateGameState(GameModel& state) {
	int score = 0;
	Player actualPlayer = getCurrentPlayer(state);
	Piece actualPiece = actualPlayer == PLAYER_BLACK ? PIECE_BLACK : PIECE_WHITE;
	Piece opponentPiece = actualPlayer == PLAYER_BLACK ? PIECE_WHITE : PIECE_BLACK;
	// Factor 1: Control de las esquinas y bordes
	for (int row = 0; row < BOARD_SIZE; row++) {
		for (int col = 0; col < BOARD_SIZE; col++) {
			Square position = { row, col };
			if (getBoardPiece(state, position) == actualPiece) {
				score += getSquareValue(position);
			}
			else if (getBoardPiece(state, position) == opponentPiece) {
				// Restamos puntos por las piezas del oponente
				score -= getSquareValue(position);
			}
		}
	}

	// Factor 2: Movilidad
	Moves validMoves;
	getValidMoves(state, validMoves);
	score += validMoves.size();

	Moves validOpponentMoves;
	state.currentPlayer = actualPlayer == PLAYER_BLACK ? PLAYER_WHITE : PLAYER_BLACK;
	getValidMoves(state, validMoves);
	state.currentPlayer = actualPlayer;
	

	//score += (validMoves.size() - validOpponentMoves.size()) * MOBILITY_VALUE;

	return score;
}









/**
 * @param
 */
Square getBestMove(GameModel& model)
{
	nodeCount = 0;
	Pruning_t bestMove;
	bestMove = minMaxTraverse(model, MINUS_INFINITY_FLOAT, PLUS_INFINITY_FLOAT, MAX_DEPTH);
	if ((bestMove.movement.x < 0) || (bestMove.movement.y > 7))
	{
		printf("IT'S FAILING HERE, ON A GAMEOVER CALL");
	}
	std::cout << bestMove.value;
	return bestMove.movement;

}

