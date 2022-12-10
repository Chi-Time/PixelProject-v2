#include "Game.h"

#include <GL/glew.h>

Game::Game(SDL_GLContext* gl_context, SDL_Window* gl_window)
{
    _context = gl_context;
    _window = gl_window;
}

bool Game::Initialize()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glViewport(0, 0, 1280, 720);

    return true;
}

void Game::Run()
{
    while (true)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                return;
            }
        }
        
        SDL_GL_SwapWindow(_window);
    }
}