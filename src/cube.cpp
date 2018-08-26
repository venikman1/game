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
            get_point(Options<Sides>().set(LEFT).set(BOTTOM).set(NEAR)),
            other_cube.get_point(Options<Sides>().set(LEFT).set(BOTTOM).set(NEAR)),
            [](double a, double b) {return std::max(a, b);}
        );

        Point<double> far_boundary = map_points(
            get_point(Options<Sides>().set(RIGHT).set(TOP).set(FAR)),
            other_cube.get_point(Options<Sides>().set(RIGHT).set(TOP).set(FAR)),
            [](double a, double b) {return std::min(a, b);}  // WTF IS IT BOYS????????????????
        );
        
        return (
            near_boundary.x <= far_boundary.x &&
            near_boundary.y <= far_boundary.y &&
            near_boundary.z <= far_boundary.z
        );
    }

    Point<double> Cube::get_point(Options<Sides> which) const {
        Point<double> result;
        result.x = (which.is_set(RIGHT)) ? near_point.x + size.x:  near_point.x;
        result.y = (which.is_set(TOP)) ? near_point.y + size.y : near_point.y;
        result.z = (which.is_set(FAR)) ?  near_point.z + size.z : near_point.z;
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