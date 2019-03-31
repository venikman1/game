#include "graphics.h"
#include "world.h"

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
        , collision_left()
        , collision_right()
        , move_velocity()
        , friction(0.3)
    {
    }
    Entity::Entity(
        const Cube& shape,
        const Point<double>& color,
        const Point<double>& velocity,
        const double mass,
        bool is_static,
        const double friction
    )
        : shape(shape)
        , color(color)
        , velocity(velocity)
        , mass(mass)
        , static_object(is_static)
        , collision_left()
        , collision_right()
        , move_velocity()
        , friction(friction)
    {
    }

    Cube& Entity::get_shape() {
        return shape;
    }
    Point<double>& Entity::get_velocity() {
        return velocity;
    }
    Point<double>& Entity::get_move_velocity() {
        return move_velocity;
    }
    Point<double>& Entity::get_color() {
        return color;
    }
    double& Entity::get_mass() {
        return mass;
    }
    double& Entity::get_friction() {
        return friction;
    }
    bool& Entity::is_static() {
        return static_object;
    }
    Point<Entity*>& Entity::get_collision_from_left_side() {
        return collision_left;
    }
    Point<Entity*>& Entity::get_collision_from_right_side() {
        return collision_right;
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
        if (used_texture) {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, used_texture->get_texture());

            gl_set_color({0.4, 0.4, 0.4}); 
            glBegin(GL_QUADS);
            used_texture->uv_map_point(Options<Sides>(Left, Bottom), shape.get_size().x, shape.get_size().y);
            gl_set_point(shape.get_point(Options<Sides>().set(Left).set(Bottom).set(Near)));
            used_texture->uv_map_point(Options<Sides>(Right, Bottom), shape.get_size().x, shape.get_size().y);
            gl_set_point(shape.get_point(Options<Sides>().set(Right).set(Bottom).set(Near)));
            used_texture->uv_map_point(Options<Sides>(Right, Top), shape.get_size().x, shape.get_size().y);
            gl_set_point(shape.get_point(Options<Sides>().set(Right).set(Top).set(Near)));
            used_texture->uv_map_point(Options<Sides>(Left, Top), shape.get_size().x, shape.get_size().y);
            gl_set_point(shape.get_point(Options<Sides>().set(Left).set(Top).set(Near)));
            glEnd();

            glDisable(GL_TEXTURE_2D);

            gl_set_color(color * 0.5); 
            glBegin(GL_QUADS);
            gl_set_point(shape.get_point(Options<Sides>().set(Left).set(Bottom).set(Near)));
            gl_set_point(shape.get_point(Options<Sides>().set(Left).set(Bottom).set(Far)));
            gl_set_point(shape.get_point(Options<Sides>().set(Left).set(Top).set(Far)));
            gl_set_point(shape.get_point(Options<Sides>().set(Left).set(Top).set(Near)));
            glEnd();

            gl_set_color(color * 0.5); 
            glBegin(GL_QUADS);
            gl_set_point(shape.get_point(Options<Sides>().set(Right).set(Bottom).set(Near)));
            gl_set_point(shape.get_point(Options<Sides>().set(Right).set(Bottom).set(Far)));
            gl_set_point(shape.get_point(Options<Sides>().set(Right).set(Top).set(Far)));
            gl_set_point(shape.get_point(Options<Sides>().set(Right).set(Top).set(Near)));
            glEnd();

            gl_set_color(color * 0.4); 
            glBegin(GL_QUADS);
            gl_set_point(shape.get_point(Options<Sides>().set(Left).set(Bottom).set(Far)));
            gl_set_point(shape.get_point(Options<Sides>().set(Right).set(Bottom).set(Far)));
            gl_set_point(shape.get_point(Options<Sides>().set(Right).set(Top).set(Far)));
            gl_set_point(shape.get_point(Options<Sides>().set(Left).set(Top).set(Far)));
            glEnd();

            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, used_texture->get_texture());

            gl_set_color({1.0, 1.0, 1.0}); 
            glBegin(GL_QUADS);
            used_texture->uv_map_point(Options<Sides>(Left, Bottom), shape.get_size().x, shape.get_size().z);
            gl_set_point(shape.get_point(Options<Sides>().set(Left).set(Top).set(Near)));
            used_texture->uv_map_point(Options<Sides>(Right, Bottom), shape.get_size().x, shape.get_size().z);
            gl_set_point(shape.get_point(Options<Sides>().set(Right).set(Top).set(Near)));
            used_texture->uv_map_point(Options<Sides>(Right, Top), shape.get_size().x, shape.get_size().z);
            gl_set_point(shape.get_point(Options<Sides>().set(Right).set(Top).set(Far)));
            used_texture->uv_map_point(Options<Sides>(Left, Top), shape.get_size().x, shape.get_size().z);
            gl_set_point(shape.get_point(Options<Sides>().set(Left).set(Top).set(Far)));
            glEnd();

            glDisable(GL_TEXTURE_2D);
        }
        else {
            gl_set_color(color * 0.4); 
            glBegin(GL_QUADS);
            gl_set_point(shape.get_point(Options<Sides>().set(Left).set(Bottom).set(Near)));
            gl_set_point(shape.get_point(Options<Sides>().set(Right).set(Bottom).set(Near)));
            gl_set_point(shape.get_point(Options<Sides>().set(Right).set(Top).set(Near)));
            gl_set_point(shape.get_point(Options<Sides>().set(Left).set(Top).set(Near)));
            glEnd();

            gl_set_color(color * 0.5); 
            glBegin(GL_QUADS);
            gl_set_point(shape.get_point(Options<Sides>().set(Left).set(Bottom).set(Near)));
            gl_set_point(shape.get_point(Options<Sides>().set(Left).set(Bottom).set(Far)));
            gl_set_point(shape.get_point(Options<Sides>().set(Left).set(Top).set(Far)));
            gl_set_point(shape.get_point(Options<Sides>().set(Left).set(Top).set(Near)));
            glEnd();

            gl_set_color(color * 0.5); 
            glBegin(GL_QUADS);
            gl_set_point(shape.get_point(Options<Sides>().set(Right).set(Bottom).set(Near)));
            gl_set_point(shape.get_point(Options<Sides>().set(Right).set(Bottom).set(Far)));
            gl_set_point(shape.get_point(Options<Sides>().set(Right).set(Top).set(Far)));
            gl_set_point(shape.get_point(Options<Sides>().set(Right).set(Top).set(Near)));
            glEnd();

            gl_set_color(color * 0.4); 
            glBegin(GL_QUADS);
            gl_set_point(shape.get_point(Options<Sides>().set(Left).set(Bottom).set(Far)));
            gl_set_point(shape.get_point(Options<Sides>().set(Right).set(Bottom).set(Far)));
            gl_set_point(shape.get_point(Options<Sides>().set(Right).set(Top).set(Far)));
            gl_set_point(shape.get_point(Options<Sides>().set(Left).set(Top).set(Far)));
            glEnd();

            gl_set_color(color); 
            glBegin(GL_QUADS);
            gl_set_point(shape.get_point(Options<Sides>().set(Left).set(Top).set(Near)));
            gl_set_point(shape.get_point(Options<Sides>().set(Right).set(Top).set(Near)));
            gl_set_point(shape.get_point(Options<Sides>().set(Right).set(Top).set(Far)));
            gl_set_point(shape.get_point(Options<Sides>().set(Left).set(Top).set(Far)));
            glEnd();
        }
    }
}