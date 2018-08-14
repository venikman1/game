#pragma once

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <string>

namespace gm_engine {
    class Image
    {
    private:
        GLubyte *texture;

    public:
        int width;
        int height;
        bool alpha;
        Image(std::string filename);
        ~Image();
        GLubyte* read_bytes();
        GLuint load_texture();
    };
}