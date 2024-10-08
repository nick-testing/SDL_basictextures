#ifndef GAME_H
#define GAME_H

typedef struct SDL_Window SDL_Window;
typedef struct SDL_Renderer SDL_Renderer;
typedef struct SDL_Texture SDL_Texture;

class Game {
public:
    Game();
    void Run();

private:
    static const int SCREEN_HEIGHT = 600;
    static const int SCREEN_WIDTH = 800;

    SDL_Window* window;
    SDL_Texture* texture;
    SDL_Renderer* renderer;

    bool Init();
    bool LoadMedia();
    SDL_Texture* LoadTexture(const char*);
    void EventHandler();
    void Close();

    void RenderTexture();
    void RenderViewport();
};

#endif