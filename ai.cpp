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

#define MAX_NODE_COUNT 5000

typedef struct{
    std::forward_list <GameModel> future;
    float minimax;
    unsigned int nodeCount;
}Tree_Nodes_t;

typedef struct{
    Tree_Nodes_t * front;
}Tree_t;





Square getBestMove(GameModel &model)
{
    // To-do: your code goes here...
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
