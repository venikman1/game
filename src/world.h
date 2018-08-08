#pragma once

#include <vector>

#include "geometry.h"

namespace gm_engine {
    class Entity {
    private:
        Cube shape;
    
    public:
        Entity();
        Entity(const Cube& shape);

        Cube& get_shape();
        void render();
    };

    class World {
    private:
        std::vector<Entity*> entities; // This is a little bs
    };
}