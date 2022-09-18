#include <DxLib.h>
#include <cmath>
#include "utils.hpp"

float utils::round_point(float val, int point) {
    float ret = val * std::pow(10.0f, point - 1);
    ret = static_cast<float>(static_cast<int>(ret + 0.5f));
    return ret * std::pow(10.0f, -point + 1);
}
