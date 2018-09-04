#include "graphics.h"
#include "geometry.h"

#include <string>

namespace gm_engine {
    Texture::Texture()
        : texture_id()
        , in_game_size()
    {}

    Texture::Texture(const Image& image) {
        texture_id = image.load_texture();
        in_game_size = {static_cast<double>(image.width), static_cast<double>(image.height), 0.0};
    }

    Texture::Texture(std::string filename)
        : Texture(Image(filename))
    {}

    Point<double>& Texture::get_in_game_size() {
        return in_game_size;
    }
    
    void Texture::uv_map_point(const Options<Sides>& which, double plain_width, double plain_height) {
        if (which.is_set(Left) && which.is_set(Bottom)) {
            glTexCoord2d(0.0, 0.0);
        }
        else if (which.is_set(Right) && which.is_set(Bottom)) {
            glTexCoord2d(plain_width / in_game_size.x, 0.0);
        }
        else if (which.is_set(Right) && which.is_set(Top)) {
            glTexCoord2d(plain_width / in_game_size.x, plain_height / in_game_size.y);
        }
        else {
            glTexCoord2d(0.0, plain_height / in_game_size.y);
        }
    }

    GLuint Texture::get_texture() const {
        return texture_id;
    }
}
