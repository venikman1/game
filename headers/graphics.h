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
#include "geometry.h"

namespace gm_engine {
    class Image
    {
    /*
        Image is used to load images from files and upload it to OpenGL.
    */
    private:
        GLubyte *texture;

    public:
        int width;
        int height;
        bool alpha;
        Image(std::string filename);
        ~Image();
        GLubyte* read_bytes();
        GLuint load_texture() const;
    };

    class Texture {
    /*
        Texture provides some useful functions to work with texturing.
    */
    private:
        GLuint texture_id;
        Point<double> in_game_size;

    public:
        Texture();
        Texture(const Image& image);
        Texture(std::string filename);

        GLuint get_texture() const;
        Point<double>& get_in_game_size();
        void uv_map_point(const Options<Sides>& which, double plain_width, double plain_height);
    };
}
