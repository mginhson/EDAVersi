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



#define MAX_DEPTH 10

typedef struct{
    float value;
    Square movement;
}Pruning_t; 

static Pruning_t minMaxTraverse (GameModel model, float alpha, float beta, int remainingLevels);

static Pruning_t minMaxTraverse (GameModel model, float alpha, float beta, int remainingLevels)
{
    Pruning_t proposedPlay;    
    if (nodeCount >= MAX_NODE_COUNT)
    {
        
    }
    Pruning_t bestScore;

    if (remainingLevels == 0 || nodeCount >= MAX_NODE_COUNT)
    {
        //evaluate and return;
    }
    
    //We have to minimize
    if (model.currentPlayer == model.humanPlayer)
    {
        float value;
        bestScore.value =  std::numeric_limits<double>::infinity(); //-INF
        bestScore.movement = GAME_INVALID_SQUARE;
        Moves validMovements;
        getValidMoves(model, validMovements);
        GameModel copiedModel = model;
        for (auto movement : validMovements)
        {
            copiedModel = model;
            playMove(copiedModel, movement);
            proposedPlay.movement = movement;
            proposedPlay = minMaxTraverse(copiedModel, alpha, beta, remainingLevels - 1);
            
            if (proposedPlay.value < bestScore.value)
                bestScore = proposedPlay;
            
            if (beta < bestScore.value)
                beta = bestScore.value;

            //AlphaBeta condition
            if (alpha >= beta)
                break;
            

        }
    }
    else //We have to maximize, it's AI player
    {
        float value;
        bestScore.value = -std::numeric_limits<double>::infinity();
        bestScore.movement = GAME_INVALID_SQUARE; //Will always be replaced anyways

        Moves validMovements;
        getValidMoves (model, validMovements);
        GameModel copiedModel;

        for (auto movement : validMovements)
        {
            copiedModel = model;
            playMove (copiedModel,movement);
            proposedPlay = minMaxTraverse(copiedModel, alpha, beta, remainingLevels - 1);
            
            if (proposedPlay.value > bestScore.value)
                bestScore = proposedPlay;
            
            if (bestScore.value > alpha)
                alpha = bestScore.value;

            if (alpha >= beta)
                break;
        }
    }

    return bestScore;
}



static float evaluateNode(GameModel& currentModel)
{
    if (currentModel.gameOver == true)
    {
        
        if (getScore(currentModel, gameTree.aiPlayer) >=
            getScore(currentModel,currentModel.humanPlayer))
        {
            return INFINITY;
        }
        else
        {
            return -INFINITY;
        }
    }
    else
    {
        
        if (getScore(currentModel,gameTree.aiPlayer) >=
            getScore(currentModel,currentModel.humanPlayer))
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }
}









/**
 * @param 
 */
Square getBestMove(GameModel &model, Square lastHumanMovement)
{
    nodeCount = 0;
    /**
     * Call maxMinTraverse with a fixed depth recursively, 
     * each time starting on the new found best position 
     */
    while (nodeCount < MAX_NODE_COUNT)
    {

    }        
    
}



