#include "utils.h"

namespace gm_utils {
    double current_timestamp()
    {
        return ((std::chrono::duration< double, std::milli> )(std::chrono::duration_cast< std::chrono::milliseconds >(
            std::chrono::system_clock::now().time_since_epoch()
        ))).count();
    }
}