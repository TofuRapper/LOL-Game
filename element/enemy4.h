#ifndef enemy4_H_INCLUDED
#define enemy4_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [enemy4 object]
*/
typedef struct _enemy4
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
    int blood;
} enemy4;
Elements *New_enemy4(int label,int x);
void enemy4_update(Elements *self);
void enemy4_interact(Elements *self, Elements *tar);
void enemy4_draw(Elements *self);
void enemy4_destory(Elements *self);
void _enemy4_update_position(Elements *self, int dx, int dy);

#endif
