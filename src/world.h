#pragma once

#include "geometry.h"

namespace gm_engine {
    class Cube {
    private:
        Point<double> near_point;
        Point<double> size;
    
    public:
        static const unsigned int LEFT, RIGHT, BOTTOM, TOP, NEAR, FAR;

        Cube(const Point<double>& near_point, const Point<double>& size);

        bool is_intersect(const Cube& other_cube) const;
        Point<double> get_point(unsigned int which) const;
        Point<double> get_size() const;

        void move_to(const Point<double>& position);
        void move(const Point<double>& position_change);
    };

}
