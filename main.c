#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "map.h"
#include "moves.h"
#include "tree_functions.h"

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
    t_move tabAction[5] = {F_10, F_20, F_30, T_LEFT, T_RIGHT };
//    t_move tabAction[1] = {T_LEFT};


    /// Création de l'arbre des chemins empreintés (3 choix/profondeur)
    int value = map.costs[robot.pos.x][robot.pos.y];
    t_node *new_tree = createTrainingTree(value, 0, 5, robot, tabAction, map);

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


/*    for(int i = 0; i < 5; i++){
        printf("%d\n", tabAction[i]);
    }
    printf("\n");
    for(int i = 0; i < 5; i++){
        for(int j = i; j < 4; j++){
            tabAction[j] = tabAction[j + 1];
        }
    }

    for(int i = 0; i < 4; i++){
        printf("%d\n", tabAction[i]);
    }
    printf("\n%d %d", map.x_max, map.y_max);*/

    printf("Minimum : %d\n", findMin(new_tree, 0, 3, 10000));

    return 0;
}
