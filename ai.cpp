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



#define MAX_DEPTH 4
static float minMaxTraverse (GameModel model, float alpha, float beta, int remainingLevels)
{
    

    float bestScore;

    if (remainingLevels == 0)
    {
        //evaluate
    }
    
    //We have to minimize
    if (model.currentPlayer == model.humanPlayer)
    {
        float value;
        bestScore =  std::numeric_limits<double>::infinity(); //-INF
        Moves validMovements;
        getValidMoves(model, validMovements);
        GameModel copiedModel = model;
        for (auto movement : validMovements)
        {
            copiedModel = model;
            playMove(copiedModel, movement);
            value = minMaxTraverse(copiedModel, alpha, beta, remainingLevels - 1);
            bestScore = std::min(value, bestScore);
            beta = std::min(beta, bestScore);

            //AlphaBeta condition
            if (alpha >= beta)
                break;
            

        }
    }
    else //We have to maximize, it's AI player
    {
        float value;
        bestScore = -std::numeric_limits<double>::infinity();
        Moves validMovements;
        getValidMoves (model, validMovements);
        GameModel copiedModel;

        for (auto movement : validMovements)
        {
            copiedModel = model;
            playMove (copiedModel,movement);
            value = minMaxTraverse(copiedModel, alpha, beta, remainingLevels - 1);
            bestScore = std::max(bestScore, value);
            alpha = std::max(alpha, bestScore);

            if (alpha >= beta)
                break;
        }
    }

    return bestScore;
}


// Definimos algunos pesos para los distintos factores
const int CORNER_VALUE = 100;
const int EDGE_VALUE = 10;
const int PIECE_VALUE = 1;
const int MOBILITY_VALUE = 5;

int countPieces(GameModel &state, int player) {
    int count = 0;
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (board[row][col] == player) {
                count++;
            }
        }
    }
    return count;
}

// Función para contar las jugadas válidas (movilidad)
int countValidMoves(int player) {
    // Aquí necesitarías implementar la lógica para contar jugadas válidas
    // con base en las reglas de Reversi. Esta función es solo un marcador.
    return 0;
}

// Función para verificar si una posición es una esquina
bool isCorner(int row, int col) {
    return (row == 0 && col == 0) || (row == 0 && col == BOARD_SIZE - 1) ||
        (row == BOARD_SIZE - 1 && col == 0) || (row == BOARD_SIZE - 1 && col == BOARD_SIZE - 1);
}

// Función para verificar si una posición es un borde
bool isEdge(int row, int col)  {
    return (row == 0 || row == BOARD_SIZE - 1 || col == 0 || col == BOARD_SIZE - 1);
}

    int evaluate(GameModel & state) {
        int score = 0;
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











Square getBestMove(GameModel &model, Square lastHumanMovement)
{
    std::vector <int> v;
    
    
}



