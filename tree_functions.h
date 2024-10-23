//
// Created by Laetitia Arnoult on 23/10/2024.
//

#ifndef MARC_PROJECT_BERNARD_LASSOUT_GARCIA_ARNOULT_TREE_FUNCTIONS_H
#define MARC_PROJECT_BERNARD_LASSOUT_GARCIA_ARNOULT_TREE_FUNCTIONS_H

typedef struct s_node{
    int value;//valeur stockée dans le noeud
    int depth; // profondeur de l'arbre
    struct s_node **sons;
    int nbSons; // nombre de fils fils
}t_node;

t_node *createNode(int val, int nbSons);


#endif //MARC_PROJECT_BERNARD_LASSOUT_GARCIA_ARNOULT_TREE_FUNCTIONS_H
