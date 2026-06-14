#include "renderer.h"

typedef struct window_info {
    const int width;
    const int height;
} WindowInfo;

void StartGameLoop(); // init
void EndGameLoop(); // deinit

typedef void (*UpdateFunc)(float dt, Scene* loaded_scene);
void RegisterUpdate(UpdateFunc func);

void LoadScene(Scene* scene);
WindowInfo CreateWindow(int width, int height, const char* title);
