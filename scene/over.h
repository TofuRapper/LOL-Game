#ifndef Over_H_INCLUDED
#define Over_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [Over object]
*/
typedef struct _Over
{
    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    ALLEGRO_BITMAP * background;
    int title_x, title_y;
} Over;
Scene *New_Over(int label);
void Over_update(Scene *self);
void Over_draw(Scene *self);
void Over_destroy(Scene *self);

#endif
