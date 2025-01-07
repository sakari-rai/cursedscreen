#include "vec2.h"

template<>
fvec2_t fvec2_t::rotated(float radians) {
    const float cs = cos(radians);
    const float ss = sin(radians);
    return {
        cs * x - ss * y,
        ss * x + cs * y 
    };
}

template<>
fvec2_t& fvec2_t::rotate(float radians) {
    const float cs = cos(radians);
    const float ss = sin(radians);
    const float current_x = x;
    const float current_y = y;
    x = cs * current_x - ss * current_y;
    y = ss * current_x + cs * current_y;
    return *this;
}
