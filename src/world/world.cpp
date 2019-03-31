#include <iostream>
#include <vector>

#include "world.h"
#include "graphics.h"

namespace gm_engine {
    Entity* intersect_with_entities(std::vector<Entity*>& entities, Entity* checking_entity) {
        for (auto entity : entities) {
            if (entity == checking_entity)
                continue;
            if (entity->get_shape().is_intersect(checking_entity->get_shape())) {
                return entity;
            }
        }
        return 0;
    }


    void World::add_object(WorldObject* object) {
        objects.push_back(object);
    }

    void World::render() {
        for (WorldObject* object : objects) {
            object->render();
        }
    }

    void World::apply_gravity(double time) {
        for (int i = 0; i < objects.size(); ++i) {
            Entity* entity = objects[i]->get_entity();
            if (entity && !entity->is_static())
                entity->get_velocity() += gravity_acceleration * time;
        }
    }

    Point<Entity*>& get_collision_side(Entity* entity, double speed) {
        if (speed > 0)
            return entity->get_collision_from_right_side();
        else
            return entity->get_collision_from_left_side();
    }

    template <typename Func> 
    void World::process_physic_on_axis(std::vector<Entity*> &entities, double time, Func axis_getter) {
        for (int i = 0; i < entities.size(); ++i) {
            axis_getter(entities[i]->get_collision_from_left_side()) = 0;
            axis_getter(entities[i]->get_collision_from_right_side()) = 0;

            double old_velocity = axis_getter(entities[i]->get_velocity());
            entities[i]->get_shape().move(axis_getter(old_velocity * time));
            std::vector<Entity*> intersections;
            if (entities[i]->is_static()) {  // Collision is not set for static objects
                for (int j = 0; j < entities.size(); ++j) {
                    if (i == j) {
                        continue;
                    }
                    if (!entities[j]->is_static() && entities[i]->get_shape().is_intersect(entities[j]->get_shape())) {
                        //entities[i]->get_shape().move(axis_getter(-old_velocity * time));
                        axis_getter(entities[j]->get_velocity()) = axis_getter(entities[i]->get_velocity());
                        entities[j]->get_shape().move(axis_getter(axis_getter(entities[j]->get_velocity()) * time));
                        // entities[i]->get_shape().move(axis_getter(-old_velocity * time));
                    }
                }
            }
            else {
                bool collide_with_static = false;
                for (int j = 0; j < entities.size(); ++j) {
                    if (i == j) {
                        continue;
                    }
                    if (entities[i]->get_shape().is_intersect(entities[j]->get_shape())) {
                        if (entities[j]->is_static()) {
                            entities[i]->get_shape().move(axis_getter(-old_velocity * time));
                            axis_getter(entities[i]->get_velocity()) = axis_getter(entities[j]->get_velocity());
                            // entities[i]->get_shape().move(axis_getter(axis_getter(entities[i]->get_velocity()) * time));
                            collide_with_static = true;
                            axis_getter(get_collision_side(entities[i], old_velocity)) = entities[j];
                        }
                        intersections.push_back(entities[j]);
                    }
                }
                if (collide_with_static)
                    continue;
                if (!intersections.empty()) {

                    // EXPEREMENTAL CODE
                    std::vector<double> colls;
                    for (Entity* entity : intersections) {
                        Options<Sides> side = (old_velocity > 0
                            ? Options<Sides>().set(Sides::Left).set(Sides::Bottom).set(Sides::Near)
                            : Options<Sides>().set(Sides::Right).set(Sides::Top).set(Sides::Far)
                        );

                        colls.push_back(
                            axis_getter(entity->get_shape().get_point(side)) + 
                            (side.is_set(Sides::Left) ? -EPS - axis_getter(entities[i]->get_shape().get_size()) : EPS)
                        );
                    }
                    double nearest_coll = colls[0];
                    for (double e : colls) {
                        if (old_velocity > 0 && e < nearest_coll)
                            nearest_coll = e;
                        else if (old_velocity < 0 && e > nearest_coll)
                            nearest_coll = e;
                    }
                    axis_getter(entities[i]->get_shape().get_position()) = nearest_coll; // FIXME: I am not working

                    axis_getter(get_collision_side(entities[i], old_velocity)) = intersections[0];  // FIXME: collision with not single object
                    for (Entity* entity : intersections) {
                        axis_getter(get_collision_side(entities[i], -old_velocity)) = entities[i];
                    }
                    intersections.push_back(entities[i]);
                    // entities[i]->get_shape().move(axis_getter(-old_velocity * time));

                    // double vel_step = old_velocity / 2;
                    // while (std::fabs(vel_step) > EPS) {
                    //     entities[i]->get_shape().move(axis_getter(vel_step * time));
                    //     if (intersect_with_entities(entities, entities[i]))
                    //         entities[i]->get_shape().move(axis_getter(-vel_step * time));
                    //     vel_step /= 2;
                    // }  // FIXME: This doesn't fix problem

                    double impulse = 0;
                    double sum_mass = 0;
                    for (Entity* entity : intersections) {
                        impulse += entity->get_mass() * axis_getter(entity->get_velocity());
                        sum_mass += entity->get_mass();
                    }
                    double new_velocity = impulse / sum_mass;
                    for (Entity* entity : intersections) {
                        axis_getter(entity->get_velocity()) = new_velocity;
                    }
                }
            }
        }
    }
    
    struct AxisGetter {
        enum Mode {X, Y, Z};

        Mode mode;

        template <typename T>
        T operator()(const Point<T>& point) const {
            switch(mode) {
                case X: return point.x;
                case Y: return point.y;
                case Z: return point.z;
            }
        }

        template <typename T>
        T& operator()(Point<T>& point) const {
            switch(mode) {
                case X: return point.x;
                case Y: return point.y;
                case Z: return point.z;
            }
        }

        template <typename T>
        Point<T> operator()(const T& k) const {
            Point<T> result;
            switch(mode) {
                case X: result.x = k; break;
                case Y: result.y = k; break;
                case Z: result.z = k; break;
            }
            return result;
        }
    };
    void World::process_physic(double time) {
        apply_gravity(time);

        std::vector<Entity*> entities;
        for (auto object : objects)
            if (object)
                entities.push_back(object->get_entity());

        AxisGetter a;
        a.mode = AxisGetter::X;
        process_physic_on_axis(entities, time, a);
        a.mode = AxisGetter::Y;
        process_physic_on_axis(entities, time, a);
        a.mode = AxisGetter::Z;
        process_physic_on_axis(entities, time, a);

        for (auto entity : entities) {
            if (entity->is_static())
                continue;
            Entity* standing_on = entity->get_collision_from_left_side().y;
            if (standing_on) {
                Point<double> relative_speed = entity->get_velocity() - entity->get_move_velocity() - standing_on->get_velocity();
                double friction = entity->get_friction() + standing_on->get_friction();
                double max_friction_accel = std::fabs(gravity_acceleration.y) * friction;
                double max_friction_vel_change = max_friction_accel * time;
                
                if (std::fabs(relative_speed.x) < max_friction_vel_change) {
                    entity->get_velocity().x -= relative_speed.x;
                }
                else {
                    entity->get_velocity().x -= sign(relative_speed.x) * max_friction_vel_change;
                }

                if (std::fabs(relative_speed.z) < max_friction_vel_change) {
                    entity->get_velocity().z -= relative_speed.z;
                }
                else {
                    entity->get_velocity().z -= sign(relative_speed.z) * max_friction_vel_change;
                }
            }
            else {
                Point<double> relative_speed = entity->get_velocity() - entity->get_move_velocity();
                relative_speed.y = 0.0;
                double friction = 5.0;

                entity->get_velocity() -= relative_speed * friction * time / entity->get_mass();
            }
        }
    }
    
    World::~World() {
        for (WorldObject *object : objects)
            delete object;
    }
}
