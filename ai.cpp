/**
 * @brief Implements the Reversi game AI
 * @author Marc S. Ressl
 *
 * @copyright Copyright (c) 2023-2024
 */

#include <cstdlib>
#include <forward_list>
#include <iostream>

#include "ai.h"
#include "controller.h"
#include "model.h"
#define MAX_NODE_COUNT 5000
unsigned int nodeCount = 0;

typedef struct{
    float alpha, beta;
}Pruning_t;

#define MAX_DEPTH 4
static Pruning_t minMaxTraverse (GameModel model, float alpha, float beta)
{

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



