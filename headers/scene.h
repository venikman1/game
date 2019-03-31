#pragma once

#include "geometry.h"
#include "world.h"

namespace gm_engine {
    class Scene {
    // I don't knwo why I created this class. Maybe remove it?
    private:
        World world;
    
    public:
        Scene();
        Scene(const World& world);

        void process(double time);

        World&  get_world();
    };
}