#pragma once
#include <variant>
namespace MiniSynth {

    struct QuitEvent{};

    struct KeyDownEvent{
        int scancode;
        bool repeat;
    };

    struct KeyUpEvent {
        int scancode;
    };

    using Event = std::variant<
        QuitEvent,
        KeyDownEvent,
        KeyUpEvent,
        >;
}