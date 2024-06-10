#include "gamescene.h"
#include "../element/enemy1.h"
#include <stdlib.h>
#include "../shapes/Rectangle.h"
#include <allegro5/allegro_primitives.h>
#include <time.h>
#include <stdbool.h>
#include "equipmentscene.h"

/*
   [GameScene function]
*/
Scene *New_GameScene(int label)
{
    GameScene *pDerivedObj = (GameScene *)malloc(sizeof(GameScene));
    Scene *pObj = New_Scene(label);

    // Load sound
    pDerivedObj->song = al_load_sample("assets/sound/music.mp3");

    // Create a sample instance
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);

    // Loop the song until the display closes
    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    if (!al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer())) {
        return NULL;
    }

    // Set the volume of the instance
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 0.5);
    // Setting derived object member
    pDerivedObj->background = al_load_bitmap("assets/image/stage.jpg");

    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 12, 0);

    pObj->pDerivedObj = pDerivedObj;

    // Register elements
    _Register_elements(pObj, New_Floor(Floor_L));
    _Register_elements(pObj, New_Teleport(Teleport_L));
    srand(time(NULL));
    int x = (rand() % 900);
    pDerivedObj->title_x = WIDTH / 2;
    pDerivedObj->title_y = HEIGHT / 2;
    _Register_elements(pObj, New_enemy(Enemy_L, x));
    _Register_elements(pObj, New_Character(Character_L));

    // Setting derived object functions
    pObj->Update = game_scene_update;
    pObj->Draw = game_scene_draw;
    pObj->Destroy = game_scene_destroy;

    // Play the music
    al_play_sample_instance(pDerivedObj->sample_instance);

    return pObj;
}

/*Scene *New_GameScene(int label)
{
    GameScene *pDerivedObj = (GameScene *)malloc(sizeof(GameScene));
    Scene *pObj = New_Scene(label);
    pDerivedObj->song = al_load_sample("assets/sound/music.mp3");
    al_reserve_samples(20);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    // Loop the song until the display closes
    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 0.5);
    // setting derived object member
    pDerivedObj->background = al_load_bitmap("assets/image/stage.jpg");
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 12, 0);

    pObj->pDerivedObj = pDerivedObj;
    // register element
    _Register_elements(pObj, New_Floor(Floor_L));
    _Register_elements(pObj, New_Teleport(Teleport_L));
    srand(time(NULL));
    int x = (rand()%900);
    pDerivedObj->title_x = WIDTH / 2;
    pDerivedObj->title_y = HEIGHT / 2;
    _Register_elements(pObj, New_enemy(Enemy_L,x));
    _Register_elements(pObj, New_Character(Character_L));
    // setting derived object function
    pObj->Update = game_scene_update;
    pObj->Draw = game_scene_draw;
    pObj->Destroy = game_scene_destroy;
    return pObj;
}*/

unsigned int clk = 500;
unsigned int pause_cooldown = 0;
static char str_health[12]; 
static char str_score[20];

void game_scene_update(Scene *self)
{ 
    GameScene *Obj = ((GameScene *)(self->pDerivedObj));
    clk -= 1;
    if (pause_cooldown > 0) {
        pause_cooldown -= 1;
    }

    if (!pause) {
        t_clock++;
    }

    if (pause) {
        if (key_state[ALLEGRO_KEY_P] && pause_cooldown == 0) {
            pause = false;
            pause_cooldown = 20;  // Cooldown period to prevent immediate re-pause
        }
        if (key_state[ALLEGRO_KEY_B]) {
            self->scene_end = true;
            pause = false;
            t_clock = 0;
            score = 0;
            health = 1000;
            stage = 0;
            window = 0;
        }
        if (key_state[ALLEGRO_KEY_R]) {
            self->scene_end = true;
            pause = false;
            score = 0;
            t_clock = 0;
            stage = 0;
            health = 1000;
            window = 1;
        }
        if (key_state[ALLEGRO_KEY_M] && pause_cooldown == 0) {
            if (al_get_sample_instance_gain(Obj->sample_instance) > 0.0) {
                // Sound is not muted, so mute it
                al_set_sample_instance_gain(Obj->sample_instance, 0.0);  // Mute sound
            } else {
                // Sound is muted, so unmute it
                al_set_sample_instance_gain(Obj->sample_instance, 0.5);  // Unmute sound
            }
            // Avoid toggling the mute state continuously by adding a small delay
            pause_cooldown = 20;
        }
        return;
    }

    if (key_state[ALLEGRO_KEY_P] && pause_cooldown == 0) {
        pause = true;
        pause_cooldown = 20;  // Cooldown period to prevent immediate re-unpause
    }

    if (health <= 0) {
        self->scene_end = true;
        window = 2;
    }

    if (t_clock >= 400) {
        self->scene_end = true;
        t_clock = 0;
        window = 3;
    }

    int randx = (rand() % 800);
    if (clk % 350 == 0) {
        Elements *ene = New_enemy(Enemy_L, randx);
        _Register_elements(self, ene);
        randx = rand() % 800;
        if (stage >= 1) {
            Elements *ene2 = New_enemy2(Enemy2_L, randx);
            _Register_elements(self, ene2);
            randx = (rand() % 800);
        }
        if (stage >= 2) {
            Elements *ene3 = New_enemy3(Enemy3_L, randx);
            _Register_elements(self, ene3);
            randx = (rand() % 800);
        }
        if (stage >= 3) {
            Elements *ene4 = New_enemy4(Enemy4_L, randx);
            _Register_elements(self, ene4);
        }
        if (clk <= 0) {
            clk = 500;
        }
    }

    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++) {
        allEle.arr[i]->Update(allEle.arr[i]);
    }

    // run interact for every element
    for (int i = 0; i < allEle.len; i++) {
        Elements *ele = allEle.arr[i];
        // run every interact object
        for (int j = 0; j < ele->inter_len; j++) {
            int inter_label = ele->inter_obj[j];
            ElementVec labelEle = _Get_label_elements(self, inter_label);
            for (int i = 0; i < labelEle.len; i++) {
                ele->Interact(ele, labelEle.arr[i]);
            }
        }
    }

    // remove element
    for (int i = 0; i < allEle.len; i++) {
        Elements *ele = allEle.arr[i];
        if (ele->dele)
            _Remove_elements(self, ele);
    }
}

void game_scene_draw(Scene *self)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    GameScene *gs = ((GameScene *)(self->pDerivedObj));
    al_draw_bitmap(gs->background, 0, 0, 0);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++) {
        Elements *ele = allEle.arr[i];
        ele->Draw(ele);
    }
    if (health >= 0) {
        sprintf(str_health, "%d", health);
        const char *healthstr = str_health;
        al_draw_rectangle(50, 640, 70 + (health / 3), 645, al_map_rgb(255, 0, 0), 10);
        al_draw_text(gs->font, al_map_rgb(255, 255, 255), 45, 635, ALLEGRO_ALIGN_LEFT, healthstr);    
    }
    if (pause) {
        al_draw_rectangle(275, 100, 375, 550, al_map_rgb(255, 255, 255), 100);
        al_draw_rectangle(525, 100, 625, 550, al_map_rgb(255, 255, 255), 100);
        al_draw_text(gs->font, al_map_rgb(255, 255, 255), 10, 10, ALLEGRO_ALIGN_LEFT, "Press P to Resume");
        al_draw_text(gs->font, al_map_rgb(255, 255, 255), 10, 30, ALLEGRO_ALIGN_LEFT, "Press R to Restart");  
        al_draw_text(gs->font, al_map_rgb(255, 255, 255), 10, 50, ALLEGRO_ALIGN_LEFT, "Press B back to menu");
        al_draw_text(gs->font, al_map_rgb(255, 255, 255), 10, 70, ALLEGRO_ALIGN_LEFT, "Press M to Mute/Unmute"); 
    }
    if (!pause) {
        sprintf(str_score, "%d", score);
        const char *scorestr = str_score;
        al_draw_text(gs->font, al_map_rgb(255, 255, 255), 10, 10, ALLEGRO_ALIGN_LEFT, scorestr);
    }
}

void game_scene_destroy(Scene *self)
{
    GameScene *Obj = ((GameScene *)(self->pDerivedObj));
    ALLEGRO_BITMAP *background = Obj->background;
    al_destroy_bitmap(background);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++) {
        Elements *ele = allEle.arr[i];
        ele->Destroy(ele);
    }
    free(Obj);
    free(self);
}
