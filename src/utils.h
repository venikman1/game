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
        Options<T>(const T &option);
        template<typename ...Args>
        Options<T>(const T &option, const Args &...other);
        Options<T>& set(const T &option);
        Options<T>& unset(const T &option);
        bool is_set(const T &option);
    };

    template<typename T>
    Options<T>::Options(const T &option)
    {
        options |= option;
    }

    template<typename T>
    template<typename ...Args>
    Options<T>::Options(const T &option, const Args &...other):
        Options(other...)
    {
        options |= 1 << option;
    }

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
    bool Options<T>::is_set(const T &option)
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