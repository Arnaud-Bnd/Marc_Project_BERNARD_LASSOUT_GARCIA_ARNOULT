#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "map.h"
#include "moves.h"
#include "tree_functions.h"
#include <limits.h>
#include "SDL.h"


int main() {
    int langue, fin = 0;
    clock_t start, end;

    int action, isNewMap = 0, isTabAction = 0;
    t_map map = createMapFromFile("../maps/example1.map"), newMap;
    t_localisation robot = loc_init(0, 0, NORTH);


    printf("Bienvenue,\nAvant de vous expliquer votre mission, choisissez la langue dans laquelle vous voulez poursuivre.\n");
    printf("1) Français \n2) English\nChoix :");

    do {
        scanf("%d", &langue);
    } while (langue < 1 || langue > 2);
    if (langue == 1)
        printf("Vous avez choisi Francais.\n");
    else if (langue == 2)
        printf("You have chosen English.\n");


    do {
        switch (langue) {
            case 1:
                printf("Votre mission, si toute fois vous l'acceptez, est de déplacer le robot jusqu'à sa base. \nPour cela vous avez plusieurs possibilités.\n"
                       "1) Créer votre carte pour ramener MARC\n"
                       "2) Afficher la carte pour voir ou se situe le robot\n"
                       "3) Afficher les couts\n"
                       "4) Faire un tirage des actions puis les afficher\n"
                       "5) Choisir l'emplacement du robot\n"
                       "6) Création de l'arbre\n"
                       "7) Afficher l'arbre\n"
                       "8) Déplacement du robot vers la base\n"
                       "9) Fin de la mission\n");
                printf("Choix :");
                do {
                    scanf("%d", &action);
                } while (action < 1 || action > 9);

                switch (action) {
                    case 1:
                        printf("Vous avez choisi créer votre carte pour ramener MARC.\n"
                               "Attention ! Si la taille est supérieur à 15x15, alors l'interface ne sera pas visible.\n"
                               "1) Une carte de taille supérieur à 15x15 mais sans visibilité (sans interface)\n");
                        int colum, row;

                        printf("Donnez le nombre de colonnes :");
                        do {
                            scanf("%d", &colum);
                        } while (colum <= 0);
                        printf("Donnez le nombre de lignes :");
                        do {
                            scanf("%d", &row);
                        } while (row <= 0);

                        new_map(colum, row);
                        newMap = createMapFromFile("../maps/new_map.map");
                        isNewMap = 1;
                        break;


                    case 2:
                        printf("Vous avez choisi d'afficher la carte\n");
                        if (isNewMap == 1) {
                            printf("Quelle map voulez-vous afficher ?\n"
                                   "1) La map de base\n"
                                   "2) La nouvelle map\n"
                                   "Choix :");
                            int choixMap;
                            do {
                                scanf("%d", &choixMap);
                            } while (choixMap < 1 || choixMap > 2);
                            switch (choixMap) {
                                case 1:
                                    displayMap(map);
                                    break;
                                case 2:
                                    displayMap(newMap);
                                    break;
                            }
                        } else
                            displayMap(map);
                        break;

                    case 3:
                        printf("Vous avez choisi d'afficher les coûts\n");
                        if (isNewMap == 1) {
                            printf("De quelle map voulez-vous afficher les coûts?\n"
                                   "1) La map de base\n"
                                   "2) La nouvelle map\n"
                                   "Choix :");
                            int choixMap;
                            do {
                                scanf("%d", &choixMap);
                            } while (choixMap < 1 || choixMap > 2);
                            switch (choixMap) {
                                case 1:
                                    displayCost(map);
                                    break;
                                case 2:
                                    displayCost(newMap);
                                    break;
                            }
                        } else
                            displayCost(map);
                        break;

                    case 4:
                        printf("Vous avez choisi de faire un tirage des actions puis les afficher\n");
                        t_move *tabAction = tirage_aleatoire_adaptatif();
                        displayMoveTab(tabAction);
                        isTabAction = 1;
                        break;

                    case 5:
                        printf("Vous avez choisi de définir l'emplacement du robot\n");
                        int x_robot, y_robot, ori_robot;
                        if (isNewMap == 1) {
                            printf("Quelle map voulez-vous utiliser ?\n"
                                   "1) La map de base\n"
                                   "2) La nouvelle map\n"
                                   "Choix :");
                            int choixMap;
                            do {
                                scanf("%d", &choixMap);
                            } while (choixMap < 1 || choixMap > 2);
                            switch (choixMap) {
                                case 1:
                                    printf("À quelle ligne voulez-vous placer le robot ? :");
                                    do {
                                        scanf("%d", &x_robot);
                                    } while (x_robot <= 0 || x_robot >= map.y_max);
                                    printf("À quelle colonne voulez-vous placer le robot ? :");
                                    do {
                                        scanf("%d", &y_robot);
                                    } while (y_robot <= 0 || y_robot >= map.x_max);
                                    printf("Dans quelle direction voulez-vous placer le robot ?\n"
                                           "1) Nord\n"
                                           "2) Est\n"
                                           "3) Sud\n"
                                           "4) Ouest\n"
                                           "Choix :");
                                    do {
                                        scanf("%d", &ori_robot);
                                    } while (ori_robot < 1 || ori_robot > 4);
                                    switch (ori_robot) {
                                        case 1:
                                            robot = loc_init(x_robot - 1, y_robot - 1, NORTH);
                                            break;
                                        case 2:
                                            robot = loc_init(x_robot - 1, y_robot - 1, EAST);
                                            break;
                                        case 3:
                                            robot = loc_init(x_robot - 1, y_robot - 1, SOUTH);
                                            break;
                                        case 4:
                                            robot = loc_init(x_robot - 1, y_robot - 1, WEST);
                                            break;
                                    }
                                    break;
                                case 2:
                                    printf("À quelle ligne voulez-vous placer le robot ? :");
                                    do {
                                        scanf("%d", &x_robot);
                                    } while (x_robot <= 0 || x_robot >= newMap.y_max);
                                    printf("À quelle colonne voulez-vous placer le robot ? :");
                                    do {
                                        scanf("%d", &y_robot);
                                    } while (y_robot <= 0 || y_robot >= newMap.x_max);
                                    printf("Dans quelle direction voulez-vous placer le robot ?\n"
                                           "1) Nord\n"
                                           "2) Est\n"
                                           "3) Sud\n"
                                           "4) Ouest\n"
                                           "Choix :");
                                    do {
                                        scanf("%d", &ori_robot);
                                    } while (ori_robot < 1 || ori_robot > 4);
                                    switch (ori_robot) {
                                        case 1:
                                            robot = loc_init(x_robot - 1, y_robot - 1, NORTH);
                                            break;
                                        case 2:
                                            robot = loc_init(x_robot - 1, y_robot - 1, EAST);
                                            break;
                                        case 3:
                                            robot = loc_init(x_robot - 1, y_robot - 1, SOUTH);
                                            break;
                                        case 4:
                                            robot = loc_init(x_robot - 1, y_robot - 1, WEST);
                                            break;
                                    }
                                    break;
                            }
                        } else {
                            printf("À quelle ligne voulez-vous placer le robot ? :");
                            do {
                                scanf("%d", &x_robot);
                            } while (x_robot <= 0 || x_robot >= map.y_max);
                            printf("À quelle colonne voulez-vous placer le robot ? :");
                            do {
                                scanf("%d", &y_robot);
                            } while (y_robot <= 0 || y_robot >= map.x_max);
                            printf("Dans quelle direction voulez-vous placer le robot ?\n"
                                   "1) Nord\n"
                                   "2) Est\n"
                                   "3) Sud\n"
                                   "4) Ouest\n"
                                   "Choix :");
                            do {
                                scanf("%d", &ori_robot);
                            } while (ori_robot < 1 || ori_robot > 4);
                            switch (ori_robot) {
                                case 1:
                                    robot = loc_init(x_robot - 1, y_robot - 1, NORTH);
                                    break;
                                case 2:
                                    robot = loc_init(x_robot - 1, y_robot - 1, EAST);
                                    break;
                                case 3:
                                    robot = loc_init(x_robot - 1, y_robot - 1, SOUTH);
                                    break;
                                case 4:
                                    robot = loc_init(x_robot - 1, y_robot - 1, WEST);
                                    break;
                            }
                        }
                        break;

                    case 6:
                        printf("Vous avez choisi de créer l'arbre\n");
                        t_node *new_tree;
                        if (isNewMap == 1) {
                            printf("Quelle map voulez-vous utiliser ?\n"
                                   "1) La map de base\n"
                                   "2) La nouvelle map\n"
                                   "Choix :");
                            int choixMap;
                            do {
                                scanf("%d", &choixMap);
                            } while (choixMap < 1 || choixMap > 2);
                            switch (choixMap) {
                                case 1:
                                    if (isTabAction == 0) {
                                        printf("Vous devez d'abord tirer les actions\n");
                                        break;
                                    }
                                    for (int i = 4; i >= 0; i--) {
                                        start = clock();
                                        new_tree = createTree(map.costs[robot.pos.x][robot.pos.y], 0, 9, i, robot,
                                                              tabAction, map, NULL, -1);
                                        end = clock();
                                        printf("Temps construction de l'arbre avec %d choix : %f\n", 9 - i,
                                               ((double) (end - start)) / CLOCKS_PER_SEC);
                                    }
                                    break;
                                case 2:
                                    if (isTabAction == 0) {
                                        printf("Vous devez d'abord tirer les actions\n");
                                        break;
                                    }
                                    for (int i = 4; i >= 0; i--) {
                                        start = clock();
                                        new_tree = createTree(newMap.costs[robot.pos.x][robot.pos.y], 0, 9, i, robot,
                                                              tabAction, newMap, NULL, -1);
                                        end = clock();
                                        printf("Temps construction de l'arbre avec %d choix : %f\n", 9 - i,
                                               ((double) (end - start)) / CLOCKS_PER_SEC);
                                    }
                                    break;
                            }
                        } else {
                            if (isTabAction == 0) {
                                printf("Vous devez d'abord tirer les actions\n");
                                break;
                            }
                            for (int i = 4; i >= 0; i--) {
                                start = clock();
                                new_tree = createTree(map.costs[robot.pos.x][robot.pos.y], 0, 9, i, robot, tabAction,
                                                      map,NULL, -1);
                                end = clock();
                                printf("Temps construction de l'arbre avec %d choix : %f\n", 9 - i,
                                       ((double) (end - start)) / CLOCKS_PER_SEC);
                            }
                        }
                        break;

                    case 7 :
                        displayTree(new_tree, 0, 1);
                        break;

                    case 8:
                        printf("Vous avez choisi de déplacer le robot vers la base\n");

                        printf("Quelle map voulez-vous utiliser ?\n"
                               "1) La map de base\n"
                               "2) La nouvelle map\n"
                               "Choix :");
                        int choixMap;
                        do {
                            scanf("%d", &choixMap);
                        } while (choixMap < 1 || choixMap > 2);
                        t_map mapInterface;
                        switch (choixMap) {
                            case 1:
                                mapInterface = map;
                                break;
                            case 2:
                                mapInterface = newMap;
                                break;
                        }

                        do {
                            t_node *maxnode = createRoot(INT_MAX, 0);
                            start = clock();
                            t_node *mini_node = findMinNode(new_tree, 0, 9, maxnode);
                            end = clock();
                            printf("Temps de recherche de la feuille minimale : %f\n", ((double) (end - start)) / CLOCKS_PER_SEC);

                            start = clock();
                            t_stack stack = path_min_choices(mini_node);
                            end = clock();
                            printf("Temps de recherche du chemin optimal : %f\n", ((double) (end - start)) / CLOCKS_PER_SEC);
                            if (mapInterface.x_max <= 15 && mapInterface.y_max <= 15) {
                                int width = mapInterface.x_max;
                                int height = mapInterface.y_max;

                                // Initialisation de SDL
                                SDL_Init(SDL_INIT_VIDEO);
                                SDL_Window *window = SDL_CreateWindow("Carte Mars", SDL_WINDOWPOS_CENTERED,
                                                                      SDL_WINDOWPOS_CENTERED, width * TILE_SIZE,
                                                                      height * TILE_SIZE, SDL_WINDOW_SHOWN);
                                SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

                                // Charger les images pour chaque type de terrain
                                textures[BASE_STATION] = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP(
                                        "../Skins/Base_1.bmp"));
                                textures[PLAIN] = SDL_CreateTextureFromSurface(renderer,
                                                                               SDL_LoadBMP("../Skins/Plain.bmp"));
                                textures[ERG] = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("../Skins/Erg.bmp"));
                                textures[REG] = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("../Skins/Reg.bmp"));
                                textures[CREVASSE] = SDL_CreateTextureFromSurface(renderer,
                                                                                  SDL_LoadBMP("../Skins/Crevasse.bmp"));

                                // Charger l'image du robot
                                robotTexture = SDL_CreateTextureFromSurface(renderer,
                                                                            SDL_LoadBMP("../Skins/Robot.bmp"));

                                int running = 1;

                                SDL_Event event;


                                while (running && stack.nbElts != 0) {
                                    // Gestion des événements
                                    while (SDL_PollEvent(&event)) {
                                        if (event.type == SDL_QUIT) running = 0;
                                    }

                                    // Effacer l'écran
                                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Fond blanc
                                    SDL_RenderClear(renderer);

                                    // Dessiner la carte
                                    for (int y = 0; y < height; y++) {
                                        for (int x = 0; x < width; x++) {
                                            drawTile(renderer, x, y, mapInterface.soils[y][x]);
                                        }
                                    }

                                    // Déplacer le robot
                                    updateLocalisation(&robot, pop(&stack));

                                    // Dessiner le robot par-dessus la carte
                                    drawRobot(renderer, robot);

                                    // Afficher la scène
                                    SDL_RenderPresent(renderer);

                                    // Attendre un peu pour voir le mouvement
                                    SDL_Delay(1000); // 2000 ms

                                }

                                // Libérer les textures
                                for (int i = 0; i < 5; i++) {
                                    SDL_DestroyTexture(textures[i]);
                                }
                                SDL_DestroyTexture(robotTexture);

                                SDL_DestroyRenderer(renderer);
                                SDL_DestroyWindow(window);
                                SDL_Quit();
                            } else {
                                do {
                                    updateLocalisation(&robot, pop(&stack));
                                } while (stack.nbElts != 0);
                                printf("Le robot est à la position (%d, %d) et est orienté vers le ", robot.pos.x + 1, robot.pos.y + 1);
                                switch (robot.ori) {
                                    case NORTH:
                                        printf("Nord\n");
                                        break;
                                    case EAST:
                                        printf("Est\n");
                                        break;
                                    case SOUTH:
                                        printf("Sud\n");
                                        break;
                                    case WEST:
                                        printf("Ouest\n");
                                        break;
                                }
                                if (mapInterface.costs[robot.pos.x][robot.pos.y] == 0)
                                    printf("Le robot est bien à sa base\n");
                                else
                                    printf("Le robot n'est pas à sa base\n");
                            }
                            createTree(mapInterface.costs[robot.pos.x][robot.pos.y], 0, 9, 0, robot, tabAction,
                                       mapInterface, NULL, -1);
                            tabAction = tirage_aleatoire_adaptatif();
                        } while (mapInterface.costs[robot.pos.x][robot.pos.y] != 0);
                        break;

                    case 9:
                        fin = 1;
                        break;
                }
                break;

            case 2 :
                printf("Your mission, if you accept it, is to move the robot to its base. \nThere are several ways of doing this.\n"
                       "1) Create your card to bring MARC back\n"
                       "2) Display the map to see where the robot is located\n"
                       "3) Show costs\n"
                       "4) Draw the actions and display them\n"
                       "5) Choosing a location for the robot\n"
                       "6) Creating the tree\n"
                       "7) Display tree\n"
                       "8) Moving the robot towards the base\n"
                       "9) End of mission\n");
                printf("Choice :");
                do {
                    scanf("%d", &action);
                } while (action < 1 || action > 9);

                switch (action) {
                    case 1:
                        printf("You have chosen to create your card to bring back MARC.\n"
                               "Warning! If the size is greater than 15x15, then the interface will not be visible."
                               "1) A card larger than 15x15 but without visibility (no interface)");
                        int colum, row;

                        printf("Enter the number of columns :");
                        do {
                            scanf("%d", &colum);
                        } while (colum <= 0);
                        printf("Enter the number of columns :");
                        do {
                            scanf("%d", &row);
                        } while (row <= 0);

                        new_map(colum, row);
                        newMap = createMapFromFile("../maps/new_map.map");
                        isNewMap = 1;
                        break;


                    case 2:
                        printf("You have chosen to display the map\n");
                        if (isNewMap == 1) {
                            printf("Which map do you want to display?\n"
                                   "1) The basic map\n"
                                   "2) The new map\n"
                                   "Choice :");
                            int choixMap;
                            do {
                                scanf("%d", &choixMap);
                            } while (choixMap < 1 || choixMap > 2);
                            switch (choixMap) {
                                case 1:
                                    displayMap(map);
                                    break;
                                case 2:
                                    displayMap(newMap);
                                    break;
                            }
                        } else
                            displayMap(map);
                        break;

                    case 3:
                        printf("You have chosen to display costs\n");
                        if (isNewMap == 1) {
                            printf("Which map do you want to display the costs for?\n"
                                   "1) The basic map\n"
                                   "2) The new map\n"
                                   "Choice :");
                            int choixMap;
                            do {
                                scanf("%d", &choixMap);
                            } while (choixMap < 1 || choixMap > 2);
                            switch (choixMap) {
                                case 1:
                                    displayCost(map);
                                    break;
                                case 2:
                                    displayCost(newMap);
                                    break;
                            }
                        } else
                            displayCost(map);
                        break;

                    case 4:
                        printf("You have chosen to draw stocks and then display them\n");
                        t_move *tabAction = tirage_aleatoire_adaptatif();
                        isTabAction = 1;
                        break;

                    case 5:
                        printf("You have chosen to define the location of the robot\n");
                        int x_robot, y_robot, ori_robot;
                        if (isNewMap == 1) {
                            printf("Which map do you want to use ?\n"
                                   "1) The basic map\n"
                                   "2) The new map\n"
                                   "Choice :");
                            int choixMap;
                            do {
                                scanf("%d", &choixMap);
                            } while (choixMap < 1 || choixMap > 2);
                            switch (choixMap) {
                                case 1:
                                    printf("On which line do you want to place the robot ? :");
                                    do {
                                        scanf("%d", &x_robot);
                                    } while (x_robot <= 0 || x_robot >= map.y_max);
                                    printf("To which column do you want to place the robot ? :");
                                    do {
                                        scanf("%d", &y_robot);
                                    } while (y_robot <= 0 || y_robot >= map.x_max);
                                    printf("In which direction do you want to position the robot ?\n"
                                           "1) North\n"
                                           "2) East\n"
                                           "3) South\n"
                                           "4) West\n"
                                           "Choice :");
                                    do {
                                        scanf("%d", &ori_robot);
                                    } while (ori_robot < 1 || ori_robot > 4);
                                    switch (ori_robot) {
                                        case 1:
                                            robot = loc_init(x_robot - 1, y_robot - 1, NORTH);
                                            break;
                                        case 2:
                                            robot = loc_init(x_robot - 1, y_robot - 1, EAST);
                                            break;
                                        case 3:
                                            robot = loc_init(x_robot - 1, y_robot - 1, SOUTH);
                                            break;
                                        case 4:
                                            robot = loc_init(x_robot - 1, y_robot - 1, WEST);
                                            break;
                                    }
                                    break;
                                case 2:
                                    printf("On which line do you want to place the robot ? :");
                                    do {
                                        scanf("%d", &x_robot);
                                    } while (x_robot <= 0 || x_robot >= newMap.y_max);
                                    printf("To which column do you want to place the robot ? :");
                                    do {
                                        scanf("%d", &y_robot);
                                    } while (y_robot <= 0 || y_robot >= newMap.x_max);
                                    printf("In which direction do you want to position the robot ?\n"
                                           "1) North\n"
                                           "2) East\n"
                                           "3) South\n"
                                           "4) West\n"
                                           "Choice :");
                                    do {
                                        scanf("%d", &ori_robot);
                                    } while (ori_robot < 1 || ori_robot > 4);
                                    switch (ori_robot) {
                                        case 1:
                                            robot = loc_init(x_robot - 1, y_robot - 1, NORTH);
                                            break;
                                        case 2:
                                            robot = loc_init(x_robot - 1, y_robot - 1, EAST);
                                            break;
                                        case 3:
                                            robot = loc_init(x_robot - 1, y_robot - 1, SOUTH);
                                            break;
                                        case 4:
                                            robot = loc_init(x_robot - 1, y_robot - 1, WEST);
                                            break;
                                    }
                                    break;
                            }
                        } else {
                            printf("On which line do you want to place the robot ? :");
                            do {
                                scanf("%d", &x_robot);
                            } while (x_robot <= 0 || x_robot >= map.y_max);
                            printf("To which column do you want to place the robot ? :");
                            do {
                                scanf("%d", &y_robot);
                            } while (y_robot <= 0 || y_robot >= map.x_max);
                            printf("In which direction do you want to position the robot ?\n"
                                   "1) North\n"
                                   "2) East\n"
                                   "3) South\n"
                                   "4) West\n"
                                   "Choice :");
                            do {
                                scanf("%d", &ori_robot);
                            } while (ori_robot < 1 || ori_robot > 4);
                            switch (ori_robot) {
                                case 1:
                                    robot = loc_init(x_robot - 1, y_robot - 1, NORTH);
                                    break;
                                case 2:
                                    robot = loc_init(x_robot - 1, y_robot - 1, EAST);
                                    break;
                                case 3:
                                    robot = loc_init(x_robot - 1, y_robot - 1, SOUTH);
                                    break;
                                case 4:
                                    robot = loc_init(x_robot - 1, y_robot - 1, WEST);
                                    break;
                            }
                        }
                        break;

                    case 6:
                        printf("You have chosen to create the tree\n");
                        t_node *new_tree;
                        if (isNewMap == 1) {
                            printf("Which map do you want to use ?\n"
                                   "1) The basic map\n"
                                   "2) The new map\n"
                                   "Choice :");
                            int choixMap;
                            do {
                                scanf("%d", &choixMap);
                            } while (choixMap < 1 || choixMap > 2);
                            switch (choixMap) {
                                case 1:
                                    if (isTabAction == 0) {
                                        printf("First you need to draw up the actions\n");
                                        break;
                                    }
                                    for (int i = 4; i >= 0; i--) {
                                        start = clock();
                                        new_tree = createTree(map.costs[robot.pos.x][robot.pos.y], 0, 9, i, robot,
                                                              tabAction, map, NULL, -1);
                                        end = clock();
                                        printf("Tree construction time with %d choices : %f\n", 9 - i,
                                               ((double) (end - start)) / CLOCKS_PER_SEC);
                                    }
                                    break;
                                case 2:
                                    if (isTabAction == 0) {
                                        printf("First you need to draw up the actions\n");
                                        break;
                                    }
                                    for (int i = 4; i >= 0; i--) {
                                        start = clock();
                                        new_tree = createTree(newMap.costs[robot.pos.x][robot.pos.y], 0, 9, i, robot,
                                                              tabAction, newMap, NULL, -1);
                                        end = clock();
                                        printf("Tree construction time with %d choices : %f\n", 9 - i,
                                               ((double) (end - start)) / CLOCKS_PER_SEC);
                                    }
                                    break;
                            }
                        } else {
                            if (isTabAction == 0) {
                                printf("First you need to draw up the actions\n");
                                break;
                            }
                            for (int i = 4; i >= 0; i--) {
                                start = clock();
                                new_tree = createTree(map.costs[robot.pos.x][robot.pos.y], 0, 9, i, robot, tabAction,
                                                      map, NULL, -1);
                                end = clock();
                                printf("Tree construction time with %d choices : %f\n", 9 - i,
                                       ((double) (end - start)) / CLOCKS_PER_SEC);
                            }
                        }
                        break;

                    case 7 :
                        displayTree(new_tree, 0, 1);
                        break;

                    case 8:
                        printf("You have chosen to move the robot to the base\n");

                        printf("Which map do you want to use ?\n"
                               "1) The basic map\n"
                               "2) The new map\n"
                               "Choice :");
                        int choixMap;
                        do {
                            scanf("%d", &choixMap);
                        } while (choixMap < 1 || choixMap > 2);
                        t_map mapInterface;
                        switch (choixMap) {
                            case 1:
                                mapInterface = map;
                                break;
                            case 2:
                                mapInterface = newMap;
                                break;
                        }

                        do {
                            t_node *maxnode = createRoot(INT_MAX, 0);
                            start = clock();
                            t_node *mini_node = findMinNode(new_tree, 0, 9, maxnode);
                            end = clock();
                            printf("Minimum sheet search time : %f\n", ((double) (end - start)) / CLOCKS_PER_SEC);

                            start = clock();
                            t_stack stack = path_min_choices(mini_node);
                            end = clock();
                            printf("Optimum path search time : %f\n", ((double) (end - start)) / CLOCKS_PER_SEC);
                            if (mapInterface.x_max <= 15 && mapInterface.y_max <= 15) {
                                int width = mapInterface.x_max;
                                int height = mapInterface.y_max;

                                // Initialisation de SDL
                                SDL_Init(SDL_INIT_VIDEO);
                                SDL_Window *window = SDL_CreateWindow("Mars Map", SDL_WINDOWPOS_CENTERED,
                                                                      SDL_WINDOWPOS_CENTERED, width * TILE_SIZE,
                                                                      height * TILE_SIZE, SDL_WINDOW_SHOWN);
                                SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

                                // Charger les images pour chaque type de terrain
                                textures[BASE_STATION] = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP(
                                        "../Skins/Base_1.bmp"));
                                textures[PLAIN] = SDL_CreateTextureFromSurface(renderer,
                                                                               SDL_LoadBMP("../Skins/Plain.bmp"));
                                textures[ERG] = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("../Skins/Erg.bmp"));
                                textures[REG] = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("../Skins/Reg.bmp"));
                                textures[CREVASSE] = SDL_CreateTextureFromSurface(renderer,
                                                                                  SDL_LoadBMP("../Skins/Crevasse.bmp"));

                                // Charger l'image du robot
                                robotTexture = SDL_CreateTextureFromSurface(renderer,
                                                                            SDL_LoadBMP("../Skins/Robot.bmp"));

                                int running = 1;

                                SDL_Event event;


                                while (running && stack.nbElts != 0) {
                                    // Gestion des événements
                                    while (SDL_PollEvent(&event)) {
                                        if (event.type == SDL_QUIT) running = 0;
                                    }

                                    // Effacer l'écran
                                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Fond blanc
                                    SDL_RenderClear(renderer);

                                    // Dessiner la carte
                                    for (int y = 0; y < height; y++) {
                                        for (int x = 0; x < width; x++) {
                                            drawTile(renderer, x, y, mapInterface.soils[y][x]);
                                        }
                                    }

                                    // Déplacer le robot
                                    updateLocalisation(&robot, pop(&stack));

                                    // Dessiner le robot par-dessus la carte
                                    drawRobot(renderer, robot);

                                    // Afficher la scène
                                    SDL_RenderPresent(renderer);

                                    // Attendre un peu pour voir le mouvement
                                    SDL_Delay(1000); // 2000 ms

                                }

                                // Libérer les textures
                                for (int i = 0; i < 5; i++) {
                                    SDL_DestroyTexture(textures[i]);
                                }
                                SDL_DestroyTexture(robotTexture);

                                SDL_DestroyRenderer(renderer);
                                SDL_DestroyWindow(window);
                                SDL_Quit();
                            } else {
                                do {
                                    updateLocalisation(&robot, pop(&stack));
                                } while (stack.nbElts != 0);
                                printf("The robot is at position (%d, %d) and is oriented towards the ", robot.pos.x,
                                       robot.pos.y);
                                switch (robot.ori) {
                                    case NORTH:
                                        printf("North\n");
                                        break;
                                    case EAST:
                                        printf("East\n");
                                        break;
                                    case SOUTH:
                                        printf("South\n");
                                        break;
                                    case WEST:
                                        printf("West\n");
                                        break;
                                }
                                if (mapInterface.costs[robot.pos.x][robot.pos.y] == 0)
                                    printf("The robot is at its base\n");
                                else
                                    printf("The robot is not at its base\n");
                            }
                            createTree(mapInterface.costs[robot.pos.x][robot.pos.y], 0, 9, 0, robot, tabAction,
                                       mapInterface, NULL, -1);
                        } while (mapInterface.costs[robot.pos.x][robot.pos.y] != 0);
                        break;

                    case 9:
                        fin = 1;
                        break;
                }
                break;
        }
    } while (fin != 1);

    return 0;
}