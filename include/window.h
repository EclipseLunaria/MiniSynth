#pragma once

namespace MiniSynth {
    class Window{
        int m_width;
        int m_height;
        int m_window_index;
        int m_window_id;
        bool m_is_closed;

        public:
        Window(int m_width = 800, int m_height = 600, const char * title = "Window");
        ~Window();

        static Window * find_window(int window_id);

        void clear();
        void present();
    };

}