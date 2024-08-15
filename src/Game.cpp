#include "Game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#define COLOR_CHANNEL_MAX_VAL (0xFF)
#define COLOR_CHANNEL_MIN_VAL (0x00)

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
        
        SDL_SetRenderDrawColor(renderer, COLOR_CHANNEL_MAX_VAL, COLOR_CHANNEL_MAX_VAL, COLOR_CHANNEL_MAX_VAL, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        
        // Render a filled rectangle with top left point being (x, y) coordinate pair, w width and y height)
        SDL_Rect fillRect = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
        SDL_SetRenderDrawColor(renderer, COLOR_CHANNEL_MAX_VAL, COLOR_CHANNEL_MIN_VAL, COLOR_CHANNEL_MIN_VAL, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &fillRect);

        // Render a hollow rectangle
        SDL_Rect outlineRect = {SCREEN_WIDTH / 8, SCREEN_HEIGHT / 8,SCREEN_WIDTH / 2 + SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 4};
        SDL_SetRenderDrawColor(renderer, COLOR_CHANNEL_MIN_VAL, COLOR_CHANNEL_MAX_VAL, COLOR_CHANNEL_MIN_VAL, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawRect(renderer, &outlineRect);

        // Render a vertical blue line spanning the width of the window
        SDL_SetRenderDrawColor(renderer, COLOR_CHANNEL_MIN_VAL, COLOR_CHANNEL_MIN_VAL, COLOR_CHANNEL_MAX_VAL, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

        // Render a horizontal dotted line
        SDL_SetRenderDrawColor(renderer, COLOR_CHANNEL_MAX_VAL, COLOR_CHANNEL_MAX_VAL, COLOR_CHANNEL_MIN_VAL, SDL_ALPHA_OPAQUE);
        int middleWidth = SCREEN_WIDTH / 2;
        for (int i = 0; i < SCREEN_HEIGHT; i += 5) {
            SDL_RenderDrawPoint(renderer, middleWidth, i);
        }

        SDL_RenderPresent(renderer);
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