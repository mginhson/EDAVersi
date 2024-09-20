/**
 * @brief Implements the Reversi game AI
 * @author Marc S. Ressl
 *
 * @copyright Copyright (c) 2023-2024
 */

#include <cstdlib>
#include <forward_list>
#include "ai.h"
#include "controller.h"
#include "model.h"
#define MAX_NODE_COUNT 5000

static bool compareBoards(GameModel& model1, GameModel& model2)
{
    for (unsigned int a = 0; a < BOARD_SIZE; a++)
    {
        for (unsigned int b = 0; b < BOARD_SIZE; b++)
        {
            if (getBoardPiece(model1, (Square){a,b}) 
            != getBoardPiece(model1, (Square){a,b}))
            {
                return 0;
            }
        }
    }

    return 1;
}




typedef struct{
    //std::forward_list <GameModel> future;
    GameModel proposedGameModel;
    std::forward_list<Tree_Nodes_t> nextStates;
    float minimax;
    unsigned int nodeCount;
}Tree_Nodes_t;

typedef struct{
    Tree_Nodes_t * front;
}Tree_t;

static void buildTree(GameModel& currentModel, Tree_Nodes_t& ptr , unsigned int nodeCount);
static void deleteTree(Tree_Nodes_t * branch);
static float evaluateNode(GameModel& currentModel);
static float traverseTree(GameModel& currentModel);


//Tree_Nodes_t asfa;
//buildTree(currentModel, asfa, );

static void buildTree(Tree_Nodes_t& currentState, unsigned int levelCount) {
    if (levelCount == 0) {
        return;
    }
    Moves validMoves;
    getValidMoves(currentState.proposedGameModel, validMoves);
    for (auto &move : validMoves) {
        Tree_Nodes_t* newNode = new Tree_Nodes_t;
        
        newNode->proposedGameModel = currentState.proposedGameModel;
        playMove(newNode->proposedGameModel, move);
        currentState.nextStates.push_front(newNode);

    }
    for (auto &node : currentState.nextStates) {
        buildTree(node, levelCount - 1);
    }
    
}


Tree_t gameTree;

Square getBestMove(GameModel &model)
{
    //Caso inicial
    if (gameTree.front == NULL)
    {
        gameTree.front = new Tree_Nodes_t;
        gameTree.front->proposedGameModel = model; //copy the model
    }
    /**
     * We now need to trim the moves that won't be used, and advance the 
     * Tree's head
     */
    



    Moves validMoves;
    getValidMoves(model, validMoves);

    if (validMoves.size() == 0)
    {
        
    }
    for (auto i : validMoves)
    {
        GameModel tempModel = model;
        playMove(tempModel,i);
        
    }
    
    


    // +++ TEST
    // Returns a random valid move...
    
    
    getValidMoves(model, validMoves);

    int index = rand() % validMoves.size();
    return validMoves[index];
    
    // --- TEST
}
