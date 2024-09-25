/**
 * @brief Implements the Reversi game AI
 * @author Marc S. Ressl
 *
 * @copyright Copyright (c) 2023-2024
 */

#include <cstdlib>
#include <limits>


#include "ai.h"
#include "controller.h"
#include "model.h"
#define MAX_NODE_COUNT 5000
unsigned int nodeCount = 0;

bool isCorner(int row, int col);
bool isEdge(int row, int col);
double evaluateGameState(GameModel& state);
#define MAX_DEPTH 2

typedef struct{
    float value;
    Square movement;
}Pruning_t; 

static Pruning_t minMaxTraverse (GameModel model, float alpha, float beta, int remainingLevels);

static Pruning_t minMaxTraverse (GameModel model, float alpha, float beta, int remainingLevels)
{
    Pruning_t proposedPlay;    
    Pruning_t bestScore;

    if (remainingLevels == 0 || nodeCount >= MAX_NODE_COUNT)
    {
        //The .movement member won't be used on this case
        bestScore.movement = GAME_INVALID_SQUARE;
        bestScore.value = evaluateGameState (model);
        return bestScore;
    }
    
    //We have to minimize
    if (model.currentPlayer == model.humanPlayer)
    {
        float value;

        Moves validMovements;
        getValidMoves(model, validMovements);
        GameModel copiedModel = model;

        bestScore.value = std::numeric_limits<float>::infinity();
        
        

        
        for (auto movement : validMovements)
        {
            copiedModel = model;
            playMove(copiedModel, movement);
            proposedPlay.movement = movement;
            proposedPlay = minMaxTraverse(copiedModel, alpha, beta, remainingLevels - 1);
            
            if (proposedPlay.value < bestScore.value)
                bestScore = proposedPlay;
            
            if (beta > bestScore.value)
                beta = bestScore.value;

            //AlphaBeta condition
           if (alpha > beta)
            break;
            

        }
    }
    else //We have to maximize, it's AI player
    {
        float value;
        

        Moves validMovements;
        getValidMoves (model, validMovements);
        
        if (validMovements.size() > 0)
        {
            bestScore.value = -1 * std::numeric_limits<float>::infinity();
            
            GameModel copiedModel;
            for (auto movement : validMovements)
            {
                copiedModel = model;
                playMove (copiedModel,movement);
                proposedPlay = minMaxTraverse(copiedModel, alpha, beta, remainingLevels - 1);
                proposedPlay.movement = movement;
                if (proposedPlay.value > bestScore.value)
                    bestScore = proposedPlay;
                
                if (bestScore.value > alpha)
                    alpha = bestScore.value;

                if (alpha > beta)
                    break;

            }    
        }
        else //Either won or lost
        {
            int humanScore, aiScore;
            aiScore = getScore (model, model.currentPlayer);
            humanScore = getScore(model, model.humanPlayer);
            
        }
        
    }

    return bestScore;
}


// Definimos algunos pesos para los distintos factores
const int CORNER_VALUE = 100;
const int EDGE_VALUE = 10;
const int PIECE_VALUE = 1;
const int MOBILITY_VALUE = 5;


// Función para verificar si una posición es una esquina
bool isCorner(int row, int col) {
    return (row == 0 && col == 0) || (row == 0 && col == BOARD_SIZE - 1) ||
        (row == BOARD_SIZE - 1 && col == 0) || (row == BOARD_SIZE - 1 && col == BOARD_SIZE - 1);
}

// Función para verificar si una posición es un borde
bool isEdge(int row, int col)  {
    return (row == 0 || row == BOARD_SIZE - 1 || col == 0 || col == BOARD_SIZE - 1);
}

    double evaluateGameState(GameModel & state) {
        double score = 0;
        Player actualPlayer = getCurrentPlayer(state);
        Piece actualPiece = actualPlayer == PLAYER_BLACK ? PIECE_BLACK : PIECE_WHITE;
        Piece opponentPiece = actualPlayer == PLAYER_BLACK ? PIECE_WHITE : PIECE_BLACK;
        // Factor 1: Control de las esquinas y bordes
        for (int row = 0; row < BOARD_SIZE; row++) {
            for (int col = 0; col < BOARD_SIZE; col++) {
                Square position = { row, col };
                if (getBoardPiece(state, position) == actualPiece) {
                    if (isCorner(row, col)) {
                        score += CORNER_VALUE;  // Mayor peso para las esquinas
                    }
                    else if (isEdge(row, col)) {
                        score += EDGE_VALUE;    // Menor peso para los bordes
                    }
                    else {
                        score += PIECE_VALUE;   // Peso básico para una ficha común
                    }
                }
                else if (getBoardPiece(state, position) == opponentPiece) {
                    // Restamos puntos por las piezas del oponente
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
        
        // Factor 2: Movilidad
        Moves validMoves;
        getValidMoves(state, validMoves);
        score += validMoves.size();

        Moves validOpponentMoves;
        state.currentPlayer = actualPlayer == PLAYER_BLACK ? PLAYER_WHITE : PLAYER_BLACK;
        getValidMoves(state, validMoves);
        state.currentPlayer = actualPlayer;

       
        score += (validMoves.size() - validOpponentMoves.size()) * MOBILITY_VALUE;

        return score;
    }









/**
 * @param 
 */
Square getBestMove(GameModel &model)
{
    nodeCount = 0;
    Pruning_t bestMove;
    bestMove = minMaxTraverse (model, -std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity() , MAX_DEPTH);     



    Moves validMoves;

    getValidMoves(model, validMoves);
    
    return bestMove.movement;
        
}

