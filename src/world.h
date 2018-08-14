#pragma once

#include <vector>

#include "geometry.h"

namespace gm_engine {
    class Entity {
    private:
        Cube shape;
        Point<double> color;
        Point<double> velocity;
        bool static_object;

    public:
        Entity();
        Entity(
            const Cube& shape,
            const Point<double>& color = Point<double>(0.7, 0.7, 0.7),
            const Point<double>& velocity = Point<double>(0.0, 0.0, 0.0),
            bool is_static = true
        );

        Cube& get_shape();
        Point<double>& get_velocity();
        Point<double>& get_color();

        void render();
    };

    class World {
    private:
        std::vector<Entity*> entities; // This is a little bs
    
    public:
        void add_entity(Entity* entity);
        void render();
        void process_physic(double time);
    };
}