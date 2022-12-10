#include <GL/glew.h>
#include <SDL.h>

#include <iostream>
#include <format>

#include "Game.h"
#include "Scripts/Utility/Console.h"

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
        Console::PrintError("PixelProject failed to initialize!\n");
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
        Console::PrintError(std::string("Window could not be created!\nSDL Err: %s\n", SDL_GetError()));
        success = false;
    }
    g_context = SDL_GL_CreateContext(g_window);
    if (g_context == nullptr)
    {
        Console::PrintError(std::string("OpenGL context could not be created! SDL Err: %s\n", SDL_GetError()));
        success = false;
    }
    else
    {
        // Vsync cause we're bad
        if (SDL_GL_SetSwapInterval(1) < 0)
        {
            Console::PrintWarning(std::string("Unable to set VSync! SDL Error: %s\n", SDL_GetError()));
        }
        glClearColor(0.01f, 0.01f, 0.01f, 1.0f);
    }
    // Init glew, has to be done after context
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        // Convert GLubyte * to char *
        auto errStr = reinterpret_cast<const char*>(glewGetErrorString(err));
        Console::PrintError(std::string("GLEW failed to initialize! GLEW Err: %s\n", errStr));
        success = false;
    }
    Console::PrintSuccess("OpenGL context created successfully!\n");
    return success;
}