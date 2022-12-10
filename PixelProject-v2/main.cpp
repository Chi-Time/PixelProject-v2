#include <GL/glew.h>
#include <SDL.h>

#include <iostream>

#include "Game.h"

void PrintInGameCommands();
bool CreateWindowAndContext();

SDL_GLContext g_context;
SDL_Window* g_window;

int main(int argc, char* argv[])
{
    bool success = true;

    if (!CreateWindowAndContext())
        success = false;
    
    Game game(&g_context, g_window);
    if (!success || !game.Initialize())
    {
        printf("PixelProject failed to Initialize");
        success = false;
    }

    // GLErrorCallback::LinkCallback(true);
    game.Run();

    SDL_DestroyWindow(g_window);
    SDL_Quit();
    return 0;
}

bool CreateWindowAndContext()
{
    bool success = true;
    
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    g_window = SDL_CreateWindow(
       "Pixel Project v2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
         1280, 720,
       SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );

    if (g_window == nullptr) {
        printf("Window could not be created!\nSDL Err: %s\n", SDL_GetError());
        success = false;
    }
    g_context = SDL_GL_CreateContext(g_window);
    if (g_context == nullptr)
    {
        printf("OpenGL context could not be created! SDL Err: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // Vsync cause we're bad
        if (SDL_GL_SetSwapInterval(1) < 0)
        {
            printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
        }
        glClearColor(0.01f, 0.01f, 0.01f, 1.0f);
    }
    // Init glew, has to be done after context
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
        success = false;
    }
    std::cerr << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
    return success;
}