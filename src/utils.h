#pragma once

#include <chrono>
#include <iostream>
#include <fstream>

namespace gm_utils {
    double current_timestamp();

    template<typename T>
    void serialize(std::ostream &stream, const T &object)
    {
        size_t object_size = sizeof(object);
        std::cout << object_size << std::endl;
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