//
// Created by Laetitia Arnoult on 23/10/2024.
//

#include "tree_functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>



t_node *createTree(int tree_depth, t_map map, int x, int y){
    t_node *tree = createNode(map.costs[x][y], 5, 0);
    if (tree_depth > 0) {
        for (int i = 0; i < 5; i++) {
            tree->sons[i] = createNode(i + 1, 5, tree->depth + 1);
        }
    }
    return tree;
}


t_node *createNode(int val, int nbSons, int depth){
    t_node *new = (t_node *) malloc(sizeof(t_node));
    new->value = val;   // Valeur stocké
    new->depth = depth; // Profondeur du nœud
    new->nbSons = nbSons;    // Nombre de nœuds fils
    new->sons = (t_node **) malloc(new->nbSons * sizeof(t_node *));
    for (int i = 0; i < new->nbSons; i++){
        new->sons[i] = NULL;
    }
    return new;
}


t_node *createTrainingTree(int value, int depth, int nbSons, t_localisation robot, t_move *tabAction, t_map map) {
    t_node *node = createNode(value, nbSons, depth);

    if (depth > 0) {
        for (int i = 0; i < nbSons; i++) {
            t_localisation new_robot = move(robot, tabAction[i]);
//            updateLocalisation(&robot, tabAction[i]);
            //printf("%d\n", robot.ori);
            //printf("new robot = (%d,%d)\n", robot.pos.x, robot.pos.y);
            if (isValidLocalisation(new_robot.pos, map.x_max - 1, map.y_max - 1)) {
                int caseValue = map.costs[new_robot.pos.x][new_robot.pos.y];
                if (0 < caseValue && caseValue < 10000) {
                    t_move *new_tabAction = (t_move *) malloc((nbSons - 1) * sizeof (t_move));
                    for(int j = i; j < nbSons - 1; j++){
                      new_tabAction[j] = tabAction[j + 1];
                    }
                    node->sons[i] = createTrainingTree(caseValue, depth - 1, nbSons - 1, new_robot, new_tabAction, map);
                }
                else{
                    node->sons[i] = createNode(caseValue, 0, depth);
                }
            }
            else {
                node->sons[i] = createNode(10000, 0, depth);
            }
        }
    }
    return node;
}

t_node *createTrainingTree2(int value, int depth, int nbSons, t_localisation robot, t_move *tabAction, t_map map) {
    t_node *node = createNode(value, nbSons, depth);

    if (depth > 0) {
        for (int i = 0; i < nbSons; i++) {
            updateLocalisation(&robot, tabAction[i]);
            int caseValue = map.costs[robot.pos.x][robot.pos.y];
            for (int j = i; j < nbSons - 1; j++){
                tabAction[j] = tabAction[j + 1];
            }
            tabAction = (t_move *) realloc(tabAction, (nbSons - 1) * sizeof(t_move));
            node->sons[i] = createTrainingTree(caseValue, depth - 1, nbSons - 1, robot, tabAction, map);
        }
    }
    return node;
}


void displayTree(t_node *root, int depth, int is_last_child) {
    if (root == NULL) {
        return;
    }
    // Affichage de l'indentation pour chaque niveau
    for (int i = 0; i < depth - 1; i++) {
        printf("│   ");
    }

    // Affichage des caractères d'arbre pour le niveau actuel
    if (depth > 0) {
        if (is_last_child) {
            printf("└── ");
        } else {
            printf("├── ");
        }
    }

    // Affichage de la valeur du nœud
    printf("%d\n", root->value);

    // Affichage récursif pour chaque enfant
    for (int i = 0; i < root->nbSons; i++) {
        int is_last = (i == root->nbSons - 1);
        displayTree(root->sons[i], depth + 1, is_last);
    }
}


t_move *tirageAction(){
    t_move *tab_action = (t_move *) malloc(5 * sizeof(t_move));

    double forward_10 = 0.22, forward_20 = 0.37, forward_30 = 0.44, backward = 0.51, t_left = 0.72, t_right = 0.93, u_turn = 1;
    srand(clock());

    for (int i = 0; i < 5; i++){
        double randomValue = (double) rand()/RAND_MAX;
        if (randomValue <= forward_10)
            tab_action[i] = F_10;
        else if (forward_10 <= randomValue && randomValue <= forward_20--)
            tab_action[i] = F_20;
        else if (forward_20 <= randomValue && randomValue <= forward_30--)
            tab_action[i] = F_30;
        else if (forward_30 <= randomValue && randomValue <= backward--)
            tab_action[i] = B_10;
        else if (backward <= randomValue && randomValue <= t_left--)
            tab_action[i] = T_LEFT;
        else if (t_left <= randomValue && randomValue <= t_right--)
            tab_action[i] = T_RIGHT;
        else if (t_right <= randomValue && randomValue <= u_turn--)
            tab_action[i] = U_TURN;
        else
            i--;
    }

    return tab_action;
}