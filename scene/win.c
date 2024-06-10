#include <allegro5/allegro_primitives.h>
#include "win.h"
#include <stdbool.h>
#include <allegro5/allegro_image.h>
#include "equipmentscene.h"
#include "gamescene.h"
#include "sceneManager.h"
/*
   [winner function]
*/
Scene *New_winner(int label)
{
    winner *pDerivedObj = (winner *)malloc(sizeof(winner));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 12, 0);
    pDerivedObj->background = al_load_bitmap("assets/image/win.png");
    // Load sound
    pDerivedObj->song = al_load_sample("assets/sound/menu.mp3");
    al_reserve_samples(20);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    pDerivedObj->title_x = WIDTH / 2;
    pDerivedObj->title_y = HEIGHT / 2;
    // Loop the song until the display closes
    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 0.5);
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Update = winner_update;
    pObj->Draw = winner_draw;
    pObj->Destroy = winner_destroy;
    return pObj;
}


void winner_update(Scene *self)
{
    if (key_state[ALLEGRO_KEY_ENTER])
    {
        self->scene_end = true;
        health = 1000;
        t_clock = 0;
        if (stage < 3) {
            stage++;
            window = 4;
        }
        else {
            stage = 0;
            score = 0;
            window = 0;
        }
        //clear_key_states(); // Clear key states to prevent immediate action
    }
    if (key_state[ALLEGRO_KEY_X])
    {
        self->scene_end = true;
        health = 1000;
        t_clock = 0;
        stage = 0;
        score = 0;
        window = 0;
        //clear_key_states(); // Clear key states to prevent immediate action
    }
    return; 
}

static char str_score[20];
void winner_draw(Scene *self)
{
    winner *Obj = ((winner *)(self->pDerivedObj));
    al_play_sample_instance(Obj->sample_instance);
    al_draw_bitmap(Obj->background, 1, 1, 0);
    sprintf(str_score,"%d",score);
    const char *scorestr=str_score;
    al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->title_x-300, Obj->title_y+200, ALLEGRO_ALIGN_CENTER, "You are winner!");
    al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->title_x-300, Obj->title_y+220, ALLEGRO_ALIGN_CENTRE, "Your Score:");
    al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->title_x-300, Obj->title_y+240, ALLEGRO_ALIGN_CENTER, scorestr);
    if(stage < 3){
    al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->title_x-300, Obj->title_y+260, ALLEGRO_ALIGN_CENTER, "Press Enter to Continue");
    }else{
        al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->title_x-300, Obj->title_y+260, ALLEGRO_ALIGN_CENTER, "Press Enter to Restart");
    }
    al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->title_x-300, Obj->title_y+280, ALLEGRO_ALIGN_CENTER, "Press X to back to Menu");
    al_draw_rectangle(Obj->title_x - 450, Obj->title_y+160, Obj->title_x - 150, Obj->title_y + 320, al_map_rgb(255, 255, 255), 0);
}
void winner_destroy(Scene *self)
{
    winner *Obj = ((winner *)(self->pDerivedObj));
    al_destroy_font(Obj->font);
    al_destroy_sample(Obj->song);
    al_destroy_sample_instance(Obj->sample_instance);
    free(Obj);
    free(self);
}
