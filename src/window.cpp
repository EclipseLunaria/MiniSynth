#include "window.h"
#include <iostream>
#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"

namespace {
    const int MAX_WINDOWS = 8;
    SDL_Window * windows_impl[MAX_WINDOWS] = {nullptr};
    SDL_Renderer * renderers[MAX_WINDOWS] = {nullptr};
    MiniSynth::Window * windows[MAX_WINDOWS] = {nullptr};
    int allocate_window(){
        for (int i = 0; i < MAX_WINDOWS; i++){
            if(windows_impl[i] == nullptr) return i;
        }
        return -1;
    }
}
MiniSynth::Window::Window(int width, int height, const char * title)
{
    // init sdl
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)){
        SDL_Log("Unable to initialize the SDL window");
        throw "SDL initialization error";
    }

    m_height = height;
    m_width = width;
    
    // Initialize Window
    m_window_index = allocate_window();

    windows_impl[m_window_index] = SDL_CreateWindow(title, m_width, m_height, 0);
    m_window_id = static_cast<int>(SDL_GetWindowID(windows_impl[m_window_index]));
    if (m_window_id == 0) throw "Invalid window id.";

    windows[m_window_index] = this;
    //Initialize Renderers
    renderers[m_window_index] = SDL_CreateRenderer(windows_impl[m_window_index], nullptr);

    SDL_SetRenderLogicalPresentation(renderers[m_window_index], m_width, m_height, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    std::cout << "window and renderer intitialized" << std::endl;
}

MiniSynth::Window::~Window()
{
    SDL_DestroyRenderer(renderers[m_window_index]);
    SDL_DestroyWindow(windows_impl[m_window_index]);
    windows_impl[m_window_index] = nullptr;
    windows[m_window_index] = nullptr;
    SDL_Log("Destroying window %d.\n", m_window_index);
}

MiniSynth::Window *MiniSynth::Window::find_window(int window_id)
{
    for (int i = 0; i < MAX_WINDOWS; ++i){
        if (windows[i]->m_window_id == window_id) 
        {
            return windows[i];
        }
    }
    return nullptr;
}

void MiniSynth::Window::clear()
{
    SDL_RenderClear(renderers[m_window_index]);
}

void MiniSynth::Window::present()
{
    SDL_RenderPresent(renderers[m_window_index]);
}
