#pragma once

#include "geometry.h"

namespace gm_engine {
    class Scene {
    private:
        World world;
    
    public:
        Scene();
        Scene(const World& world);

        void process(double time);

        World&  get_world();
    };
}