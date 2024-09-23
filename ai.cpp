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

typedef struct{
    float alpha, beta;
}Pruning_t;

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




static void buildTree(Tree_Nodes_t& currentState, unsigned int levelCount) {
    Tree_Nodes_t placeholder;
    if (levelCount == 0) {
        return;
    }
    Moves validMoves;
    getValidMoves(currentState.proposedGameModel, validMoves);
    for (auto &move : validMoves) {
        
        
        placeholder.proposedGameModel = currentState.proposedGameModel;
        placeholder.previousMovement = move;
        playMove(placeholder.proposedGameModel, move);
        currentState.nextStates.push_front(placeholder);

    }
    for (auto &node : currentState.nextStates) {
        buildTree(node, levelCount - 1);
    }
    
}

#define BRANCHES_LEVEL 4




Square getBestMove(GameModel &model, Square lastHumanMovement)
{
    std::vector <int> v;
    
    
}



