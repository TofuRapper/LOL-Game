#include <allegro5/allegro_primitives.h>
#include "menu.h"
#include <stdbool.h>
#include <allegro5/allegro_image.h>
/*
   [Menu function]
*/
Scene *New_Menu(int label)
{
    Menu *pDerivedObj = (Menu *)malloc(sizeof(Menu));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 14, 0);
    pDerivedObj->background = al_load_bitmap("assets/image/lol.jpg");
    // Load sound
    pDerivedObj->song = al_load_sample("assets/sound/menu.mp3");
    //al_reserve_samples(20);
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
    pObj->Update = menu_update;
    pObj->Draw = menu_draw;
    pObj->Destroy = menu_destroy;
    return pObj;
}
int tot = 0;
void menu_update(Scene *self)
{
    Menu *Obj = ((Menu *)(self->pDerivedObj));
    ALLEGRO_BITMAP *img;
    if (key_state[ALLEGRO_KEY_SPACE])
    {   
        tot = 1;
        img = al_load_bitmap("assets/image/tutoral.jpg");
        Obj->background = img;
    }
    if (key_state[ALLEGRO_KEY_ENTER])
        {
            self->scene_end = true;
            t_clock = 0;
            stage = 0;
            window = 1;
        }
    if (tot == 1) {
        if (key_state[ALLEGRO_KEY_X]){
            tot = 0;
            img = al_load_bitmap("assets/image/lol.jpg");
            Obj->background=img;
        }
    }
    return;
}
void menu_draw(Scene *self)
{
    Menu *Obj = ((Menu *)(self->pDerivedObj));
    al_play_sample_instance(Obj->sample_instance);
    Menu *menu = ((Menu *)(self->pDerivedObj));
    al_draw_bitmap(menu->background, 1, 1, 0);

    // Define colors
    ALLEGRO_COLOR text_color = al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR rect_color = al_map_rgb(0, 0, 0); // Black background for text

    if (tot == 0) {
        // Draw filled rectangles behind the text
        al_draw_filled_rectangle(Obj->title_x - 150, Obj->title_y + 180, Obj->title_x + 150, Obj->title_y + 200, rect_color);
        al_draw_filled_rectangle(Obj->title_x - 150, Obj->title_y + 200, Obj->title_x + 150, Obj->title_y + 220, rect_color);
        al_draw_filled_rectangle(Obj->title_x - 150, Obj->title_y + 220, Obj->title_x + 150, Obj->title_y + 240, rect_color);

        // Draw text
        al_draw_text(Obj->font, text_color, Obj->title_x, Obj->title_y + 180, ALLEGRO_ALIGN_CENTRE, "Minion Killer");
        al_draw_text(Obj->font, text_color, Obj->title_x, Obj->title_y + 200, ALLEGRO_ALIGN_CENTRE, "Press Enter to Start");
        al_draw_text(Obj->font, text_color, Obj->title_x, Obj->title_y + 220, ALLEGRO_ALIGN_CENTRE, "Press Space for Tutorial");

        // Draw rectangle border
        al_draw_rectangle(Obj->title_x - 150, Obj->title_y + 180, Obj->title_x + 150, Obj->title_y + 240, al_map_rgb(255, 255, 255), 0);
    } else if (tot == 1) {
        // Draw filled rectangles behind the text
        al_draw_filled_rectangle(Obj->title_x - 150, Obj->title_y - 300, Obj->title_x + 150, Obj->title_y - 280, rect_color);
        al_draw_filled_rectangle(Obj->title_x - 150, Obj->title_y - 280, Obj->title_x + 150, Obj->title_y - 260, rect_color);
        al_draw_filled_rectangle(Obj->title_x - 150, Obj->title_y - 260, Obj->title_x + 150, Obj->title_y - 240, rect_color);
        al_draw_filled_rectangle(Obj->title_x - 150, Obj->title_y - 240, Obj->title_x + 150, Obj->title_y - 220, rect_color);
        al_draw_filled_rectangle(Obj->title_x - 150, Obj->title_y - 220, Obj->title_x + 150, Obj->title_y - 200, rect_color);

        // Draw text
        al_draw_text(Obj->font, text_color, Obj->title_x, Obj->title_y - 300, ALLEGRO_ALIGN_CENTRE, "Save our nexus!");
        al_draw_text(Obj->font, text_color, Obj->title_x, Obj->title_y - 280, ALLEGRO_ALIGN_CENTRE, "Press A,D to Move");
        al_draw_text(Obj->font, text_color, Obj->title_x, Obj->title_y - 260, ALLEGRO_ALIGN_CENTRE, "Press Space to Attack");
        al_draw_text(Obj->font, text_color, Obj->title_x, Obj->title_y - 240, ALLEGRO_ALIGN_CENTRE, "Press Enter to Continue");
        al_draw_text(Obj->font, text_color, Obj->title_x, Obj->title_y - 220, ALLEGRO_ALIGN_CENTRE, "Press X to back to menu");

        // Draw rectangle border
        al_draw_rectangle(Obj->title_x - 150, Obj->title_y - 310, Obj->title_x + 150, Obj->title_y - 190, al_map_rgb(255, 255, 255), 0);

        // Draw characters and their labels
        al_draw_bitmap(al_load_bitmap("assets/image/Leesin.jpg"), 50, 200, 0);
        al_draw_text(Obj->font, text_color, 150, 600, ALLEGRO_ALIGN_CENTRE, "Lee Sin");

        al_draw_bitmap(al_load_bitmap("assets/image/Ezreal.jpg"), 350, 200, 0);
        al_draw_text(Obj->font, text_color, 450, 600, ALLEGRO_ALIGN_CENTRE, "Ezreal");

        al_draw_bitmap(al_load_bitmap("assets/image/taliyah.jpg"), 650, 200, 0);
        al_draw_text(Obj->font, text_color, 750, 600, ALLEGRO_ALIGN_CENTRE, "Taliyah");
    }
}

void menu_destroy(Scene *self)
{
    Menu *Obj = ((Menu *)(self->pDerivedObj));
    al_destroy_font(Obj->font);
    al_destroy_sample(Obj->song);
    al_destroy_sample_instance(Obj->sample_instance);
    free(Obj);
    free(self);
}
