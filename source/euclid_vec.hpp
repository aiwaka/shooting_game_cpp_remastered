#pragma once

#include <cmath>
#include "utils.hpp"

struct Vec2
{
    float x;
    float y;

    constexpr Vec2() : x(0.0f), y(0.0f) {};

    constexpr Vec2(float _x, float _y) : x(_x), y(_y) {};


    //! 線形補間
    Vec2 lerp(const Vec2& target, const float param) const;


    //! @brief コンストラクタの一種. 角度から単位ベクトルを生成.
    constexpr static Vec2 from_angle(const float angle) {
        return Vec2{ std::cos(angle), std::sin(angle) };
    }
    //! @brief 角度が正の方向に長さを保って90度回転させたベクトル
    constexpr Vec2 perp() const {
        return Vec2{ -y, x };
    }
    //! @brief 引数の位置ベクトルとの距離を返す.
    float distance(const Vec2 _rhs) const;
    //! @brief 自分の長さの二乗を返す.
    float length_square() const;
    //! @brief 自分の長さを返す.
    float length() const;
    //! @brief 自分のX軸からの角度を返す.
    float angle() const;
    //! @brief 引数との内積の値を返す.
    float dot(const Vec2 _rhs) const;
    //! @brief 二次元での外積をとり, すなわち三次元におけるxy平面上ベクトル同士のクロス積のz成分を返す.
    float perp_dot(const Vec2 _rhs) const;
    //! @brief 引数の角度分回転させたベクトルを返す.
    Vec2 rotate(const float angle) const;
    //! @brief 正規化したベクトルを返す.
    Vec2 normalized() const;
    //! @brief minベクトルとmaxベクトルによる矩形の範囲に収めたベクトルを返す
    Vec2 clamp(const Vec2 min, const Vec2 max) const;

    //! 演算子オーバーロード
    // unary plus は自身のインスタンスの値を返せばよい（コピーされる？）
    constexpr Vec2 operator +() const {
        return *this;
    }

    constexpr Vec2 operator -() const {
        return Vec2{ -x, -y };
    }

    constexpr Vec2 operator +(const Vec2& _rhs) const {
        return Vec2{ this->x + _rhs.x, this->y + _rhs.y };
    }
    constexpr Vec2 operator -(const Vec2& _rhs) const {
        return Vec2{ this->x - _rhs.x, this->y - _rhs.y };
    }

    constexpr Vec2 operator *(float _rhs) const {
        return Vec2{ x * _rhs, y * _rhs };
    }
    constexpr Vec2 operator /(float _rhs) const {
        return Vec2{ x / _rhs, y / _rhs };
    }

    /// 複合代入演算子
    Vec2& operator +=(const Vec2& _rhs) {
        x += _rhs.x;
        y += _rhs.y;
        return *this;
    }
    Vec2& operator -=(const Vec2& _rhs) {
        x -= _rhs.x;
        y -= _rhs.y;
        return *this;
    }
    Vec2& operator *=(const float _rhs) {
        x *= _rhs;
        y *= _rhs;
        return *this;
    }
    Vec2& operator /=(const float _rhs) {
        x /= _rhs;
        y /= _rhs;
        return *this;

    }
};


inline Vec2 operator *(float a, const Vec2& vec) {
    return Vec2{ a * vec.x, a * vec.y };
}


//#define MIN(a, b)		((a) > (b))? (b): (a)
//#define MAX(a, b)		((a) >= (b))? (a): (b)
//#define COUNTOF(a)		((sizeof a)/(sizeof a[0]))
//
//
//// 角度計算.
//#define F_PI			((float)M_PI)
//#define F_2PI			((float)(M_PI*2.0))
//#define RAD2DEG(a)		(((a)*180.0f/F_PI))														// ラジアン→度.
//#define DEG2RAD(a)		(((a)*F_PI/180.0f))														// 度→ラジアン.
//#define ANGLE(a)		DEG2RAD(a)																// 度→ラジアン.
//#define FIT_DEG(x)		(((x)>180.0f) ? ((x)-360.0f) : (((x)<=-180.0f) ? ((x)+360.0f) : (x)))	// 角度補正( -180.0 <= x <= 180.0 ).
//#define FIT_RAD(x)		(((x)>F_PI) ? ((x)-F_2PI) : (((x)<=-F_PI) ? ((x)+F_2PI) : (x)))			// ラジアン補正( -F_PI <= x <= F_PI ).
//#define FIT_ANGLE(x)	(((x)>=360.0f) ? ((x)-360.0f) : ((x) < 0.0f) ? ((x)+360.0f) : (x))		// 角度補正( 0.0 <= x <= 360.0 ).
//#define IS_FIT_ANGLE(x)	(((x)<=360.0f) && ((x)>=0.0f))											// 角度チェック.

