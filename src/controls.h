#pragma once

#include <utility>
#include <vector>

namespace gm_engine {
    class Controller {
    private:
        std::vector<bool> pressed_keys;
        int mouse_x, mouse_y;
        bool pressed_mouse;
    
    public:
        Controller();

        void press_key(unsigned int key);
        void release_key(unsigned int key);
        bool is_key_pressed(unsigned int key);

        void press_mouse();
        void release_mouse();
        void move_mouse(int x, int y);
        std::pair<int, int> get_mouse_position();
        bool is_mouse_pressed();
    };
}
