#include "renderer.h"
#include <raylib.h>
#include <stdio.h>
#include "game.h"


#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

static Scene* current_loaded_scene = nullptr;

WindowInfo CreateWindow(int width, int height, const char* title) {
    InitWindow(width, height, title);
    return (WindowInfo){ width, height };
}

void LoadScene(Scene* scene) {
    current_loaded_scene = scene;
    // NOTE: if we add heap we might have to deinit the current_loaded_scene before loading a new one
    // if we use heap do we own the loaded scene?
}

void GameLoop() {
    Renderer_Draw(current_loaded_scene);
}

void StartGameLoop() {
    if (current_loaded_scene == nullptr) {
        printf("Error: NO SCENE LOADED!");
        return;
    }
    #ifdef __EMSCRIPTEN__
        emscripten_set_main_loop(GameLoop, 60, 1);
    #else
        SetTargetFPS(60);
        while (!WindowShouldClose()) {
            GameLoop();
        }
    #endif
}

void EndGameLoop() {
    CloseWindow();
}
