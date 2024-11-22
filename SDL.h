//
// Created by Marc-Antoine on 13/11/2024.
//

#ifndef MARC_PROJECT_BERNARD_LASSOUT_GARCIA_ARNOULT_SDL_H
#define MARC_PROJECT_BERNARD_LASSOUT_GARCIA_ARNOULT_SDL_H

#define TILE_SIZE 100// Taille d'une case en pixels
#include <SDL2/SDL.h>
#include "tree_functions.h"


// Déclarations des textures
SDL_Texture* textures[5];
SDL_Texture* robotTexture;  // Texture du robot


void drawTile(SDL_Renderer *renderer, int x, int y, t_soil type);
void drawRobot(SDL_Renderer *renderer, t_localisation loc) ;



#endif //MARC_PROJECT_BERNARD_LASSOUT_GARCIA_ARNOULT_SDL_H
