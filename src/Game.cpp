#include "Game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#define COLOR_CHANNEL_MAX_VALUE (0xFF)
#define COLOR_CHANNEL_MIN_VALUE (0x00)

Game::Game(): window(NULL), texture(NULL), renderer(NULL) {};

bool Game::Init() {
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed, SDL error: " << SDL_GetError() << std::endl;
        success = false;
    }
    else {
        window = SDL_CreateWindow("SDL Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (!window) {
            std::cerr << "SDL window creation failed, SDL error: " << SDL_GetError() << std::endl;
            success = false;
        }
        else {
            // Create renderer for window
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (!renderer) {
                std::cerr << "SDL CreateRenderer failed, SDL error: " << SDL_GetError() << std::endl;
                success = false;
            }
            else {
                // Initialize renderer colour
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);

                // Initialize SDL image PNG loading
                if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
                    std::cerr << "SDL_Image init failed, SDL error: " << SDL_GetError() << std::endl;
                    success = false;
                }
            }
        }
    }

    return success;
}

SDL_Texture* Game::LoadTexture(const char* filepath) {
    SDL_Texture* newTexture = IMG_LoadTexture(renderer, filepath);

    return newTexture;
}

bool Game::LoadMedia() {
    bool success = true;

    texture = LoadTexture("assets/texture.png");
    if (!texture) {
        std::cerr << "Failed ot load texture, SDL error: " << SDL_GetError() << std::endl;
        success = false;
    }
    
    return success;
}

void Game::EventHandler() {
    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (SDL_QUIT == e.type) {
                quit = true;
            }
        }
        

    }
}

void Game::Close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window);

    renderer = nullptr;
    texture = nullptr;
    window = nullptr;

    SDL_Quit();
    IMG_Quit();
}

void Game::Run() {
    if (Init()) {
        LoadMedia();
        EventHandler();
    }

    Close();
}