#ifndef enemy3_H_INCLUDED
#define enemy3_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [enemy3 object]
*/
typedef struct _enemy3
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
    int blood;
} enemy3;
Elements *New_enemy3(int label,int x);
void enemy3_update(Elements *self);
void enemy3_interact(Elements *self, Elements *tar);
void enemy3_draw(Elements *self);
void enemy3_destory(Elements *self);
void _enemy3_update_position(Elements *self, int dx, int dy);

#endif
