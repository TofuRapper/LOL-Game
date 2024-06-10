#ifndef GAMESCENE_H_INCLUDED
#define GAMESCENE_H_INCLUDED
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include "scene.h"
#include "../element/element.h"
#include "../element/charater.h"
#include "../element/floor.h"
#include "../element/teleport.h"
#include "../element/projectile.h"
#include "../element/enemy1.h"
#include "../element/enemy2.h"
#include "../element/enemy3.h"
#include "../element/enemy4.h"
/*
   [game scene object]
*/
typedef enum EleType
{
    Floor_L,
    Teleport_L,
    Character_L,
    Projectile_L,
    Enemy_L,
    Enemy2_L,
    Enemy3_L,
    Enemy4_L
} EleType;
typedef struct _GameScene
{
    ALLEGRO_FONT *font;
    int title_x, title_y;
    ALLEGRO_BITMAP *background;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    ALLEGRO_SAMPLE *song;
} GameScene;
Scene *New_GameScene(int label);
void game_scene_update(Scene *self);
void game_scene_draw(Scene *self);
void game_scene_destroy(Scene *self);

#endif
