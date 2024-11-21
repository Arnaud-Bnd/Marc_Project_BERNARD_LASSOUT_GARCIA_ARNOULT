//
// Created by flasque on 19/10/2024.
//

#ifndef UNTITLED1_STACK_H
#define UNTITLED1_STACK_H

#include "moves.h"

/**
 * @brief Structure for the stack of integers
 */
typedef struct s_stack
{
    t_move *moves;
    int size;
    int nbElts;
} t_stack;

/**
 * @brief Function to create a stack
 * @param size : the size of the stack
 * @return the stack
 */
t_stack createStack(int);

/**
 * @brief Function to push a move in the stack
 * @param pointer to the stack
 * @param move : the move to push
 * @return none
 */
void push(t_stack *, t_move);

/**
 * @brief Function to pop a move from the stack
 * @param : pointer to the stack
 * @return the move popped
 */
t_move pop(t_stack *);

/**
 * @brief Function to get the top move of the stack
 * @param stack : the stack
 * @return the top move
 */
t_move top(t_stack);


#endif //UNTITLED1_STACK_H