#pragma once

#include <chrono>
#include <iostream>
#include <fstream>

namespace gm_engine {
    double current_timestamp();

    template<typename T>
    class Options
    {
    private:
        unsigned int options;
    public:
        Options<T>();
        Options<T>& set(const T &option);
        Options<T>& unset(const T &option);
        bool is_set(const T &option) const;
    };

    template<typename T>
    Options<T>::Options()
    {
        options = 0;
    }

    template<typename T>
    Options<T>& Options<T>::set(const T &option)
    {
        options |= 1 << option;
        return *this;
    }

    template<typename T>
    bool Options<T>::is_set(const T &option) const
    {
        return ((options >> option) & 1) == 1;
    }

    template<typename T>
    Options<T>& Options<T>::unset(const T &option)
    {
        if (is_set(option))
        {
            options ^= 1 << option;
        }
        return *this;
    }

    template<typename T>
    void serialize(std::ostream &stream, const T &object)
    {
        size_t object_size = sizeof(object);
        char *ptr = (char*)&object;
        stream.write(ptr, object_size);
    };

    template<typename T>
    void deserialize(std::istream &stream, T &object)
    {
        size_t object_size = sizeof(object);
        char *ptr = (char*)&object;
        stream.read(ptr, object_size);
    }
}