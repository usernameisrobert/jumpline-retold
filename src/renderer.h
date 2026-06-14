#pragma once
#include "player.h"
#include <raylib.h>
#include <stddef.h>

typedef struct object {
    Vector2 pos;
    Vector2 scale;
    float rotation;

    union {
        Color color;
        struct {
            Color tint;
            Texture2D texture;
        };
    };

    bool istextured;
} Object;

typedef struct scene {
    Color bg_color;
    Player player;

    Object* objects;
    size_t obj_cap;
    size_t obj_count;
} Scene;


void Renderer_Draw(Scene const* const scene);

/// NOTE: this clones object and return the new object in heap, keep in mind the object may be invalidated if you add anohter object
Object* Scene_AddObject(Scene* scene, Object obj);
void Scene_AddObjects(Scene* scene, Object obj[], int count);
void Scene_Deinit(Scene* scene);
