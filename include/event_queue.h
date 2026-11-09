#pragma once
#include "event.h"

#include <optional>

namespace MiniSynth{
    class EventQueue {
        EventQueue();
        
        std::optional<Event> pop_event();
        bool isEmpty();
        
        
        
    };
}