//
// Created by Laetitia Arnoult on 23/10/2024.
//

#include "tree_functions.h"
#include <stdlib.h>

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