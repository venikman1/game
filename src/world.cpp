#include <iostream>
#include <vector>

#include "world.h"
#include "graphics.h"

namespace gm_engine {
    Entity::Entity()
        : shape(
            Point<double>(),
            Point<double>()
        )
        , color(0.7, 0.7, 0.7)
        , velocity()
        , mass(1.0)
        , static_object(true)
        , collision()
    {
    }
    Entity::Entity(const Cube& shape, const Point<double>& color, const Point<double>& velocity, const double mass, bool is_static)
        : shape(shape)
        , color(color)
        , velocity(velocity)
        , mass(mass)
        , static_object(is_static)
        , collision()
    {
    }

    Cube& Entity::get_shape() {
        return shape;
    }
    Point<double>& Entity::get_velocity() {
        return velocity;
    }
    Point<double>& Entity::get_color() {
        return color;
    }
    double& Entity::get_mass() {
        return mass;
    }
    bool& Entity::is_static() {
        return static_object;
    }
    Point<Entity::Collision>& Entity::get_collision() {
        return collision;
    }
    
    inline void gl_set_point(const Point<double>& p) {
        glVertex3d(p.x, p.y, p.z);
        // std::cout << p << "\n";
    }

    inline void gl_set_color(const Point<double>& p) {
        glColor3d(p.x, p.y, p.z);
        // std::cout << p << "\n";
    }

    void Entity::render() {
        gl_set_color(color * 0.4); 
        glBegin(GL_QUADS);
        gl_set_point(shape.get_point(Cube::LEFT | Cube::BOTTOM | Cube::NEAR));
        gl_set_point(shape.get_point(Cube::RIGHT | Cube::BOTTOM | Cube::NEAR));
        gl_set_point(shape.get_point(Cube::RIGHT | Cube::TOP | Cube::NEAR));
        gl_set_point(shape.get_point(Cube::LEFT | Cube::TOP | Cube::NEAR));
        glEnd();

        gl_set_color(color * 0.5); 
        glBegin(GL_QUADS);
        gl_set_point(shape.get_point(Cube::LEFT | Cube::BOTTOM | Cube::NEAR));
        gl_set_point(shape.get_point(Cube::LEFT | Cube::BOTTOM | Cube::FAR));
        gl_set_point(shape.get_point(Cube::LEFT | Cube::TOP | Cube::FAR));
        gl_set_point(shape.get_point(Cube::LEFT | Cube::TOP | Cube::NEAR));
        glEnd();

        gl_set_color(color * 0.5); 
        glBegin(GL_QUADS);
        gl_set_point(shape.get_point(Cube::RIGHT | Cube::BOTTOM | Cube::NEAR));
        gl_set_point(shape.get_point(Cube::RIGHT | Cube::BOTTOM | Cube::FAR));
        gl_set_point(shape.get_point(Cube::RIGHT | Cube::TOP | Cube::FAR));
        gl_set_point(shape.get_point(Cube::RIGHT | Cube::TOP | Cube::NEAR));
        glEnd();

        gl_set_color(color * 0.4); 
        glBegin(GL_QUADS);
        gl_set_point(shape.get_point(Cube::LEFT | Cube::BOTTOM | Cube::FAR));
        gl_set_point(shape.get_point(Cube::RIGHT | Cube::BOTTOM | Cube::FAR));
        gl_set_point(shape.get_point(Cube::RIGHT | Cube::TOP | Cube::FAR));
        gl_set_point(shape.get_point(Cube::LEFT | Cube::TOP | Cube::FAR));
        glEnd();

        gl_set_color(color); 
        glBegin(GL_QUADS);
        gl_set_point(shape.get_point(Cube::LEFT | Cube::TOP | Cube::NEAR));
        gl_set_point(shape.get_point(Cube::RIGHT | Cube::TOP | Cube::NEAR));
        gl_set_point(shape.get_point(Cube::RIGHT | Cube::TOP | Cube::FAR));
        gl_set_point(shape.get_point(Cube::LEFT | Cube::TOP | Cube::FAR));
        glEnd();
    }
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


    void World::add_entity(Entity* entity) {
        entities.push_back(entity);
    }
    void World::render() {
        for (Entity* entity : entities) {
            entity->render();
        }
    }

    void World::apply_gravity(double time) {
        for (int i = 0; i < entities.size(); ++i) {
            if (!entities[i]->is_static())
                entities[i]->get_velocity() += gravity_acceleration * time;
        }
    }

    void set_collision(Entity::Collision& collision, double speed) {
        if (speed > 0)
            collision = Entity::RIGHT;
        else
            collision = Entity::LEFT;
    }

    template <typename Func> 
    void World::process_physic_on_axis(double time, Func axis_getter) {
        for (int i = 0; i < entities.size(); ++i) {
            axis_getter(entities[i]->get_collision()) = Entity::NONE;

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
                            entities[i]->get_shape().move(axis_getter(axis_getter(entities[i]->get_velocity()) * time));
                            collide_with_static = true;
                            set_collision(axis_getter(entities[i]->get_collision()), old_velocity);
                            break;
                        }
                        intersections.push_back(entities[j]);
                    }
                }
                if (collide_with_static)
                    continue;
                if (!intersections.empty()) {
                    set_collision(axis_getter(entities[i]->get_collision()), old_velocity);
                    Entity::Collision another_side = (axis_getter(entities[i]->get_collision()) == Entity::LEFT ? Entity::RIGHT : Entity::LEFT);
                    for (Entity* entity : intersections) {
                        axis_getter(entity->get_collision()) = another_side;
                    }
                    intersections.push_back(entities[i]);
                    entities[i]->get_shape().move(axis_getter(-old_velocity * time));
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
        T& operator()(Point<T>& point) {
            switch(mode) {
                case X: return point.x;
                case Y: return point.y;
                case Z: return point.z;
            }
        }

        template <typename T>
        Point<T> operator()(const T& k) {
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
        AxisGetter a;
        a.mode = AxisGetter::X;
        process_physic_on_axis(time, a);
        a.mode = AxisGetter::Y;
        process_physic_on_axis(time, a);
        a.mode = AxisGetter::Z;
        process_physic_on_axis(time, a);

        for (auto entity : entities) {
            if (entity->get_collision().y == gm_engine::Entity::LEFT) {
                entity->get_velocity().x += sign(entity->get_velocity().x) * gravity_acceleration.y * 0.3 * time;
                entity->get_velocity().z += sign(entity->get_velocity().z) * gravity_acceleration.y * 0.3 * time;
            }
        }
    }
}
