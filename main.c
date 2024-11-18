#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "map.h"
#include "moves.h"
#include "tree_functions.h"
#include <limits.h>

int main() {
    t_map map = createMapFromFile("../maps/example1.map");
    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }
    // printf the costs, aligned left 5 digits
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }
    displayMap(map);


    /// Initialisation du robot en (0, 3) orienté vers l'Est
    t_localisation robot = loc_init(3, 0, EAST);

    /// Initialisation de l'enchaînement d'action
//    t_move tabAction[5] = {F_10, F_20, F_30, T_LEFT, T_RIGHT };
//    t_move tabActionleft[1] = {T_LEFT};

    t_move * tabAction = tirage_aleatoire_adaptatif();



    /// Création de l'arbre des chemins empreintés (3 choix/profondeur)
    int value = map.costs[robot.pos.x][robot.pos.y];
    t_node *new_tree = createTrainingTree(value, 0, 9, robot, tabAction, map, NULL, -1);

    /// Affichage de l'arbre des chemins empreintés
    displayTree(new_tree, 0, 1);

    /// Test des résultats
    printf("\nPosition avant déplacement :\nx : %d\ny : %d\nori : %d\n", robot.pos.x, robot.pos.y, robot.ori);
    printf("%d\n", map.costs[robot.pos.x][robot.pos.y]);
//    t_localisation new_robot;
//    new_robot.ori = rotate(robot.ori, T_LEFT);
//    new_robot = translate(robot, T_LEFT);
    updateLocalisation(&robot, T_LEFT);
    printf("isValidLocation : %d\n", isValidLocalisation(robot.pos, map.x_max - 1, map.y_max - 1));
    //robot.pos.y = robot.pos.y - 1;
    printf("Position après déplacement :\nx : %d\ny : %d\nori : %d\n", robot.pos.x, robot.pos.y, robot.ori);
    printf("%d\n\n", map.costs[robot.pos.x][robot.pos.y]);


//    t_node *mini_node = findMin(new_tree, 0, 9, INT_MAX);
    t_node *maxnode = createRoot(INT_MAX, 0, 0);
    t_node *mini_node = findMinNode(new_tree, 0, 9, maxnode);

    printf("Minimum : %d\n", mini_node->value);
    t_stack stack = path_min_choices(mini_node);
    for(int i = 0; i<=stack.size; i++){
        printf("%d\n", stack.moves[i]);
    }


    return 0;
}
