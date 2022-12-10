#pragma once

#include <SDL.h>

class Game
{
public:
    Game(SDL_GLContext* gl_context, SDL_Window* gl_window);
    bool Initialize();
    void Run();
    
protected:
    SDL_GLContext* _context;
    SDL_Window* _window;

private:
    Game() = default;
    ~Game() = default;

};