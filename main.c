#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "map.h"
#include "moves.h"
#include "tree_functions.h"
#include <limits.h>
#include "SDL.h"




int main() {
    clock_t start, end;
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
    t_localisation robot = loc_init(3, 4, EAST);

    /// Initialisation de l'enchaînement d'action
    t_move tabAction[5] = {F_10, F_20, F_30, T_LEFT, T_RIGHT };
//    t_move tabActionleft[1] = {T_LEFT};

//    t_move * tabAction = tirage_aleatoire_adaptatif();



    /// Création de l'arbre des chemins empreintés (3 choix/profondeur)
    int value = map.costs[robot.pos.x][robot.pos.y];
    start = clock();
    t_node *new_tree = createTree(value, 0, 9, 0, robot, tabAction, map, NULL, -1);
    end = clock();

    /// Affichage de l'arbre des chemins empreintés
//    displayTree(new_tree, 0, 1);


//    t_node *mini_node = findMin(new_tree, 0, 9, INT_MAX);
    t_node *maxnode = createRoot(INT_MAX, 0);
    t_node *mini_node = findMinNode(new_tree, 0, 9, maxnode);

    printf("Minimum : %d\n", mini_node->value);
    t_stack stack = path_min_choices( mini_node);

    for (int i = 4; i >= 0; i--) {
        start = clock();
        t_node *new_tree = createTree(value, 0, 9, i, robot, tabAction, map, NULL, -1);
        end = clock();
        printf("Temps construction de l'arbre avec %d choix : %f\n", 9 - i, ((double) (end - start)) / CLOCKS_PER_SEC);
    }

    int width = map.x_max;
    int height = map.y_max;

    // Initialisation de SDL
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Carte Mars", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width * TILE_SIZE, height * TILE_SIZE, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Charger les images pour chaque type de terrain
    textures[BASE_STATION] = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("../Skins/Base_1.bmp"));
    textures[PLAIN] = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("../Skins/Plain.bmp"));
    textures[ERG] = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("../Skins/Erg.bmp"));
    textures[REG] = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("../Skins/Reg.bmp"));
    textures[CREVASSE] = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("../Skins/Crevasse.bmp"));

    // Charger l'image du robot
    robotTexture = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("../Skins/Robot.bmp"));

    int running = 1;

    SDL_Event event;


    while (running && stack.nbElts!=0) {
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
                drawTile(renderer, x, y, map.soils[y][x]);
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


    int langue, fin = 0;
    printf("Bienvenue,\nAvant de vous expliquer votre mission, choisissez la langue dans laquelle vous voulez poursuivre.\n");
    printf("1) English \n2) Francais\nChoix :");

    do {
        scanf("%d", &langue);
    } while (langue < 1 || langue > 2);
    if (langue == 1)
        printf("You have chosen English.\n");
    else if (langue == 2)
        printf("Vous avez choisi Francais.\n");

    do {
        switch (langue) {
            case 1:

                printf("Votre mission, si toute fois vous l'acceptez, est de déplacer le robot jusqu'à sa base. \nPour cela vous avez plusieurs possibilités.\n");
                printf("1) Créer votre carte pour ramener MARC\n");
                printf("2) Afficher la carte pour voir ou se situe le robot\n");
                printf("3) Afficher les couts\n");
                printf("4) Faire un tirage des actions puis les afficher\n");
                printf("5)\n");
                printf("6) Choisir l'emplacement du robot\n");
                printf("7) Fin de la mission\n");
                printf("Choix :");
                int action, isNewMap = 0;
                do {
                    scanf("%d", &action);
                } while (action < 1 || action > 7);
                t_map map = createMapFromFile("../maps/example1.map"), newMap;
                t_localisation robot;


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
                        do{
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
                            displayMap(newMap);
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
                        tirage_aleatoire_adaptatif();
                        break;

                    case 5:
                        break;

                    case 6:
                        printf("Vous avez choisi de définir l'emplacement du robot\n");
                        printf("À quelle ligne voulez-vous placer le robot ? :");
                        int x_robot;
                        do {
                            scanf("%d", &x_robot);
                        } while (x_robot <= 0 || x_robot >= map.y_max);
                        printf("À quelle colonne voulez-vous placer le robot ? :");
                        int y_robot;
                        do {
                            scanf("%d", &y_robot);
                        } while (y_robot <= 0 || y_robot >= map.x_max);
                        int ori_robot;
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

                    case 7:
                        fin = 1;
                        break;
                }
            case 2 :

                printf("Your mission, if you accept it, is to move the robot to its base.\nThere are several ways of doing this.\n");
                printf("1) Create your card to bring MARC back\n");
                printf("2) Display the map to see where the robot is located\n");
                printf("3) Show costs\n");
                printf("4) Draw the actions and display them\n");
                printf("5)\n");
                printf("6) Choosing a location for the robot\n");
                printf("7) End of the mission\n");
                int action, isNewMap = 0;
                do {
                    scanf("%d", &action);
                } while (action < 1 || action > 7);
                t_map map = createMapFromFile("../maps/example1.map"), newMap;
                t_localisation robot;


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
                        do{
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
                            displayMap(newMap);
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
                        tirage_aleatoire_adaptatif();
                        break;

                    case 5:
                        break;

                    case 6:
                        printf("You have chosen to define the location of the robot\n");
                        printf("On which row do you want to place the robot ? :");
                        int x_robot;
                        do {
                            scanf("%d", &x_robot);
                        } while (x_robot <= 0 || x_robot >= map.y_max);
                        printf("On which column do you want to place the robot ? :");
                        int y_robot;
                        do {
                            scanf("%d", &y_robot);
                        } while (y_robot <= 0 || y_robot >= map.x_max);
                        int ori_robot;
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

                    case 7:
                        fin = 1;
                break;
        }

    } while (fin != 1);





    
    return 0;
}
