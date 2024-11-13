//
// Created by Laetitia Arnoult on 23/10/2024.
//

#ifndef MARC_PROJECT_BERNARD_LASSOUT_GARCIA_ARNOULT_TREE_FUNCTIONS_H
#define MARC_PROJECT_BERNARD_LASSOUT_GARCIA_ARNOULT_TREE_FUNCTIONS_H

#include "map.h"
#include "moves.h"
#include "loc.h"

typedef struct s_node{
    int value;  // Valeur stockée dans le nœud
    int depth;  // Profondeur du nœud
    struct s_node **sons;   // Tableau des fils
    int nbSons; // Nombre de fils (taille physique)
    struct s_node *prev;    // Pointeur vers le nœud précédent
    t_move action;  // Action du nœud
} t_node;


typedef struct s_n_node{
    int value;
    int depth;
    t_node **sons;
}t_n_node;


/**
 * @brief Function to create a phase tree
 * @param map : the map used
 * @param x : the x position of the robot
 * @param y : the y position of the robot
 * @return A pointer for a tree
 */
t_node *createTree(int, t_map, int, int);


/**
 * @brief Function to create a node of the case
 * @param val : the value stocked in the node
 * @param nbSons : the number of sons in the node
 * @param depth : the level of the node
 * @return A node
 */
t_node *createRoot(int val, int nbSons, int depth);

/**
 * @brief Function to create a node of the case
 * @param val : the value stocked in the node
 * @param nbSons : the number of sons in the node
 * @param depth : the level of the node
 * @param prev : the precedent node
 * @param action : the current action of the node
 * @return A node
 */
t_node *createNode(int val, int nbSons, int depth, t_node *prev, t_move action);


/**
 * @brief Function to create a tree for tests
 * @param value : the value of the root
 * @param depth : the depth of the tree (number of choice)
 * @param nbSons : the number of children for each node (number of possibilities)
 * @param robot : the localisation of the robot
 * @param tabAction : the actions table
 * @param map : the map use for the tree
 * @return A node
 */
t_node *createTrainingTree(int value, int depth, int nbSons, t_localisation robot, t_move *tabAction, t_map map, t_node *prev, t_move action);
//t_node *createTrainingTree(int value, int depth, int nbSons);


/**
 * @brief Function to display a tree
 * @param root : the pointer to the root of the tree
 * @param depth : the depth of the tree
 * @param is_last_child : variable indicating that this is the last node
 */
void displayTree(t_node *root, int depth, int is_last_child);


t_move *tirageAction();

t_node *findMin(t_node *tree, int depth, int depthMax, int min);

t_node* findMinNode(t_node *tree, int depth, int depthMax, t_node *minNode);


t_move *tirage_aleatoire_adaptatif();


#endif //MARC_PROJECT_BERNARD_LASSOUT_GARCIA_ARNOULT_TREE_FUNCTIONS_H
