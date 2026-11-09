#include "event_queue.h"
#include "SDL3/SDL.h"

using namespace MiniSynth;

std::optional<Event> MiniSynth::EventQueue::pop_event()
{
    SDL_Event sdl_event;

    while (SDL_PollEvent(&sdl_event)) {
        switch (sdl_event.type) {
            case SDL_EVENT_QUIT:
            return QuitEvent{};
            
            case SDL_EVENT_KEY_DOWN:
            return KeyDownEvent{
                .scancode = static_cast<int>(sdl_event.key.scancode),
                .repeat = sdl_event.key.repeat
            };

            case SDL_EVENT_KEY_UP:
            return KeyUpEvent{
                .scancode = static_cast<int>(sdl_event.key.scancode)
            };

            default:
            break;
        }

        return std::nullopt;
    }
}