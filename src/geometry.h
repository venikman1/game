#pragma once

namespace gm_engine {
    template<typename T>
    class Point
    {
    public:
        T x;
        T y;
        T z;
        Point(T _x = 0, T _y = 0, T _z = 0);
        Point operator+(const Point &p) const;
        Point operator+() const;
        Point operator-(const Point &p) const;
        Point operator-() const;
        Point operator*(const T &k) const;
        Point& operator+=(const Point &p);
        Point& operator-=(const Point &p);
        Point& operator*=(const T &k);
    };

    template<typename T>
    Point<T> operator*(const T &k, const Point<T> &p);

    template<typename T, typename Mapper>
    Point<T> map_points(const Point<T> &p1, const Point<T> &p2, Mapper func);
    template<typename T, typename Mapper>
    Point<T> map_point(const Point<T> &p, Mapper func);

    template<typename T>
    Point<T>::Point(T _x, T _y, T _z)
        : x(_x)
        , y(_y)
        , z(_z)
    {
    }

    template<typename T>
    Point<T> Point<T>::operator+(const Point<T> &p) const
    {
        return Point<T>(x + p.x, y + p.y, z + p.z);
    }

    template<typename T>
    Point<T> Point<T>::operator+() const
    {
        return Point<T>(x, y, z);
    }

    template<typename T>
    Point<T> Point<T>::operator-(const Point<T> &p) const
    {
        return Point<T>(x - p.x, y - p.y, z - p.z);
    }

    template<typename T>
    Point<T> Point<T>::operator-() const
    {
        return Point<T>(-x, -y, -z);
    }

    template<typename T>
    Point<T> Point<T>::operator*(const T &k) const
    {
        return Point<T>(x * k, y * k, z * k);
    }

    template<typename T>
    Point<T>& Point<T>::operator+=(const Point<T> &p)
    {
        x += p.x;
        y += p.y;
        z += p.z;
        return *this;
    }

    template<typename T>
    Point<T>& Point<T>::operator-=(const Point<T> &p)
    {
        x -= p.x;
        y -= p.y;
        z -= p.z;
        return *this;
    }

    template<typename T>
    Point<T>& Point<T>::operator*=(const T &k)
    {
        x *= k;
        y *= k;
        z *= k;
        return *this;
    }

    template<typename T>
    Point<T> operator*(const T &k, const Point<T> &p)
    {
        return p * k;
    }

    template<typename T, typename Mapper>
    Point<T> map_points(const Point<T> &p1, const Point<T> &p2, Mapper func)
    {
        return Point<T>(
            func(p1.x, p2.x),
            func(p1.y, p2.y),
            func(p1.z, p2.z)
        );
    }

    template<typename T, typename Mapper>
    Point<T> map_point(const Point<T> &p, Mapper func) 
    {
        return Point<T>(
            func(p.x),
            func(p.y),
            func(p.z)
        );
    }

    class Cube {
    private:
        Point<double> near_point;
        Point<double> size;
    
    public:
        static const unsigned int LEFT, RIGHT, BOTTOM, TOP, NEAR, FAR;

        Cube(const Point<double>& near_point, const Point<double>& size);

        bool is_intersect(const Cube& other_cube) const;
        Point<double> get_point(unsigned int which) const;
        Point<double>& get_size();

        void move_to(const Point<double>& position);
        void move(const Point<double>& position_change);
    };
}