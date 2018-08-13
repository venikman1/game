#pragma once

#include <vector>

#include "geometry.h"

namespace gm_engine {
    class Entity {
    private:
        Cube shape;
        Point<double> color;
    
    public:
        Entity();
        Entity(const Cube& shape, const Point<double>& color = Point<double>(0.7, 0.7, 0.7));

        Cube& get_shape();
        void render();
    };

    class World {
    private:
        std::vector<Entity*> entities; // This is a little bs
    };
}