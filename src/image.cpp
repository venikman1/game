#include "graphics.h"

#include <png.h>
#include <stdio.h>

namespace gm_engine {
    Image::Image(std::string filename)
    {
        png_structp png_ptr;
        png_infop info_ptr;
        unsigned int sig_read = 0;
        int color_type, interlace_type;
        FILE *fp;
        fp = std::fopen(filename.c_str(), "rb");
        png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        info_ptr = png_create_info_struct(png_ptr);
        png_init_io(png_ptr, fp);
        png_set_sig_bytes(png_ptr, sig_read);
        png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);
        png_uint_32 out_width, out_height;
        int bit_depth;
        png_get_IHDR(png_ptr, info_ptr, &out_width, &out_height, &bit_depth, &color_type, &interlace_type, NULL, NULL);
        width = out_width;
        height = out_height;
        alpha = (color_type == PNG_COLOR_TYPE_RGBA);
        unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
        texture = (unsigned char*) malloc(row_bytes * height);
        png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);
        for (int i = 0; i < height; i++)
        {
            memcpy(texture + (row_bytes * (height - 1 - i)), row_pointers[i], row_bytes);
        }
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(fp);
    }
    Image::~Image()
    {
        // free(texture);
    }
    GLubyte* Image::read_bytes()
    {
        return texture;
    }
    GLuint Image::load_texture() {
        GLuint tex;
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, read_bytes());
        return tex;
    }
}