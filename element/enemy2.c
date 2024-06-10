#include "enemy2.h"
#include "../shapes/Rectangle.h"
#include <allegro5/allegro_primitives.h>
#include<stdlib.h>
#include <time.h>
/*
   [enemy2 function]
*/
Elements *New_enemy2(int label,int x)
{
    enemy2 *pDerivedObj = (enemy2 *)malloc(sizeof(enemy2));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/Enemy2.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = x;
    pDerivedObj->y = 0;
    pDerivedObj->blood=20;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x + pDerivedObj->width / 3,
                                        pDerivedObj->y + pDerivedObj->height / 3,
                                        pDerivedObj->x + 2 * pDerivedObj->width / 3,
                                        pDerivedObj->y + 2 * pDerivedObj->height / 3);
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = enemy2_update;
    pObj->Interact = enemy2_interact;
    pObj->Draw = enemy2_draw;
    pObj->inter_obj[pObj->inter_len++] = Floor_L;
    pObj->inter_obj[pObj->inter_len++] = Projectile_L;
    pObj->Destroy = enemy2_destory;
    return pObj;
}


void enemy2_update(Elements *self) 
{
    enemy2 *Obj = ((enemy2 *)(self->pDerivedObj));
    _enemy2_update_position(self, 0, 2);
    if(Obj->y>600)
    {
        health-=20;
        self->dele=true;
    }
}
void _enemy2_update_position(Elements *self, int dx, int dy)
{
    enemy2 *Obj = ((enemy2 *)(self->pDerivedObj));
    Obj->x += dx;
    Obj->y += dy;
    Shape *hitbox = Obj->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}
void enemy2_interact(Elements *self, Elements *tar) {
    enemy2 *Obj = ((enemy2 *)(self->pDerivedObj));
     if (tar->label == Projectile_L)
    {
        Projectile *Pro = ((Projectile *)(tar->pDerivedObj));
        if (Pro->hitbox->overlap(Pro->hitbox, Obj->hitbox))
        {
            Obj->blood-=attack;
            tar->dele=true;
            if(Obj->blood<=0){
                score+=30;
                self->dele = true;
            }
        }    
    }
}
void enemy2_draw(Elements *self)
{
    enemy2 *Obj = ((enemy2 *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img,Obj->x, Obj->y, 0);    
    //al_draw_rectangle(Obj->x,Obj->y-25,Obj->x+(Obj->blood*8), Obj->y-20, al_map_rgb(255,0,0),20);    
}
void enemy2_destory(Elements *self)
{
    enemy2 *Obj = ((enemy2 *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
