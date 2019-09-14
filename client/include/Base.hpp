#ifndef BASE_H
#define BASE_H
#include "spdlog/spdlog.h"
#include <vector>

typedef double Float;

class Vec2 {
public:
    Float x,y;
    Vec2(Float t_x = 0.f, Float t_y = 0.f):x(t_x), y(t_y) {
    }
};

#endif // BASE_H