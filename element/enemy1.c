#include "enemy1.h"
#include "../shapes/Rectangle.h"
#include <allegro5/allegro_primitives.h>
#include<stdlib.h>
#include <time.h>
/*
   [enemy function]
*/

Elements *New_enemy(int label,int x)
{
    enemy *pDerivedObj = (enemy *)malloc(sizeof(enemy));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/Enemy1.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = x;
    pDerivedObj->y = 0;
    pDerivedObj->blood = 10;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,// + pDerivedObj->width / 3,
                                        pDerivedObj->y,// + pDerivedObj->height / 3,
                                        pDerivedObj->x,// + 2 * pDerivedObj->width / 3,
                                        pDerivedObj->y + 50);// + 2 * pDerivedObj->height / 3);
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = enemy_update;
    pObj->Interact = enemy_interact;
    pObj->Draw = enemy_draw;
    pObj->inter_obj[pObj->inter_len++] = Floor_L;
    pObj->inter_obj[pObj->inter_len++] = Projectile_L;
    pObj->Destroy = enemy_destroy;
    return pObj;
}


void enemy_update(Elements *self) 
{
    enemy *Obj = ((enemy *)(self->pDerivedObj));
    _enemy_update_position(self, 0, 1);
    if(Obj->y>600)
    {
        health-=10;
        self->dele=true;
    }
}
void _enemy_update_position(Elements *self, int dx, int dy)
{
    enemy *Obj = ((enemy *)(self->pDerivedObj));
    Obj->x += dx;
    Obj->y += dy;
    Shape *hitbox = Obj->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}
void enemy_interact(Elements *self, Elements *tar) {
    enemy *Obj = ((enemy *)(self->pDerivedObj));
     if (tar->label == Projectile_L)
    {
        Projectile *Pro = ((Projectile *)(tar->pDerivedObj));
        if (Pro->hitbox->overlap(Pro->hitbox, Obj->hitbox))
        {
            Obj->blood-=attack;
            tar->dele=true;
            if(Obj->blood<=0){
                score+=10;
                self->dele = true;
            }
        }    
    }
}
void enemy_draw(Elements *self)
{
    enemy *Obj = ((enemy *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img,Obj->x, Obj->y, 0);    
    //al_draw_rectangle(Obj->x,Obj->y-25,Obj->x+(Obj->blood*10), Obj->y-20, al_map_rgb(255,0,0),20);    
}
void enemy_destroy(Elements *self)
{
    enemy *Obj = ((enemy *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
