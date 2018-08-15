#pragma once

#include <vector>

#include "geometry.h"

namespace gm_engine {
    class Entity {
    private:
        Cube shape;
        Point<double> color;
        Point<double> velocity;
        double mass;
        bool static_object;

    public:
        Entity();
        Entity(
            const Cube& shape,
            const Point<double>& color = Point<double>(0.7, 0.7, 0.7),
            const Point<double>& velocity = Point<double>(0.0, 0.0, 0.0),
            const double mass = 1,
            bool is_static = true
        );

        Cube& get_shape();
        Point<double>& get_velocity();
        Point<double>& get_color();
        double& get_mass();

        void render();
    };

    class World {
    private:
        std::vector<Entity*> entities; // This is a little bs
        Point<double> gravity_acceleration = Point<double>(0, -100.0, 0);

        void apply_gravity(double time);
        template <typename Func> 
        void process_physic_on_axis(double time, Func axis_getter);
    public:
        void add_entity(Entity* entity);
        void render();
        void process_physic(double time);
    };
}