//
// Created by flasque on 19/10/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "loc.h"
#include "queue.h"

/* prototypes of local functions */
/* local functions are used only in this file, as helper functions */

/**
 * @brief :  function to get the position of the base station
 * @param map : the map
 * @return : the position of the base station
 */
t_position getBaseStationPosition(t_map);

/**
 * @brief : function to calculate costs of the map  from the base station
 * @param map : the map
 * @return none
 */
void calculateCosts(t_map);

/**
 * @brief : function to remove 'false' crevasses costs from the costs array
 * @param map : the map
 * @return none
 */
void removeFalseCrevasses(t_map);

/* definition of local functions */

t_position getBaseStationPosition(t_map map)
{
    t_position pos;
    int i = 0;
    int found = 0;
    while (i < map.y_max && !found)
    {
        int j = 0;
        while (j < map.x_max && !found)
        {
            if (map.soils[i][j] == BASE_STATION)
            {
                pos.x = j;
                pos.y = i;
                found = 1;
            }
            j++;
        }
        i++;
    }
    // if the base station is not found, we exit the program
    if (!found)
    {
        fprintf(stderr, "Error: base station not found in the map\n");
        exit(1);
    }
    return pos;
}

void removeFalseCrevasses(t_map map)
{
    int over = 0;

    while (!over)
    {
        int min_cost = COST_UNDEF;
        int imin = -1, jmin = -1;

        // Trouver la position avec le coût minimum valide (> 10000) et pas une crevasse
        for (int i = 0; i < map.y_max; i++)
        {
            for (int j = 0; j < map.x_max; j++)
            {
                if (map.soils[i][j] != CREVASSE && map.costs[i][j] > 10000 && map.costs[i][j] < min_cost)
                {
                    min_cost = map.costs[i][j];
                    imin = i;
                    jmin = j;
                }
            }
        }

        // Si aucune position valide n'a été trouvée, la boucle peut s'arrêter
        if (imin == -1 || jmin == -1)
        {
            over = 1;
            continue;
        }

        // Calculer les coûts des voisins de cette position
        t_position pos = {jmin, imin};
        t_position lp = LEFT(pos), rp = RIGHT(pos), up = UP(pos), dp = DOWN(pos);
        int min_neighbour = COST_UNDEF;

        if (isValidLocalisation(lp, map.x_max, map.y_max))
            min_neighbour = (map.costs[lp.y][lp.x] < min_neighbour) ? map.costs[lp.y][lp.x] : min_neighbour;

        if (isValidLocalisation(rp, map.x_max, map.y_max))
            min_neighbour = (map.costs[rp.y][rp.x] < min_neighbour) ? map.costs[rp.y][rp.x] : min_neighbour;

        if (isValidLocalisation(up, map.x_max, map.y_max))
            min_neighbour = (map.costs[up.y][up.x] < min_neighbour) ? map.costs[up.y][up.x] : min_neighbour;

        if (isValidLocalisation(dp, map.x_max, map.y_max))
            min_neighbour = (map.costs[dp.y][dp.x] < min_neighbour) ? map.costs[dp.y][dp.x] : min_neighbour;

        // Mettre à jour le coût de la case actuelle
        int self_cost = _soil_cost[map.soils[imin][jmin]];
        int new_cost = min_neighbour + self_cost;

        // Vérification pour éviter les cycles
        if (new_cost < map.costs[imin][jmin])
        {
            map.costs[imin][jmin] = new_cost;
        }
        else
        {
            over = 1; // Arrêt si aucune mise à jour n'est possible
        }
    }
}


void calculateCosts(t_map map)
{
    t_position baseStation = getBaseStationPosition(map);
    //create a queue to store the positions to visit
    t_queue queue = createQueue(map.x_max * map.y_max);
    //enqueue the base station
    enqueue(&queue, baseStation);
    // while the queue is not empty
    while (queue.first != queue.last)
    {
        // dequeue the position
        t_position pos = dequeue(&queue);
        // get its self cost
        int self_cost = _soil_cost[map.soils[pos.y][pos.x]];
        // get ts neighbours
        t_position lp, rp, up, dp;
        lp = LEFT(pos);
        rp = RIGHT(pos);
        up = UP(pos);
        dp = DOWN(pos);
        // get the mimimum cost of the neighbours
        int min_cost = COST_UNDEF;
        if (isValidLocalisation(lp, map.x_max, map.y_max))
        {
            min_cost = (map.costs[lp.y][lp.x] < min_cost) ? map.costs[lp.y][lp.x] : min_cost;
        }
        if (isValidLocalisation(rp, map.x_max, map.y_max))
        {
            min_cost = (map.costs[rp.y][rp.x] < min_cost) ? map.costs[rp.y][rp.x] : min_cost;
        }
        if (isValidLocalisation(up, map.x_max, map.y_max))
        {
            min_cost = (map.costs[up.y][up.x] < min_cost) ? map.costs[up.y][up.x] : min_cost;
        }
        if (isValidLocalisation(dp, map.x_max, map.y_max))
        {
            min_cost = (map.costs[dp.y][dp.x] < min_cost) ? map.costs[dp.y][dp.x] : min_cost;
        }
        // the cost of the current position is the minimum cost of the neighbours + 1 or 0 if the soil is a base station
        map.costs[pos.y][pos.x] = (map.soils[pos.y][pos.x] == BASE_STATION) ? 0 : min_cost + self_cost;
        // enqueue the neighbours if they are not visited yet
        if (isValidLocalisation(lp, map.x_max, map.y_max) && map.costs[lp.y][lp.x] == COST_UNDEF)
        {
            // mark as visited - change the cost to 65534
            map.costs[lp.y][lp.x] = COST_UNDEF-1;
            enqueue(&queue, lp);
        }
        if (isValidLocalisation(rp, map.x_max, map.y_max) && map.costs[rp.y][rp.x] == COST_UNDEF)
        {
            map.costs[rp.y][rp.x] = COST_UNDEF-1;
            enqueue(&queue, rp);
        }
        if (isValidLocalisation(up, map.x_max, map.y_max) && map.costs[up.y][up.x] == COST_UNDEF)
        {
            map.costs[up.y][up.x] = COST_UNDEF-1;
            enqueue(&queue, up);
        }
        if (isValidLocalisation(dp, map.x_max, map.y_max) && map.costs[dp.y][dp.x] == COST_UNDEF)
        {
            map.costs[dp.y][dp.x] = COST_UNDEF-1;
            enqueue(&queue, dp);
        }
    }


    return;
}


/* definition of exported functions */
t_map createMapFromFile(char *filename)
{
    /* rules for the file :
     * - the first line contains the number of lines : y dimension (int)
     * - the second line contains the number of columns : x dimension (int)
     * - the next lines contain the map values (int) separated by spaces : one line = one row
     * - the values are the following : 0 = BASE_STATION, 1 = PLAIN, 2 = ERG, 3 = REG, 4 = CREVASSE
     */

    t_map map;
    int xdim, ydim;     // dimensions of the map
    char buffer[100];   // buffer for reading the file line by line

    FILE *file = fopen(filename,"rt");
    if (file == NULL)
    {
        fprintf(stderr, "Error: cannot open file %s\n", filename);
        exit(1);
    }

    // Lire les dimensions
    fscanf(file, "%d", &ydim);
    fscanf(file, "%d", &xdim);

    map.x_max = xdim;
    map.y_max = ydim;

    // Allouer la mémoire pour les sols
    map.soils = (t_soil **)malloc(ydim * sizeof(t_soil *));
    for (int i = 0; i < ydim; i++)
    {
        map.soils[i] = (t_soil *)malloc(xdim * sizeof(t_soil));
    }

    // Allouer la mémoire pour les coûts
    map.costs = (int **)malloc(ydim * sizeof(int *));
    for (int i = 0; i < ydim; i++)
    {
        map.costs[i] = (int *)malloc(xdim * sizeof(int));
    }

    // Lire les valeurs de la carte
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < xdim; j++)
        {
            int value;
            if (fscanf(file, "%d", &value) != 1)
            {
                fprintf(stderr, "Error: failed to read value at position (%d, %d)\n", i, j);
                exit(1);
            }
            map.soils[i][j] = value;
            map.costs[i][j] = (value == BASE_STATION) ? 0 : COST_UNDEF;
        }
    }

    fclose(file);
    calculateCosts(map);
    removeFalseCrevasses(map);
    return map;
}


t_map createTrainingMap()
{
    return createMapFromFile("../maps/training.map");
}

void displayMap(t_map map)
{
    /** the rules for display are :
     * display all soils with 3x3 characters
     * characters are : B for base station, '-' for plain, '~' for erg, '^' for reg, ' ' for crevasse
     */
    for (int i = 0; i < map.y_max; i++)
    {
        for (int rep = 0; rep < 3; rep++)
        {
            for (int j = 0; j < map.x_max; j++)
            {
                char c[8];
                switch (map.soils[i][j])
                {
                    case BASE_STATION:
                        if (rep==1)
                        {
                            strcpy(c, "   B   ");
                        }
                        else
                        {
                            strcpy(c, "       ");
                        }
                        break;
                    case PLAIN:
                        strcpy(c, "-------");
                        break;
                    case ERG:
                        strcpy(c, "~~~~~~~");
                        break;
                    case REG:
                        strcpy(c, "^^^^^^^");
                        break;
                    case CREVASSE:
                        sprintf(c, "%c%c%c%c%c%c%c",219,219,219,219,219,219,219);
                        break;
                    default:
                        strcpy(c, "???????");
                        break;
                }
                printf("%s", c);
            }
            printf("\n");
        }

    }
    return;
}


void new_map(int y, int x) {
    FILE *file = fopen("../maps/new_map.map", "w");

    // Vérifier si le fichier a bien été ouvert
    if (!file) {
        printf("Erreur : impossible d'ouvrir le fichier.\n");
        return;
    }

    // Écrire les dimensions dans le fichier
    fprintf(file, "%d\n", y);
    fprintf(file, "%d\n", x);

    // Générer les coordonnées aléatoires de la station de base
    int base_x = rand() % x;
    int base_y = rand() % y;

    // Calculer le nombre maximum de `4` autorisé globalement
    int max_fours = 3; // Par défaut, limiter à 3
    if (y * x > 30) {
        max_fours = (y * x) / 10; // Ajustement dynamique : max 10 % de `4`
    }

    int count_fours_total = 0; // Compteur global pour le nombre de `4`

    for (int i = 0; i < y; i++) {
        int count_fours_line = 0; // Compteur pour le nombre de `4` par ligne

        for (int j = 0; j < x; j++) {
            if (i == base_y && j == base_x) {
                // Insérer la station de base
                fprintf(file, "%d", 0);
            } else {
                int value;
                do {
                    // Générer un sol aléatoire
                    value = (rand() % 4) + 1; // Valeurs possibles : 1, 2, 3, 4
                } while (
                        (value == 4 && count_fours_total >= max_fours) || // Limiter le total des `4`
                        (value == 4 && count_fours_line >= 1)            // Limiter les `4` par ligne
                        );

                // Si la valeur générée est `4`, incrémenter les compteurs
                if (value == 4) {
                    count_fours_total++;
                    count_fours_line++;
                }

                // Écrire la valeur dans le fichier
                fprintf(file, "%d", value);
            }

            // Ajouter un espace sauf à la fin de la ligne
            if (j < x - 1) {
                fprintf(file, " ");
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

void displayCost(t_map map){
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }
    return;
}