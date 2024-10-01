/**
 * @brief Implements the Reversi game controller
 * @author Marc S. Ressl
 * @modifiers Sosa Mateo, Ginhson Matteo
 * @copyright Copyright (c) 2023-2024
 */

#include <algorithm>
#include <iostream>
using namespace std;

#include "raylib.h"
#include <iostream>
#include "ai.h"
#include "view.h"
#include "controller.h"

#define SELFPLAY false

bool updateView(GameModel& model)
{
	static Square lastHumanMovement = GAME_INVALID_SQUARE;
	if (WindowShouldClose())
		return false;


	if (model.gameOver)
	{
		if (IsMouseButtonPressed(0))
		{
			if (isMousePointerOverPlayBlackButton())
			{
				model.humanPlayer = PLAYER_BLACK;
				model.aiPlayer = PLAYER_WHITE;
				startModel(model);
			}
			else if (isMousePointerOverPlayWhiteButton())
			{
				model.humanPlayer = PLAYER_WHITE;
				model.aiPlayer = PLAYER_BLACK;
				startModel(model);
			}
		}
	}
	else if (model.currentPlayer == model.humanPlayer)
	{
		//Call the setter of .originalCurrentPlayer
		setOriginalCurrentPlayer(model, model.humanPlayer);

		//If self play is enabled, use getBestMove    
		if (SELFPLAY)
		{
			Square square = getBestMove(model);
			playMove(model, square);
		}
		else
		{
			if (IsMouseButtonPressed(0))
			{
				// Human player
				Square square = getSquareOnMousePointer();

				if (isSquareValid(square))
				{
					Moves validMoves;
					getValidMoves(model, validMoves);

					// Play move if valid
					for (auto move : validMoves)
					{
						if ((square.x == move.x) &&
							(square.y == move.y))
						{
							playMove(model, square);
							lastHumanMovement = square;
						}
					}
				}
			}
		}

	}
	else
	{
		//Call the setter of .originalCurrentPlayer

		setOriginalCurrentPlayer(model, model.aiPlayer);
		Square square = getBestMove(model);

		playMove(model, square);
	}

	if ((IsKeyDown(KEY_LEFT_ALT) ||
		IsKeyDown(KEY_RIGHT_ALT)) &&
		IsKeyPressed(KEY_ENTER))
		ToggleFullscreen();

	drawView(model);

	return true;
}
