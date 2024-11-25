//
// Created by Laetitia Arnoult on 23/10/2024.
//

#ifndef MARC_PROJECT_BERNARD_LASSOUT_GARCIA_ARNOULT_TREE_FUNCTIONS_H
#define MARC_PROJECT_BERNARD_LASSOUT_GARCIA_ARNOULT_TREE_FUNCTIONS_H

#include "map.h"
#include "moves.h"
#include "loc.h"
#include "stack.h"
#include "queue.h"


/**
 * @brief structure for the node
 * @param value : the value stored in the node
 * @param depth : the depth of the node
 * @param sons : table of the sons
 * @param nbSons : the number of sons
 * @param prev : the pointer to the parent node
 * @param action : the action performed at this node
 */
typedef struct s_node{
    int value;  // Valeur stockée dans le nœud
    int depth;  // Profondeur du nœud
    struct s_node **sons;   // Tableau des fils
    int nbSons; // Nombre de fils (taille physique)
    struct s_node *prev;    // Pointeur vers le nœud précédent
    t_move action;  // Action du nœud
} t_node;


/**
 * @brief Function to create a node of the case
 * @param val : the value stocked in the node
 * @param nbSons : the number of sons in the node
 * @param depth : the level of the node
 * @return A node
 */
t_node *createRoot(int val, int nbSons);

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
 * @param nbMoveEnd : the number of moves at the end (depth max of the tree)
 * @param robot : the localisation of the robot
 * @param tabAction : the actions table
 * @param map : the map use for the tree
 * @return A tree (t_node)
 */
t_node *createTree(int value, int depth, int nbSons, int nbMoveEnd, t_localisation robot, t_move *tabAction, t_map map, t_node *prev, t_move action);


/**
 * @brief Function to display a tree
 * @param root : the pointer to the root of the tree
 * @param depth : the depth of the tree
 * @param is_last_child : variable indicating that this is the last node
 */
void displayTree(t_node *root, int depth, int is_last_child);


/**
 * @brief Function to find the minimum value among the leafs of the tree
 * @param tree : the pointer to the root of the tree
 * @param depth : the depth of the actual node
 * @param depthMax : the maximum depth of the tree
 * @param minNode : the pointer of the minimum leaf already find
 * @return The minimum value among the leafs of the tree
 */
int findMin(t_node *tree, int depth, int depthMax, int min);


/**
 * @brief Function to find the minimum value of a node among the leafs of the tree
 * @param tree : the pointer to the root of the tree
 * @param depth : the depth of the actual node
 * @param depthMax : the maximum depth of the tree
 * @param minNode : the pointer of the minimum leaf already find
 * @return The minimum leaf of the tree
 */
t_node* findMinNode(t_node *tree, int depth, int depthMax, t_node *minNode);

/**
 * @brief Function to make a stack of action to go to the minimum leaf
 * @param min : the pointer of the minimum leaf node
 * @return A stack of actions
 */
t_stack path_min_choices(t_node *min);


/**
 * @brief Function to make the random draw of the 9 actions
 * @return A tab of 9 actions
 */
t_move *tirage_aleatoire_adaptatif();


/**
 * @brief Function to display the tab of actions
 * @param tabAction : the tab of actions
 */
void displayMoveTab(t_move *tabAction);

#endif //MARC_PROJECT_BERNARD_LASSOUT_GARCIA_ARNOULT_TREE_FUNCTIONS_H
