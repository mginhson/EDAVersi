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




typedef struct Tree_Nodes_t{
    //std::forward_list <GameModel> future;
    GameModel proposedGameModel;
    Square previousMovement;
    std::forward_list<struct Tree_Nodes_t> nextStates;
    float minimax;
    unsigned int nodeCount;
    Square movementMadePreviously;
}Tree_Nodes_t;

typedef struct{
    Tree_Nodes_t * front;
}Tree_t;

static void buildTree(GameModel& currentModel, Tree_Nodes_t& ptr , unsigned int nodeCount);
static void deleteTree(Tree_Nodes_t * branch);
static float evaluateNode(GameModel& currentModel);
static void traverseTree(Tree_Nodes_t& treeNode);


//Tree_Nodes_t asfa;
//buildTree(currentModel, asfa, );
static void traverseTree(Tree_Nodes_t& treeNode) {
    
    if (treeNode.nextStates.empty()) {
        // Quiero llamara la función que evalua un nodo
        return;
    }   
    treeNode.minimax = 0;   
     // visitPreorder(node);
    for (auto &childNode : treeNode.nextStates) {
        traverseTree(childNode);
        treeNode.minimax += childNode.minimax;
    }
    // Visit Postorder
    
}

static void buildTree(Tree_Nodes_t& currentState, unsigned int levelCount) {
    if (levelCount == 0) {
        return;
    }
    Moves validMoves;
    getValidMoves(currentState.proposedGameModel, validMoves);
    for (auto &move : validMoves) {
        struct Tree_Nodes_t newNode;
        
        newNode.proposedGameModel = currentState.proposedGameModel;
        newNode.previousMovement = move;
        playMove(newNode.proposedGameModel, move);
        currentState.nextStates.push_front(newNode);

    }
    for (auto &node : currentState.nextStates) {
        buildTree(node, levelCount - 1);
    }
    
}


Tree_t gameTree;

#define MOVEMENTS_TO_PREDICT 20
Square getBestMove(GameModel &model, Square lastHumanMovement)
{
    //Caso inicial
    if (gameTree.front == NULL)
    {
        gameTree.front = new Tree_Nodes_t;
        gameTree.front->proposedGameModel = model; //copy the model
        buildTree((*(gameTree.front)), MOVEMENTS_TO_PREDICT);
    }
    
    if (isSquareValid(lastHumanMovement)) //No fue el primer movimiento
    {
        for (auto i : gameTree.front->nextStates)
        {
            if ((i.previousMovement.x == lastHumanMovement.x) &&
                (i.previousMovement.y == lastHumanMovement.y))
            {
                //es este
            }
            else
            {
                //borrar el subtree
            }
        }
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
