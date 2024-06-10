#ifndef win_H_INCLUDED
#define win_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [win object]
*/
typedef struct _win
{
    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    ALLEGRO_BITMAP * background;
    int title_x, title_y;
} winner;
Scene *New_winner(int label);
void winner_update(Scene *self);
void winner_draw(Scene *self);
void winner_destroy(Scene *self);

#endif
