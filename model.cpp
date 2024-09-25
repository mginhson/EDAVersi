/**
 * @brief Implements the Reversi game model
 * @author Marc S. Ressl
 *
 * @copyright Copyright (c) 2023-2024
 */

#include "raylib.h"

#include "model.h"

void initModel(GameModel& model)
{
	model.gameOver = true;

	model.playerTime[0] = 0;
	model.playerTime[1] = 0;

	memset(model.board, PIECE_EMPTY, sizeof(model.board));
}

void startModel(GameModel& model)
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

Player getCurrentPlayer(GameModel& model)
{
	return model.currentPlayer;
}

int getScore(GameModel& model, Player player)
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

double getTimer(GameModel& model, Player player)
{
	double turnTime = 0;

	if (!model.gameOver && (player == model.currentPlayer))
		turnTime = GetTime() - model.turnTimer;

	return model.playerTime[player] + turnTime;
}

Piece getBoardPiece(GameModel& model, Square square)
{
	return model.board[square.y][square.x];
}

void setBoardPiece(GameModel& model, Square square, Piece piece)
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

void getValidMoves(GameModel& model, Moves& validMoves)
{
	// To-do: your code goes here...
	validMoves.resize(0);
	for (int y = 0; y < BOARD_SIZE; y++) {
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			Square move = { x, y };

			// +++ TEST
			// Lists all empty squares...
			/*
			if (getBoardPiece(model, move) == PIECE_EMPTY)
				validMoves.push_back(move);*/
				// --- TEST
			Player player = getCurrentPlayer(model);
			Piece positionState = getBoardPiece(model, move);

			// Si la posición ya esta ocupada no es un movimiento valido 
			if (positionState != PIECE_EMPTY) {
				continue;
			}
			bool movementAlreadyAdded = false;

				// Recorremos todas las direcciones alrededor de la pieza
			for (int i = -1; i <= 1 && !movementAlreadyAdded; i++) {
				for (int j = -1; j <= 1 && !movementAlreadyAdded; j++) {
					if (j == 0 && i == 0) {
						continue;
					}
					Square directionalSquare = { x + i, y + j };
					
						for (int steps = 0; isSquareValid(directionalSquare) && !movementAlreadyAdded; steps++) {
							// Obtenemos una pieza desplazandonos en una dirección
							Piece directionalPiece = getBoardPiece(model, directionalSquare);
							if (directionalPiece == PIECE_EMPTY) {
								break;
							}
							else if ((directionalPiece == PIECE_BLACK && player == PLAYER_BLACK) ||
								(directionalPiece == PIECE_WHITE && player == PLAYER_WHITE)) {

								if (steps == 0) {
									break;
								}
								else {
									validMoves.push_back(move);
									movementAlreadyAdded = true;
									
								}
							}
							// Si la pieza es blanca avanzo en la dirección
							directionalSquare.x += i;
							directionalSquare.y += j;

						
					}

					
									
				}
			}

		}

	}
}

bool playMove(GameModel& model, Square move)
{
	// Set game piece
	Piece piece =
		(getCurrentPlayer(model) == PLAYER_WHITE)
		? PIECE_WHITE
		: PIECE_BLACK;
	
	setBoardPiece(model, move, piece);


	
	Player player = getCurrentPlayer(model);
	Piece playerColor;

	player == PLAYER_WHITE
						? playerColor = PIECE_WHITE
						: playerColor = PIECE_BLACK;

			
			

	// Recorremos todas las direcciones alrededor de la pieza
	for (int i = -1; i <= 1 ; i++) 
	{
		for (int j = -1; j <= 1 ; j++) 
		{
			if ((j == 0 && i == 0)) 
			{
				continue;
			}
			
			Square directionalSquare = move;
			
			bool shouldDirectionBeFlipped = 0,exitFlag = 0, validStart = 0;
			
			do
			{
			
				//Advance in the said direction
				directionalSquare.x += i;
				directionalSquare.y += j;

				if (isSquareValid(directionalSquare) == 0)
				{
					exitFlag = 1;
					continue;
				}
				
				Piece pointingPiece = getBoardPiece(model, directionalSquare);
				
				if (pointingPiece == PIECE_EMPTY)
				{
					exitFlag = 1;
					continue ;
				}	
				else if (pointingPiece == playerColor)
				{
					exitFlag = 1;
					if (validStart) //There's at least one opposite piece between 2 of ours
						shouldDirectionBeFlipped = 1;
				}	
				else //pointingPiece is the opposite to playerColor 
					validStart = 1;

			} while (exitFlag == 0);

			//If shouldDirectionBeFlipped is true, we iterate until we find our same color.
			//We are sure we will find it because of the previous analysis
			if (shouldDirectionBeFlipped == 1)
			{
				directionalSquare = move;
				exitFlag = 0;
				
				directionalSquare.x += i;
				directionalSquare.y += j;
				
				while((isSquareValid(directionalSquare)) && (getBoardPiece(model, directionalSquare) != playerColor))
				{
					setBoardPiece(model, directionalSquare, playerColor);
					directionalSquare.x += i;
					directionalSquare.y += j;
				}
			}
			

		}
	}	

	
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
	{
		//Swap player
		model.currentPlayer = 
			(model.currentPlayer == PLAYER_WHITE)
				? PLAYER_BLACK
				: PLAYER_WHITE;

		Moves validMoves;
		getValidMoves(model, validMoves);
		if (validMoves.size() == 0)
			model.gameOver = true;
	}

	return true;
}
