//
// Created by flasque on 19/10/2024.
//

#include <stdlib.h>
#include <assert.h>
#include "stack.h"

/**
 * @brief Function to create a stack
 * @param size : the size of the stack
 * @return the stack
 */
t_stack createStack(int size){
    // the size of the stack must be positive
    assert(size > 0);
    t_stack stack;
    stack.size = size;
    stack.nbElts = 0;
    stack.moves = (t_move *) malloc(size * sizeof(t_move));
    return stack;
}

/**
 * @brief Function to push a move in the stack
 * @param stack : the stack
 * @param value : the move to push
 * @return none
 */
void push(t_stack *p_stack, t_move move){
    // the stack must not be full
    assert(p_stack->nbElts < p_stack->size);
    p_stack->moves[p_stack->nbElts] = move;
    p_stack->nbElts++;
    return;
}

/**
 * @brief Function to pop a move from the stack
 * @param stack : the stack
 * @return the move popped
 */
t_move pop(t_stack *p_stack){
    // the stack must not be empty
    assert(p_stack->nbElts > 0);
    p_stack->nbElts--;
    return p_stack->moves[p_stack->nbElts];
}

/**
 * @brief Function to get the top move of the stack
 * @param stack : the stack
 * @return the top move
 */
t_move top(t_stack stack)
{
    // the stack must not be empty
    assert(stack.nbElts > 0);
    return stack.moves[stack.nbElts - 1];
}