#include "geometry.h"

#include <algorithm>

namespace gm_engine {
    const unsigned int Cube::LEFT = 0;
    const unsigned int Cube::RIGHT = 0b1;
    const unsigned int Cube::BOTTOM = 0;
    const unsigned int Cube::TOP = 0b10;
    const unsigned int Cube::NEAR = 0;
    const unsigned int Cube::FAR = 0b100;

    Cube::Cube(const Point<double>& near_point, const Point<double>& size)
        : near_point(near_point)
        , size(size)
    {
    }

    const double& (*min)(const double&, const double&) = &std::min<double>;
    bool Cube::is_intersect(const Cube& other_cube) const {
        Point<double> near_boundary = map_points(
            get_point(LEFT | BOTTOM | NEAR),
            other_cube.get_point(LEFT | BOTTOM | NEAR),
            [](double a, double b) {return std::max(a, b);}
        );

        Point<double> far_boundary = map_points(
            get_point(RIGHT | TOP | FAR),
            other_cube.get_point(RIGHT | TOP | FAR),
            [](double a, double b) {return std::min(a, b);}  // WTF IS IT BOYS????????????????
        );
        
        return (
            near_boundary.x > far_boundary.x ||
            near_boundary.y > far_boundary.y ||
            near_boundary.z > far_boundary.z
        );
    }

    Point<double> Cube::get_point(unsigned int which) const {
        Point<double> result;
        result.x = (which & RIGHT) ? near_point.x + size.x:  near_point.x;
        result.x = (which & TOP) ? near_point.y + size.y : near_point.y;
        result.x = (which & FAR) ?  near_point.z + size.z : near_point.z;
        return result;
    }

    Point<double> Cube::get_size() const {
        return size;
    }

    void Cube::move_to(const Point<double>& position) {
        near_point = position;
    }

    void Cube::move(const Point<double>& position_change) {
        near_point += position_change;
    }
}