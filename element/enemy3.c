#include "enemy3.h"
#include "../shapes/Rectangle.h"
#include <allegro5/allegro_primitives.h>
#include<stdlib.h>
#include <time.h>
/*
   [enemy3 function]
*/
Elements *New_enemy3(int label,int x)
{
    enemy3 *pDerivedObj = (enemy3 *)malloc(sizeof(enemy3));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/enemy3.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = x;
    pDerivedObj->y = 0;
    pDerivedObj->blood=40;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x + pDerivedObj->width / 3,
                                        pDerivedObj->y + pDerivedObj->height / 3,
                                        pDerivedObj->x + 2 * pDerivedObj->width / 3,
                                        pDerivedObj->y + 2 * pDerivedObj->height / 3);
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = enemy3_update;
    pObj->Interact = enemy3_interact;
    pObj->Draw = enemy3_draw;
    pObj->inter_obj[pObj->inter_len++] = Floor_L;
    pObj->inter_obj[pObj->inter_len++] = Projectile_L;
    pObj->Destroy = enemy3_destory;
    return pObj;
}


void enemy3_update(Elements *self) 
{
    enemy3 *Obj = ((enemy3 *)(self->pDerivedObj));
    _enemy3_update_position(self, 0, 1);
    if(Obj->y>600)
    {
        health-=40;
        self->dele=true;
    }
}
void _enemy3_update_position(Elements *self, int dx, int dy)
{
    enemy3 *Obj = ((enemy3 *)(self->pDerivedObj));
    Obj->x += dx;
    Obj->y += dy;
    Shape *hitbox = Obj->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}
void enemy3_interact(Elements *self, Elements *tar) {
    enemy3 *Obj = ((enemy3 *)(self->pDerivedObj));
     if (tar->label == Projectile_L)
    {
        Projectile *Pro = ((Projectile *)(tar->pDerivedObj));
        if (Pro->hitbox->overlap(Pro->hitbox, Obj->hitbox))
        {
            Obj->blood-=attack;
            tar->dele=true;
            if(Obj->blood<=0){
                score+=100;
                self->dele = true;
            }
        }    
    }
}
void enemy3_draw(Elements *self)
{
    enemy3 *Obj = ((enemy3 *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img,Obj->x, Obj->y, 0);    
    //al_draw_rectangle(Obj->x,Obj->y-25,Obj->x+(Obj->blood*8), Obj->y-20, al_map_rgb(255,0,0),20);    
}
void enemy3_destory(Elements *self)
{
    enemy3 *Obj = ((enemy3 *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
