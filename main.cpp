#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <graphics.h>

int example1() {
    int SCREEN_WIDTH = 640;
    int SCREEN_HEIGHT = 480;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Could not init SDL: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window *screen = SDL_CreateWindow("My application",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if (!screen) {
        fprintf(stderr, "Could not create window\n");
        return 1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_SOFTWARE);
    if (!renderer) {
        fprintf(stderr, "Could not create renderer\n");
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    bool isquit = false;
    SDL_Event event;
    while (!isquit) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isquit = true;
            }
        }
    }

    SDL_DestroyWindow(screen);
    SDL_Quit();
    return 0;
}

int example2()
{
    int SCREEN_WIDTH = 640;
    int SCREEN_HEIGHT = 480;
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
        return 1;
    }
    window = SDL_CreateWindow(
            "hello_sdl2",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN
    );
    if (window == NULL) {
        fprintf(stderr, "could not create window: %s\n", SDL_GetError());
        return 1;
    }
    screenSurface = SDL_GetWindowSurface(window);
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(window);
    bool isquit = false;
    SDL_Event event;
    while (!isquit) {
        if (SDL_PollEvent( & event)) {
            if (event.type == SDL_QUIT) {
                isquit = true;
            }
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

int example3()
{
    initwindow(800,600); int x = 400, y = 300, r;
    for (r = 25; r <= 125; r += 20)
        circle(x, y, r);
    getch(); closegraph(); return 0;
}

//arguments for main?idk
//int argc, char* args[]

int main() {
    example3();
    return 0;
}