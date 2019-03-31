#include "controls.h"

namespace gm_engine {
    Controller::Controller()
        : mouse_x(0)
        , mouse_y(0)
        , pressed_mouse(false)
        , pressed_keys(256, false)
    {
    }   

    void Controller::press_key(unsigned int key) {
        pressed_keys[key] = true;
    }
    void Controller::release_key(unsigned int key) {
        pressed_keys[key] = false;
    }
    bool Controller::is_key_pressed(unsigned int key) {
        return pressed_keys[key];
    }

    void Controller::press_mouse() {
        pressed_mouse = true;
    }
    void Controller::release_mouse() {
        pressed_mouse = false;
    }
    void Controller::move_mouse(int x, int y) {
        mouse_x = x;
        mouse_y = y;
    }
    std::pair<int, int> Controller::get_mouse_position() {
        return {mouse_x, mouse_y};
    }
    bool Controller::is_mouse_pressed() {
        return pressed_mouse;
    }
}