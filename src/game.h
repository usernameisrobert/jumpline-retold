#include "renderer.h"

typedef struct window_info {
    const int width;
    const int height;
} WindowInfo;

void StartGameLoop(); // init
void EndGameLoop(); // deinit

void LoadScene(Scene* scene);
WindowInfo CreateWindow(int width, int height, const char* title);
