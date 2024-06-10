#ifndef SCENEMANAGER_H_INCLUDED
#define SCENEMANAGER_H_INCLUDED
#include "scene.h"
extern Scene *scene;
typedef enum {
    Menu_L,
    GameScene_L,
    Over_L,
    WIN_L,
    Equipment_L
} SceneType;
void create_scene(SceneType);

#endif