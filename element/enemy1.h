#ifndef Enemy_H_INCLUDED
#define Enemy_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [enemy object]
*/
typedef struct _enemy
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
    int blood;
} enemy;
Elements *New_enemy(int label,int x);
void enemy_update(Elements *self);
void enemy_interact(Elements *self, Elements *tar);
void enemy_draw(Elements *self);
void enemy_destroy(Elements *self);
void _enemy_update_position(Elements *self, int dx, int dy);

#endif
