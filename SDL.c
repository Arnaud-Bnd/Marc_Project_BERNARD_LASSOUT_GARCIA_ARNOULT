//
// Created by Marc-Antoine on 13/11/2024.
//

#include "SDL.h"

// Fonction pour dessiner une case avec une texture
void drawTile(SDL_Renderer *renderer, int x, int y, t_soil type) {
    SDL_Rect tileRect = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
    SDL_RenderCopy(renderer, textures[type], NULL, &tileRect);
}

// Fonction pour dessiner le robot
void drawRobot(SDL_Renderer *renderer, t_localisation loc) {
    SDL_Rect robotRect = { loc.pos.x * TILE_SIZE, loc.pos.y * TILE_SIZE, TILE_SIZE, TILE_SIZE };

    // Déterminer l'angle de rotation en fonction de l'orientation du robot
    int angle = 0;
    switch (loc.ori) {
        case NORTH:
            angle = 0;  // Pas de rotation
            break;
        case EAST:
            angle = 90; // Rotation de 90 degrés (vers l'Est)
            break;
        case SOUTH:
            angle = 180; // Rotation de 180 degrés (vers le Sud)
            break;
        case WEST:
            angle = 270; // Rotation de 270 degrés (vers l'Ouest)
            break;
    }

    // Dessiner le robot avec la rotation calculée
    SDL_RenderCopyEx(renderer, robotTexture, NULL, &robotRect, angle, NULL, SDL_FLIP_NONE);
}
