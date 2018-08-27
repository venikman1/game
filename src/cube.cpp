#include "geometry.h"

#include <algorithm>

namespace gm_engine {

    Cube::Cube(const Point<double>& near_point, const Point<double>& size)
        : near_point(near_point)
        , size(size)
    {
    }

    const double& (*min)(const double&, const double&) = &std::min<double>;
    bool Cube::is_intersect(const Cube& other_cube) const {
        Point<double> near_boundary = map_points(
            get_point(Options<Sides>().set(Sides::Left).set(Sides::Bottom).set(Sides::Near)),
            other_cube.get_point(Options<Sides>().set(Sides::Left).set(Sides::Bottom).set(Sides::Near)),
            [](double a, double b) {return std::max(a, b);}
        );

        Point<double> far_boundary = map_points(
            get_point(Options<Sides>().set(Sides::Right).set(Sides::Top).set(Sides::Far)),
            other_cube.get_point(Options<Sides>().set(Sides::Right).set(Sides::Top).set(Sides::Far)),
            [](double a, double b) {return std::min(a, b);}  // WTF IS IT BOYS????????????????
        );
        
        return (
            near_boundary.x <= far_boundary.x &&
            near_boundary.y <= far_boundary.y &&
            near_boundary.z <= far_boundary.z
        );
    }

    Point<double> Cube::get_point(const Options<Sides>& which) const {
        Point<double> result;
        result.x = (which.is_set(Sides::Right)) ? near_point.x + size.x:  near_point.x;
        result.y = (which.is_set(Sides::Top)) ? near_point.y + size.y : near_point.y;
        result.z = (which.is_set(Sides::Far)) ?  near_point.z + size.z : near_point.z;
        return result;
    }

    Point<double>& Cube::get_size() {
        return size;
    }

    void Cube::move_to(const Point<double>& position) {
        near_point = position;
    }

    void Cube::move(const Point<double>& position_change) {
        near_point += position_change;
    }
}