//
// Created by Laetitia Arnoult on 23/10/2024.
//

#include "tree_functions.h"
#include <stdlib.h>

t_n_node *createTree(int depth){
    t_n_node *new;
    new = (t_n_node *) malloc(sizeof(t_n_node));
    new->value = 0;
    new->depth = depth;
    new->sons = (t_node **) malloc(5 * sizeof(t_node *));
    for (int i = 0; i < 5; i++){
        new->sons[i] = createNode(i + 1, 4);
    }
    return new;
}



t_node *createNode(int val, int nb_Sons){
    t_node *new;
    new = (t_node *)malloc(sizeof (t_node));
    new->value = val;
    new->nbSons = nb_Sons;
    new->sons = (t_node **) malloc(nb_Sons*sizeof(t_node *));
    for (int i = 0; i<nb_Sons; i++){
        new->sons[i] = NULL;
    }
    return new;
}

