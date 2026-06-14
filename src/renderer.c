#include "renderer.h"
#include "player.h"
#include <inttypes.h>
#include <raylib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void Obj_Draw(Scene const* const scene) {
    for (size_t i = 0; i < scene->obj_count; i++) {
        const Object * const obj = &scene->objects[i];
        
            Vector2 orgin = { 0, 0 };
        if (obj->istextured) {
            Rectangle src = { 0, 0, obj->texture.width, obj->texture.height };
            Rectangle dest = { obj->pos.x, obj->pos.y, obj->scale.x, obj->scale.y};
            DrawTexturePro(obj->texture, src, dest, orgin, obj->rotation, obj->tint);
        } else {
            Rectangle src = { obj->pos.x, obj->pos.y, obj->scale.x, obj->scale.y };
            DrawRectanglePro(src, orgin, obj->rotation, obj->color);
        }
    
    }
}

void Renderer_Draw(Scene const* const scene) {
    BeginDrawing();
    ClearBackground(scene->bg_color);
    Player_Draw(&scene->player);
    Obj_Draw(scene);
    EndDrawing();
}


void Scene_Deinit(Scene* scene) {
    free(scene->objects);
    scene->obj_count = 0;
scene->obj_cap = 0;
scene->objects = nullptr;
}

Object* Scene_AddObject(Scene *scene, Object obj) {
    if (!scene->objects || scene->obj_cap == 0) {
        // NOTE: assumes objects not allocated
        scene->objects = (Object*)malloc(sizeof(Object));
        scene->obj_cap = 1;
        scene->obj_count = 1;

         // Always check if initial malloc succeeded
        if (!scene->objects) {
            printf("Error ran out of memory");
            return nullptr; // Handle allocation failure appropriately
        }

        scene->objects[0] = obj;
    } else if (scene->obj_count >= scene->obj_cap){
        int new_cap = scene->obj_cap * 2;
        Object* tmp = realloc(scene->objects, sizeof(Object) * new_cap);

        if (!tmp) {
            printf("Error ran out of memory!");
            return nullptr;
        }
        scene->objects = tmp;
        scene->obj_cap = new_cap;
        scene->objects[scene->obj_count] = obj;
        scene->obj_count++;
    }

    return &scene->objects[scene->obj_count-1];
}


void Scene_AddObjects(Scene *scene, Object objs[], int count) {
    for (int i = 0; i < count; i++) {
        Scene_AddObject(scene, objs[i]);
    }
}
