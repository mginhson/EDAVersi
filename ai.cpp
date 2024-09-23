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
    Pruning_t placeholder;

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










Square getBestMove(GameModel &model, Square lastHumanMovement)
{
    std::vector <int> v;
    
    
}



