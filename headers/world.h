#pragma once

#include <vector>

#include "geometry.h"
#include "graphics.h"

namespace gm_engine {
    class Entity {
    /*
        Entity - is a physic body which is used by physic engine.
    */
    private:
        Cube shape;
        Point<double> color;
        Point<double> velocity, move_velocity;
        double mass;
        double friction;
        bool static_object;
        Point<Entity*> collision_left, collision_right;

    public:
        Entity();
        Entity(
            const Cube& shape,
            const Point<double>& color = Point<double>(0.7, 0.7, 0.7),
            const Point<double>& velocity = Point<double>(0.0, 0.0, 0.0),
            const double mass = 1,
            bool is_static = false,
            const double friction = 0.3
        );

        Cube& get_shape();
        Point<double>& get_velocity();
        Point<double>& get_move_velocity();
        Point<double>& get_color();
        double& get_mass();
        double& get_friction();
        bool& is_static();
        Point<Entity*>& get_collision_from_left_side();
        Point<Entity*>& get_collision_from_right_side();

        void render(); // TODO: remove render from Entity

        Texture* used_texture = 0; // TODO: enhance texture using
    };

    class WorldObject {
    /*
        Abstract class, which is stored in World class.
    */
    public:
        virtual Entity* get_entity() = 0;
        virtual void render() = 0;

        long long id;
    };

    class World {
    /*
        World stores all object which is used on current game scene. 
        This class provide rendering, physic, game logic and another game actions with scene.
    */
    private:
        std::vector<WorldObject*> objects;
        Point<double> gravity_acceleration = Point<double>(0, -100.0, 0);

        void apply_gravity(double time);
        template <typename Func> 
        void process_physic_on_axis(std::vector<Entity*> &entities, double time, Func axis_getter);
    public:
        void add_object(WorldObject* object); /* Add object and take control of freeing memory */
        void render(); /* Render the whole world */

        // TODO: move physic functions to another place
        void process_physic(double time); /* Process physic for all entities */

        ~World();
    };
}