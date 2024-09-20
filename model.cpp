/**
 * @brief Implements the Reversi game model
 * @author Marc S. Ressl
 *
 * @copyright Copyright (c) 2023-2024
 */

#include "raylib.h"

#include "model.h"

void initModel(GameModel &model)
{
    model.gameOver = true;

    model.playerTime[0] = 0;
    model.playerTime[1] = 0;

    memset(model.board, PIECE_EMPTY, sizeof(model.board));
}

void startModel(GameModel &model)
{
    model.gameOver = false;

    model.currentPlayer = PLAYER_BLACK;

    model.playerTime[0] = 0;
    model.playerTime[1] = 0;
    model.turnTimer = GetTime();

    memset(model.board, PIECE_EMPTY, sizeof(model.board));
    model.board[BOARD_SIZE / 2 - 1][BOARD_SIZE / 2 - 1] = PIECE_WHITE;
    model.board[BOARD_SIZE / 2 - 1][BOARD_SIZE / 2] = PIECE_BLACK;
    model.board[BOARD_SIZE / 2][BOARD_SIZE / 2] = PIECE_WHITE;
    model.board[BOARD_SIZE / 2][BOARD_SIZE / 2 - 1] = PIECE_BLACK;
}

Player getCurrentPlayer(GameModel &model)
{
    return model.currentPlayer;
}

int getScore(GameModel &model, Player player)
{
    int score = 0;

    for (int y = 0; y < BOARD_SIZE; y++)
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            if (((model.board[y][x] == PIECE_WHITE) &&
                 (player == PLAYER_WHITE)) ||
                ((model.board[y][x] == PIECE_BLACK) &&
                 (player == PLAYER_BLACK)))
                score++;
        }

    return score;
}

double getTimer(GameModel &model, Player player)
{
    double turnTime = 0;

    if (!model.gameOver && (player == model.currentPlayer))
        turnTime = GetTime() - model.turnTimer;

    return model.playerTime[player] + turnTime;
}

Piece getBoardPiece(GameModel &model, Square square)
{
    return model.board[square.y][square.x];
}

void setBoardPiece(GameModel &model, Square square, Piece piece)
{
    model.board[square.y][square.x] = piece;
}

bool isSquareValid(Square square)
{
    return (square.x >= 0) &&
           (square.x < BOARD_SIZE) &&
           (square.y >= 0) &&
           (square.y < BOARD_SIZE);
}

void getValidMoves(GameModel &model, Moves &validMoves)
{
    // To-do: your code goes here...

    for (int y = 0; y < BOARD_SIZE; y++)
        for (int x = 0; x < BOARD_SIZE; x++) 
        {
            Square move = {x, y};

            // +++ TEST
            // Lists all empty squares...
            if (getBoardPiece(model, move) == PIECE_EMPTY)
                validMoves.push_back(move);
            // --- TEST
             // Si la posición ya esta ocupada no es un movimiento valido 
            Player player = getCurrentPlayer(model);
            Piece pos = getBoardPiece(model, move);

            if (pos != PIECE_EMPTY) {
                continue;
            }
            // Si el jugador es el negro
            if (player == PLAYER_BLACK) {
                // Recorremos todas las direcciones alrededor de la pieza
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        if (j == 0 && i == 0) {
                            continue;
                        }
                        Square check_piece = { x + i, y + j };

                        for (int steps = 0; isSquareValid(check_piece); steps++) {
                            // Obtenemos una pieza desplazandonos en una dirección
                            Piece directional_piece = getBoardPiece(model, check_piece);
                            if (directional_piece == PIECE_EMPTY) {
                                break;
                            }
                            else if (directional_piece == PIECE_BLACK) {
                                if (steps == 0) {
                                    break;
                                }
                                else {
                                    validMoves.push_back(move);
                                    break;
                                }
                            }
                            // Si la pieza es blanca avanzo en la dirección
                            check_piece = { x + (steps + 2) * i, y + (steps + 2) * j };

                        }
                    }
                }
            }
            else if (player == PLAYER_WHITE) {
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        if (j == 0 && i == 0) {
                            continue;
                        }
                        Square check_piece = { x + i, y + j };
                        bool valid_piece = 0;
                        for (int steps = 0; isSquareValid(check_piece); steps++) {
                            // Obtenemos una pieza desplazandonos en una dirección
                            Piece directional_piece = getBoardPiece(model, check_piece);
                            if (directional_piece == PIECE_EMPTY) {
                                break;
                            }
                            else if (directional_piece == PIECE_WHITE) {
                                if (steps == 0) {
                                    break;
                                }
                                else {
                                    validMoves.push_back(move);
                                    break;
                                }
                            }
                            // Si la pieza es blanca avanzo en la dirección
                            check_piece = { x + (steps + 2) * i, y + (steps + 2) * j };

                        }
                    }
                }
            }
        }
}

bool playMove(GameModel &model, Square move)
{
    // Set game piece
    Piece piece =
        (getCurrentPlayer(model) == PLAYER_WHITE)
            ? PIECE_WHITE
            : PIECE_BLACK;

    setBoardPiece(model, move, piece);

    // To-do: your code goes here...

    // Update timer
    double currentTime = GetTime();
    model.playerTime[model.currentPlayer] += currentTime - model.turnTimer;
    model.turnTimer = currentTime;

    // Swap player
    model.currentPlayer =
        (model.currentPlayer == PLAYER_WHITE)
            ? PLAYER_BLACK
            : PLAYER_WHITE;

    // Game over?
    Moves validMoves;
    getValidMoves(model, validMoves);

    if (validMoves.size() == 0)
        model.gameOver = true;

    return true;
}
