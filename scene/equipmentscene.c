#include "equipmentscene.h"
#include "sceneManager.h"  // Include for SceneType enumeration
#include "gamescene.h"     // Include for GameScene_L
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdbool.h>
#include <stdlib.h>
#include "win.h"
#include <stdio.h> // For debugging

// Declare key_state array and clear_key_states function if not already declared elsewhere
extern bool key_state[ALLEGRO_KEY_MAX];
void clear_key_states();

Scene *New_EquipmentScene(int label)
{
    EquipmentScene *pDerivedObj = (EquipmentScene *)malloc(sizeof(EquipmentScene));
    Scene *pObj = New_Scene(label);

    // Load resources
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 12, 0);
    pDerivedObj->background = al_load_bitmap("assets/image/win.png");
    if (stage == 1) {
        pDerivedObj->sword = al_load_bitmap("assets/image/Sword1.jpg");
        //pDerivedObj->sword = al_load_bitmap("assets/image/Sword4.jpg");
        pDerivedObj->shield = al_load_bitmap("assets/image/Shield1.jpg");
    }
    else if (stage == 2) {
        pDerivedObj->sword = al_load_bitmap("assets/image/Sword2.jpg");
        //pDerivedObj->sword = al_load_bitmap("assets/image/Sword4.jpg");
        pDerivedObj->shield = al_load_bitmap("assets/image/Shield2.jpg");
    }
    else if (stage == 3) {
        pDerivedObj->sword = al_load_bitmap("assets/image/Sword3.jpg");
        pDerivedObj->other = al_load_bitmap("assets/image/Sword4.jpg");
        pDerivedObj->shield = al_load_bitmap("assets/image/Shield3.jpg");
    }


    pDerivedObj->selected_equipment = 0; // Initially select the first equipment
    pDerivedObj->title_x = WIDTH / 2;
    pDerivedObj->title_y = HEIGHT / 2;

    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = equipment_update;
    pObj->Draw = equipment_draw;
    pObj->Destroy = equipment_destroy;

    clear_key_states(); // Clear key states when the scene is created

    printf("Equipment scene created\n"); // Debugging statement
    
    return pObj;
}

void equipment_update(Scene *self)
{
    EquipmentScene *eqScene = (EquipmentScene *)(self->pDerivedObj);
    // Handle input to select equipment
    if (stage == 3) {
        if (key_state[ALLEGRO_KEY_LEFT]) {
            if (eqScene->selected_equipment > 0) {
                eqScene->selected_equipment--; // Move left if not at the leftmost equipment
            }
            key_state[ALLEGRO_KEY_LEFT] = false; // Reset key state to avoid repeated handling
            printf("Left key pressed, selected_equipment: %d\n", eqScene->selected_equipment); // Debugging statement
        } else if (key_state[ALLEGRO_KEY_RIGHT]) {
            if (eqScene->selected_equipment < 2) {
                eqScene->selected_equipment++; // Move right if not at the rightmost equipment
            }
            key_state[ALLEGRO_KEY_RIGHT] = false; // Reset key state to avoid repeated handling
            printf("Right key pressed, selected_equipment: %d\n", eqScene->selected_equipment); // Debugging statement
        }
    } else {
        // Handle selection for two equipment choices
        if (key_state[ALLEGRO_KEY_LEFT]) {
            if (eqScene->selected_equipment > 0) {
                eqScene->selected_equipment -= 2; // Move left if not at the leftmost equipment
            }
            key_state[ALLEGRO_KEY_LEFT] = false; // Reset key state to avoid repeated handling
            printf("Left key pressed, selected_equipment: %d\n", eqScene->selected_equipment); // Debugging statement
        } else if (key_state[ALLEGRO_KEY_RIGHT]) {
            if (eqScene->selected_equipment < 1) {
                eqScene->selected_equipment += 2; // Move right if not at the rightmost equipment
            }
            key_state[ALLEGRO_KEY_RIGHT] = false; // Reset key state to avoid repeated handling
            printf("Right key pressed, selected_equipment: %d\n", eqScene->selected_equipment); // Debugging statement
        }
    }

    // Confirm selection
    if (key_state[ALLEGRO_KEY_ENTER]) {
        selected_equipment = eqScene->selected_equipment;
        self->scene_end = true;
        if (selected_equipment == 2 && stage == 1) {
            health += 25; // Add 25 health for shield
        } 
        else if (selected_equipment == 0 && stage == 1) {
            attack += 10; // Add 10 attack for sword
        }
        else if (selected_equipment == 2 && stage == 2) {
            health += 50;
        }
        else if (selected_equipment == 0 && stage == 2) {
            attack += 20;
        }
        else if (selected_equipment == 1 && stage == 3) {

        }
        else if (selected_equipment == 2 && stage == 3) {
            health += 100;
        }
        else {
            attack += 50;
        }
        window = 1; // Assuming this means transitioning back to the game
        key_state[ALLEGRO_KEY_ENTER] = false; // Reset key state to avoid repeated handling
        printf("Enter pressed, ending scene\n"); // Debugging statement
    }
}
void equipment_draw(Scene *self)
{
    EquipmentScene *eqScene = (EquipmentScene *)(self->pDerivedObj);

    al_draw_bitmap(eqScene->background, 0, 0, 0);

    // Draw both images
    al_draw_bitmap(eqScene->sword, eqScene->title_x - 100, eqScene->title_y, 0);
    al_draw_bitmap(eqScene->shield, eqScene->title_x + 100, eqScene->title_y, 0);
    if (stage == 3) {
        al_draw_bitmap(eqScene->other, eqScene->title_x, eqScene->title_y, 0);
    }

    // Highlight the selected equipment
    if (eqScene->selected_equipment == 0) {
        al_draw_rectangle(eqScene->title_x - 100, eqScene->title_y, eqScene->title_x - 100 + al_get_bitmap_width(eqScene->sword), eqScene->title_y + al_get_bitmap_height(eqScene->sword), al_map_rgb(255, 0, 0), 2);
    }
    else if (eqScene->selected_equipment == 1) {
        al_draw_rectangle(eqScene->title_x, eqScene->title_y, eqScene->title_x + al_get_bitmap_width(eqScene->shield), eqScene->title_y + al_get_bitmap_height(eqScene->shield), al_map_rgb(255, 0, 0), 2);

    }
    else {
        al_draw_rectangle(eqScene->title_x + 100, eqScene->title_y, eqScene->title_x + 100 + al_get_bitmap_width(eqScene->shield), eqScene->title_y + al_get_bitmap_height(eqScene->shield), al_map_rgb(255, 0, 0), 2);
    }

    al_draw_text(eqScene->font, al_map_rgb(255, 255, 255), eqScene->title_x, eqScene->title_y + 200, ALLEGRO_ALIGN_CENTER, "Press ENTER to confirm");
}


void equipment_destroy(Scene *self)
{
    EquipmentScene *eqScene = (EquipmentScene *)(self->pDerivedObj);

    al_destroy_font(eqScene->font);
    al_destroy_bitmap(eqScene->background);
    al_destroy_bitmap(eqScene->sword);
    al_destroy_bitmap(eqScene->shield);

    free(eqScene);
    free(self);
    
    printf("Equipment scene destroyed\n"); // Debugging statement
}

// Function to clear all key states
void clear_key_states()
{
    for (int i = 0; i < ALLEGRO_KEY_MAX; i++) {
        key_state[i] = false;
    }
}
