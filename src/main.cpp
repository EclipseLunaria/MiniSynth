#include <iostream>
#include "osynth/oscillator.h"
#include "osynth/engine.h"
#include "osynth/structures/HistoryQueue.h"
#include "window.h"
#include "SDL3/SDL.h"
using namespace MiniSynth;
using namespace OSynthCore;

const int SAMPLE_RATE = 44100;
static OscillatorEngine engine(SAMPLE_RATE);

using KeyQueue = Structures::HistoryQueue<char, 16>;
static KeyQueue kq = KeyQueue();

struct UserData {
    OscillatorEngine engine;
};

static void SDLCALL AudioEngineCallback(void *userdata, SDL_AudioStream *astream, int additional_amount, int total_amount){
    engine.process_events();
    total_amount /= sizeof(float);
    while (additional_amount > 0){
        const int total = SDL_min(additional_amount, Config::MAX_BLOCK_SIZE);
        float * buffer = engine.render_buffer(total);

        SDL_PutAudioStreamData(astream, buffer, total * sizeof(float));
        additional_amount -= total;
    }
}

// helper method forward declarations
float get_frequency(char c);
void keystate_sync();

int main(){
    std::cout << "Hello World!" << std::endl;
    Window window = Window(800,600, "Test Window");
    
    auto& osc = engine.get_oscillator();
    auto& gain = engine.get_gain();
    auto& queue = engine.get_queue();
    osc.set_frequency(440);
    gain.set_linear_gain(0);

    SDL_AudioSpec spec;
    spec.format = SDL_AUDIO_F32;
    spec.channels = 1;
    spec.freq = SAMPLE_RATE;

    
    SDL_AudioStream * stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, AudioEngineCallback, NULL);
    if (!stream) {
        SDL_Log("Couldn't create audio stream: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    /* SDL_OpenAudioDeviceStream starts the device paused. You have to tell it to start! */
    SDL_ResumeAudioStreamDevice(stream);

    int running = 1;
    SDL_Event event;
    char last_key_pressed;
    bool get_sync_keystate = false;
    while (running){
        // update key played
        keystate_sync();
        char * cp = kq.most_recent();
        std::cout << "most recent key: " << (cp ? *cp : '0') << std::endl;
        if (cp){
            queue.push(Commands::SetGain{.gain = 1.0});
            queue.push(Commands::SetFrequency{.frequency = get_frequency(*cp)});
        }
        else {
            queue.push(Commands::SetGain{.gain = 0.0});
            queue.push(Commands::SetFrequency{.frequency = 0});
        }
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED){
                std::cout << "window id = " << event.window.windowID << std::endl;
                exit(0);
            }
            
            else if (event.type == SDL_EVENT_KEY_UP){
                std::cout << (char) event.key.key << "has been released.";
                if (!get_frequency(event.key.key)) continue;
                kq.release(event.key.key);
                get_sync_keystate = true;
            }

            else if (event.type == SDL_EVENT_KEY_DOWN){
                if (event.key.repeat || !event.key.down) continue;
                float f = 0.0f;
                char k = event.key.key;
                if (!get_frequency(k)) continue;
                kq.press(k);
                get_sync_keystate = true;
            }
        }

        window.clear();
        window.present();
    }
    return 0;
}

float get_frequency(char c){
    float f = 0.0f;
    switch (c){
        case 'a':
        f = 440.0f;
        break;

        case 'w':
        f = OSynthUtils::frequency_transpose(440, 1);
        
        break;

        case 's':
        f = OSynthUtils::frequency_transpose(440, 2);
        break;

        case 'e':
        f = OSynthUtils::frequency_transpose(440, 3);
        break;

        case 'd':
        f = OSynthUtils::frequency_transpose(440, 4);
        break;
        case 'f':
        f = OSynthUtils::frequency_transpose(440, 5);
        break;
        case 't':
        f = OSynthUtils::frequency_transpose(440, 6);
        break;
        case 'g':
        f = OSynthUtils::frequency_transpose(440, 7);
        break;
        case 'y':
        f = OSynthUtils::frequency_transpose(440, 8);
        break;
        case 'h':
        f = OSynthUtils::frequency_transpose(440, 9);
        break;
        case 'u':
        f = OSynthUtils::frequency_transpose(440, 10);
        break;
        case 'j':
        f = OSynthUtils::frequency_transpose(440, 11);
        break;
        case 'k':
        f = OSynthUtils::frequency_transpose(440, 12);
        break;
        default:
        break;
    }
    return f;
}

// syn
void keystate_sync(){
    int num_keys;
    const bool * keyboard_state = SDL_GetKeyboardState(&num_keys);

    char * buf[kq.capacity()];
    int n = 0;
    for (int i = 0; i < num_keys; ++i){
        if (!keyboard_state)
        {
            SDL_Keycode keycode = SDL_GetKeyFromScancode((SDL_Scancode)i, SDL_KMOD_NONE, false);
            if (kq.check(keycode)){
                if(kq.release(keycode)){
                    std::cout << "released from sync: " << keycode << std::endl;
                }
            }
        }

        
    }

}