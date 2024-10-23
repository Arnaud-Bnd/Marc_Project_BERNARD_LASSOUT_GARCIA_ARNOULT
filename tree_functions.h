//
// Created by Laetitia Arnoult on 23/10/2024.
//

#ifndef MARC_PROJECT_BERNARD_LASSOUT_GARCIA_ARNOULT_TREE_FUNCTIONS_H
#define MARC_PROJECT_BERNARD_LASSOUT_GARCIA_ARNOULT_TREE_FUNCTIONS_H

typedef struct s_node{
    int value;//valeur stockée dans le noeud
    struct s_node **sons;
    int nbSons; // nombre de fils fils
}t_node;

typedef struct s_n_node{
    int value;
    int depth;
    t_node **sons;
}t_n_node;

t_n_node *createTree(int);
t_node *createNode(int, int);


#endif //MARC_PROJECT_BERNARD_LASSOUT_GARCIA_ARNOULT_TREE_FUNCTIONS_H
