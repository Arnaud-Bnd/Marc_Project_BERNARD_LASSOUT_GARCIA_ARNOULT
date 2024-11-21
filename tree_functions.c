//
// Created by Laetitia Arnoult on 23/10/2024.
//

#include "tree_functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <limits.h>
#include "stack.h"



t_node *createTree(int tree_depth, t_map map, int x, int y){
    t_node *tree = createRoot(map.costs[x][y], 5, 0);
    if (tree_depth > 0) {
        for (int i = 0; i < 5; i++) {
            tree->sons[i] = createRoot(i + 1, 5, tree->depth + 1);
        }
    }
    return tree;
}


t_node *createRoot(int val, int nbSons, int depth){
    t_node *new = (t_node *) malloc(sizeof(t_node));
    new->value = val;   // Valeur stocké
    new->depth = depth; // Profondeur du nœud
    new->nbSons = nbSons;    // Nombre de nœuds fils
    new->sons = (t_node **) malloc(new->nbSons * sizeof(t_node *));
    for (int i = 0; i < new->nbSons; i++){
        new->sons[i] = NULL;
    }
    new->prev = NULL;
    new->action = -1;
    return new;
}

t_node *createNode(int val, int nbSons, int depth, t_node *prev, t_move action){
    t_node *new = (t_node *) malloc(sizeof(t_node));
    new->value = val;   // Valeur stocké
    new->depth = depth; // Profondeur du nœud
    new->nbSons = nbSons;    // Nombre de nœuds fils
    new->sons = (t_node **) malloc(new->nbSons * sizeof(t_node *));
    for (int i = 0; i < new->nbSons; i++){
        new->sons[i] = NULL;
    }
    new->prev = prev;
    new->action = action;
    return new;
}


t_node *createTrainingTree(int value, int depth, int nbSons, t_localisation robot, t_move *tabAction, t_map map, t_node *prev, t_move action) {
    /* Création nœud */
    t_node *node;
    if (depth == 0){
         node = createRoot(value, nbSons, depth);
    }
    else {
         node = createNode(value, nbSons, depth, prev, action);
    }

    /* Vérification de la profondeur, doit toujours être supérieur à 0 */
    if (nbSons > 0) {
        /* Parcours de toutes les actions possibles */
        for (int i = 0; i < nbSons; i++) {
            /* Effectuer l'action sélectionnée */
            t_localisation new_robot = move(robot, tabAction[i]);
//            updateLocalisation(&robot, tabAction[i]);
            //printf("%d\n", robot.ori);
            //printf("new robot = (%d,%d)\n", robot.pos.x, robot.pos.y);

            /* Vérifier la validité des coordonnées */
            if (isValidLocalisation(new_robot.pos, map.y_max, map.x_max)) {
                /* Stockage de la valeur de la case */
                int caseValue = map.costs[new_robot.pos.x][new_robot.pos.y];
                /* Si la valeur est comprise entre 0 et 1, créer un nœud avec nbSons - 1 */
                if (0 < caseValue && caseValue < 10000) {
                    // Créer un nouveau tableau d'actions sans l'action courante
                    t_move *new_tabAction = (t_move *) malloc((nbSons - 1) * sizeof(t_move));

                    // Copier les éléments avant l'index courant
                    for (int j = 0; j < i; j++) {
                        new_tabAction[j] = tabAction[j];
                    }

                    // Copier les éléments après l'index courant
                    for (int j = i; j < nbSons - 1; j++) {
                        new_tabAction[j] = tabAction[j + 1];
                    }

                    /* Création du nœud */
                    node->sons[i] = createTrainingTree(caseValue, depth + 1, nbSons - 1, new_robot, new_tabAction, map, node, tabAction[i]);
//                    printf("[%d][%d] : %d\n", new_robot.pos.x, new_robot.pos.y, caseValue);
                    free(new_tabAction);
                }
                /* Sinon créer un nœud sans fils */
                else{
                    node->sons[i] = createNode(caseValue, 0, depth + 1, node, tabAction[i]);
//                    printf("[%d][%d] : %d\n", new_robot.pos.x, new_robot.pos.y, caseValue);
//                    printf("\n");
                }
            }

            /* Création d'un nœud avec la valeur 65535 qui indique qu'on est en dehors de la map */
            else {
//                printf("[%d][%d] : ", new_robot.pos.x, new_robot.pos.y);
//                printf("%d\t", map.costs[new_robot.pos.x][new_robot.pos.y]);
//                printf("%d\n", tabAction[i]);
                node->sons[i] = createNode(65535, 0, depth + 1, node, tabAction[i]);
            }
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
    if (root->depth == 0) {
        printf("%d\n", root->value);
//        printf("%d\t%d\n", root->value, root->action);
    }
    else {
        printf("%d\n", root->value);
//        printf("%d\t%d\t%d\n", root->value, root->prev->value, root->action);
    }
    // Affichage récursif pour chaque enfant
    for (int i = 0; i < root->nbSons; i++) {
        int is_last = (i == root->nbSons - 1);
        displayTree(root->sons[i], depth + 1, is_last);
    }
}



t_move* tirageAction() {

    char* action_names[] = {"forward_10", "forward_20", "forward_30", "backward", "t_left", "t_right", "u_turn"};
    int nb_action=9;

    // Allocation du tableau de 9 actions
    t_move* tab_action = (t_move*) malloc(nb_action * sizeof(t_move));

    double probabilites[] = {0.22, 0.15, 0.07, 0.07, 0.21, 0.21, 0.07};
    int num_actions = sizeof(probabilites) / sizeof(probabilites[0]);


    srand(clock()); // Initialiser le générateur de nombres aléatoires une fois

    for (int i = 0; i < nb_action; i++) {
        double total = 0.0;

        // Calcul de la somme des probabilités pour normalisation
        for (int j = 0; j < num_actions; j++) {
            total += probabilites[j];
        }

        // Génération d'un nombre aléatoire dans l'intervalle [0, total]
        double randomValue = ((double) rand() / RAND_MAX) * total;
        double cumulative = 0.0;
        int action = -1;

        // Détermination de l'action choisie
        for (int j = 0; j < num_actions; j++) {
            cumulative += probabilites[j];
            if (randomValue <= cumulative) {
                action = j;
                break;
            }
        }
        printf("test");
        printf("Tirage %d: %s (randomValue = %f)\n", i + 1, action_names[action], randomValue);
        tab_action[i] = (t_move) action;
        probabilites[action] -= 0.01;
    }
    return tab_action;
}


t_move *tirage_aleatoire_adaptatif() {
    int num_tirages = 9, k = 0;
    double probabilites[] = {0.22, 0.15, 0.07, 0.07, 0.21, 0.21, 0.07};
    t_move action_names[] = {F_10, F_20, F_30, B_10, T_LEFT, T_RIGHT, U_TURN};
    t_move *tabAction = (t_move *) malloc(9 * sizeof (t_move));

// Indices pour chaque action
    int num_actions = sizeof(probabilites) / sizeof(probabilites[0]);

    srand(time(NULL));

    for (int t = 0; t < num_tirages; t++) {
        double total = 0.0;

        // Calcul de la somme des probabilités pour normalisation
        for (int i = 0; i < num_actions; i++) {
            total += probabilites[i];
        }

        // Génération d'un nombre aléatoire dans l'intervalle [0, total]
        double r = ((double) rand() / RAND_MAX) * total;
        double intervalle = 0.0;
        int action = -1;

        // Détermination de l'action choisie
        for (int i = 0; i < num_actions; i++) {
            intervalle += probabilites[i];
            if (r <= intervalle) {
                action = i;
                break;
            }
        }

        // Affichage de l'action sélectionnée
        if (action != -1) {
            tabAction[k++] = action_names[action];
            printf("Tirage %d: %d\n", t + 1, action_names[action]);

            // Réduction de la probabilité de l'action choisie de 0.01, si elle est > 0.01
            if (probabilites[action] > 0.01) {
                probabilites[action] -= 0.01;
            }
        }
    }

    return tabAction;
}

int findMin(t_node *tree, int depth, int depthMax, int min) {
    int i;
    if (tree == NULL){
        printf("L'arbre est vide");
        return min;
    }
    if (depth <= depthMax) {
        for (i = 0; i < tree->nbSons; i++) {
            if (tree->sons[i]->nbSons==0) {
                if (tree->sons[i]->value < min) {
                    min = tree->sons[i]->value;
                }
            }
            min = findMin(tree->sons[i], depth + 1, depthMax, min);
        }
    }
    return min;
}


t_node* findMinNode(t_node *tree, int depth, int depthMax, t_node *minNode) {
    if (tree == NULL) {
        printf("L'arbre est vide\n");
        return minNode;
    }

    if (depth <= depthMax) {
        for (int i = 0; i < tree->nbSons; i++) {
            // Si c'est une feuille
            if (tree->sons[i]->nbSons == 0) {
                // Si c'est le premier nœud minimum ou si la valeur est plus petite que le minNode actuel
                if (minNode == NULL || tree->sons[i]->value < minNode->value) {
                    minNode = tree->sons[i];
                }
            }
            // Appel récursif pour parcourir les nœuds enfants
            minNode = findMinNode(tree->sons[i], depth + 1, depthMax, minNode);
        }
    }

    return minNode;
}

t_stack path_min_choices(t_node *min){
    t_stack pile = createStack(9);
    while (min->prev != NULL){
        push(&pile, min->action);
        min = min->prev;
    }
    return pile;
}

