#include "world.h"
#include "graphics.h"

namespace gm_engine {
    Entity::Entity()
        : shape(
            Point<double>(),
            Point<double>()
        )
    {
    }
    Entity::Entity(const Cube& shape)
        : shape(shape)
    {
    }

    Cube& Entity::get_shape() {
        return shape;
    }
    
    inline void gl_set_point(const Point<double>& p) {
        glVertex3d(p.x, p.y, p.z);
        // std::cout << p << "\n";
    }

    void Entity::render() {
        glColor3f(0.3f, 0.3f, 0.3f); 
        glBegin(GL_QUADS);
        gl_set_point(shape.get_point(Cube::LEFT | Cube::BOTTOM | Cube::NEAR));
        gl_set_point(shape.get_point(Cube::RIGHT | Cube::BOTTOM | Cube::NEAR));
        gl_set_point(shape.get_point(Cube::RIGHT | Cube::TOP | Cube::NEAR));
        gl_set_point(shape.get_point(Cube::LEFT | Cube::TOP | Cube::NEAR));
        glEnd();

        glColor3f(0.7f, 0.7f, 0.7f); 
        glBegin(GL_QUADS);
        gl_set_point(shape.get_point(Cube::LEFT | Cube::TOP | Cube::NEAR));
        gl_set_point(shape.get_point(Cube::RIGHT | Cube::TOP | Cube::NEAR));
        gl_set_point(shape.get_point(Cube::RIGHT | Cube::TOP | Cube::FAR));
        gl_set_point(shape.get_point(Cube::LEFT | Cube::TOP | Cube::FAR));
        glEnd();
    }
}
