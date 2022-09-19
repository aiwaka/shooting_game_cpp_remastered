#include "euclid_vec.hpp"

float Vec2::length() const { return std::sqrt(length_square()); }
float Vec2::length_square() const { return x * x + y * y; }
float Vec2::dot(const Vec2 _rhs) const { return x * _rhs.x + y * _rhs.y; }
float Vec2::perp_dot(const Vec2 _rhs) const { return x * _rhs.y - y * _rhs.x; }
float Vec2::distance(const Vec2 fromVec) const { return (*this - fromVec).length(); }
Vec2 Vec2::normalized() const { return *this / this->length(); }
Vec2 Vec2::lerp(const Vec2& target, const float param) const { return *this + (target - *this) * param; }
float Vec2::angle() const { return std::atan2(y, x); }
Vec2 Vec2::rotate(float angle) const {
    float cosAngle = std::cos(angle);
    float sinAngle = std::sin(angle);
    return Vec2{ cosAngle * this->x - sinAngle * this->y, sinAngle * this->x + cosAngle * this->x };
}
