#include <DxLib.h>
#include <cmath>
#include "utils.hpp"
#include "global_define.hpp"
#include "euclid_vec.hpp"

float utils::round_point(float val, int point) {
    float ret = val * std::pow(10.0f, point - 1);
    ret = static_cast<float>(static_cast<int>(ret + 0.5f));
    return ret * std::pow(10.0f, -point + 1);
}

template <typename T> T utils::clamp(const T val, const T min, const T max) {
    if (val > max) return max;
    if (val < min) return min;
    return val;
}
template int utils::clamp<int>(const int, const int, const int);
template float utils::clamp<float>(const float, const float, const float);

int utils::DrawRotaGraphF_Screen(float x, float y, float ExRate, float Angle, int GrHandle, int TransFlag, int TurnFlag) {
    return DrawRotaGraphF(x + GlobalValues::IN_TOP_LEFT_X, y + GlobalValues::IN_TOP_LEFT_Y, ExRate, Angle, GrHandle, TransFlag, TurnFlag);
}

float utils::rand_in_range(float ang) {
    return (-ang + ang * 2.0f * static_cast<float>(GetRand(10000)) / 10000.0f);
}

bool utils::sphere_collision(Vec2 pos1, Vec2 pos2, float r1, float r2) {
    return pos1.distance(pos2) < r1 + r2;
}
