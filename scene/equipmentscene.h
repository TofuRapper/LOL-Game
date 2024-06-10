#ifndef EQUIPMENTSCENE_H_INCLUDED
#define EQUIPMENTSCENE_H_INCLUDED

#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

/*
   [EquipmentScene object]
*/
typedef struct _equipmentscene
{
    ALLEGRO_FONT *font;
    ALLEGRO_BITMAP *background;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_BITMAP *sword;
    ALLEGRO_BITMAP *shield;
    ALLEGRO_BITMAP *other;
    int selected_equipment;
    int title_x, title_y;
} EquipmentScene;

Scene *New_EquipmentScene(int label);
void equipment_update(Scene *self);
void equipment_draw(Scene *self);
void equipment_destroy(Scene *self);

#endif
