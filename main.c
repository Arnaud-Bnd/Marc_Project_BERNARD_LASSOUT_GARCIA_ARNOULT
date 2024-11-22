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
//    t_move tabAction[5] = {F_10, F_20, F_30, T_LEFT, T_RIGHT };
//    t_move tabActionleft[1] = {T_LEFT};

    t_move * tabAction = tirage_aleatoire_adaptatif();



    /// Création de l'arbre des chemins empreintés (3 choix/profondeur)
    int value = map.costs[robot.pos.x][robot.pos.y];
    printf("x_max = %d\n", map.x_max);
    start = clock();
    t_node *new_tree = createTree(value, 0, 9, 0, robot, tabAction, map, NULL, -1);
    end = clock();

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
    t_node *maxnode = createRoot(INT_MAX, 0);
    t_node *mini_node = findMinNode(new_tree, 0, 9, maxnode);

    printf("Minimum : %d\n", mini_node->value);
    t_stack stack = path_min_choices( mini_node);


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
    return 0;
}
