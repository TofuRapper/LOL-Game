#include "enemy4.h"
#include "../shapes/Rectangle.h"
#include <allegro5/allegro_primitives.h>
#include<stdlib.h>
#include <time.h>
/*
   [enemy4 function]
*/
Elements *New_enemy4(int label,int x)
{
    enemy4 *pDerivedObj = (enemy4 *)malloc(sizeof(enemy4));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/enemy4.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = x;
    pDerivedObj->y = 0;
    pDerivedObj->blood=200;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x + pDerivedObj->width / 3,
                                        pDerivedObj->y + pDerivedObj->height / 3,
                                        pDerivedObj->x + 2 * pDerivedObj->width / 3,
                                        pDerivedObj->y + 2 * pDerivedObj->height / 3);
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = enemy4_update;
    pObj->Interact = enemy4_interact;
    pObj->Draw = enemy4_draw;
    pObj->inter_obj[pObj->inter_len++] = Floor_L;
    pObj->inter_obj[pObj->inter_len++] = Projectile_L;
    pObj->Destroy = enemy4_destory;
    return pObj;
}


void enemy4_update(Elements *self) 
{
    enemy4 *Obj = ((enemy4 *)(self->pDerivedObj));
    _enemy4_update_position(self, 0, 1);
    if(Obj->y>600)
    {
        health-=1001;
        self->dele=true;
    }
}
void _enemy4_update_position(Elements *self, int dx, int dy)
{
    enemy4 *Obj = ((enemy4 *)(self->pDerivedObj));
    Obj->x += dx;
    Obj->y += dy;
    Shape *hitbox = Obj->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}
void enemy4_interact(Elements *self, Elements *tar) {
    enemy4 *Obj = ((enemy4 *)(self->pDerivedObj));
     if (tar->label == Projectile_L)
    {
        Projectile *Pro = ((Projectile *)(tar->pDerivedObj));
        if (Pro->hitbox->overlap(Pro->hitbox, Obj->hitbox))
        {
            Obj->blood-=attack;
            tar->dele=true;
            if(Obj->blood<=0){
                score+=400;
                self->dele = true;
            }
        }    
    }
}
void enemy4_draw(Elements *self)
{
    enemy4 *Obj = ((enemy4 *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img,Obj->x, Obj->y, 0);    
    al_draw_rectangle(Obj->x,Obj->y-25,Obj->x+(Obj->blood), Obj->y-20, al_map_rgb(255,0,0),20);    
}
void enemy4_destory(Elements *self)
{
    enemy4 *Obj = ((enemy4 *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
