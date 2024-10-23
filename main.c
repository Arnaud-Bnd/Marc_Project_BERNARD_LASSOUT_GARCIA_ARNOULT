#include <stdio.h>
#include "map.h"
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

    t_n_node *new_tree = createTree(3);
    printf("\t\t\t%d\n", new_tree->value);
    for (int i = 0; i < 5; i++) {
        printf("%d\t", new_tree->sons[i]->value);
    }
    return 0;
}
