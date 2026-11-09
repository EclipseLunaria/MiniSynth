#include <iostream>
#include "osynth/oscillator.h"
#include "window.h"
#include "SDL3/SDL.h"
using namespace MiniSynth;
int main(){
    std::cout << "Hello World!" << std::endl;
    Window window = Window(800,600, "Test Window");
    int running = 1;
    SDL_Event event;
    while (running){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED){
                std::cout << "window id = " << event.window.windowID << std::endl;
            }
        }
        window.clear();
        window.present();
    }
    return 0;
}