#pragma once

template<typename T>
class Point
{
public:
    T x;
    T y;
    T z;
    Point(T _x, T _y, T _z);
    Point operator+(const Point &p) const;
    Point operator+() const;
    Point operator-(const Point &p) const;
    Point operator-() const;
    Point operator*(const T &k) const;
};

template<typename T>
Point<T>::Point(T _x, T _y, T _z)
    : x(_x)
    , y(_y)
    , z(_z)
{
}

template<typename T>
Point<T> Point<T>::operator+(const Point &p) const
{
    return Point<T>(x + p.x, y + p.y, z + p.z);
}

template<typename T>
Point<T> Point<T>::operator+() const
{
    return Point<T>(x, y, z);
}

template<typename T>
Point<T> Point<T>::operator-(const Point &p) const
{
    return Point<T>(x + p.x, y + p.y, z + p.z);
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