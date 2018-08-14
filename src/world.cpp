#include <iostream>

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
        , static_object(true)
    {
    }
    Entity::Entity(const Cube& shape, const Point<double>& color, const Point<double>& velocity, bool is_static)
        : shape(shape)
        , color(color)
        , velocity(velocity)
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
    void World::process_physic(double time) {
        for (int i = 0; i < entities.size(); ++i) {
            for (int j = i + 1; j < entities.size(); ++j) {
                if (entities[i]->get_shape().is_intersect(entities[j]->get_shape())) {
                    std::cout << "INTERSECTION " << i << " " << j << "\n";
                }
            }
            entities[i]->get_shape().move(entities[i]->get_velocity() * time);
        }
    }
}
