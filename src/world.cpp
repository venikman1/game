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
    {
    }
    Entity::Entity(const Cube& shape, const Point<double>& color, const Point<double>& velocity, const double mass, bool is_static)
        : shape(shape)
        , color(color)
        , velocity(velocity)
        , mass(mass)
        , static_object(is_static)
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
            entities[i]->get_velocity() += gravity_acceleration * time;
        }
    }
    template <typename Func> 
    void World::process_physic_on_axis(double time, Func axis_getter) {
        for (int i = 0; i < entities.size(); ++i) {
            double old_velocity = axis_getter(entities[i]->get_velocity());
            entities[i]->get_shape().move(axis_getter(old_velocity * time));
            std::vector<Entity*> intersections;
            for (int j = 0; j < entities.size(); ++j) {
                if (i == j) {
                    continue;
                }
                if (entities[i]->get_shape().is_intersect(entities[j]->get_shape())) {
                    intersections.push_back(entities[j]);
                    char* names[] = {"X", "Y", "Z"};
                    std::cout << "INTERSECTION " << i << " and " << j << " on axis " << names[axis_getter.mode] << "\n";
                }
            }
            if (!intersections.empty()) {
                intersections.push_back(entities[i]);
                entities[i]->get_shape().move(axis_getter(-old_velocity * time));
                double impulse = 0;
                double sum_mass = 0;
                for (Entity* entity : entities) {
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
    template <typename T>
    struct AxisGetter {
        enum Mode {X, Y, Z};

        Mode mode;

        T& operator()(Point<T>& point) {
            switch(mode) {
                case X: return point.x;
                case Y: return point.y;
                case Z: return point.z;
            }
        }

        Point<T> operator()(const T& k) {
            switch(mode) {
                case X: return Point<T>(k, T(0), T(0));
                case Y: return Point<T>(T(0), k, T(0));
                case Z: return Point<T>(T(0), T(0), k);
            }
        }
    };
    void World::process_physic(double time) {
        // apply_gravity(time);
        AxisGetter<double> a;
        a.mode = AxisGetter<double>::X;
        process_physic_on_axis(time, a);
        a.mode = AxisGetter<double>::Y;
        process_physic_on_axis(time, a);
        a.mode = AxisGetter<double>::Z;
        process_physic_on_axis(time, a);
    }
}
