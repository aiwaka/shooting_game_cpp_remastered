#pragma once

#include <cmath>
#include "utils.hpp"

struct Vec2
{
    float x;
    float y;

    constexpr Vec2() : x(0.0f), y(0.0f) {};

    constexpr Vec2(float _x, float _y) : x(_x), y(_y) {};


    //! ���`���
    Vec2 lerp(const Vec2& target, const float param) const;


    //! @brief �R���X�g���N�^�̈��. �p�x����P�ʃx�N�g���𐶐�.
    constexpr static Vec2 from_angle(const float angle) {
        return Vec2{ std::cos(angle), std::sin(angle) };
    }
    //! @brief �p�x�����̕����ɒ�����ۂ���90�x��]�������x�N�g��
    constexpr Vec2 perp() const {
        return Vec2{ -y, x };
    }
    //! @brief �����̈ʒu�x�N�g���Ƃ̋�����Ԃ�.
    float distance(const Vec2 _rhs) const;
    //! @brief �����̒����̓���Ԃ�.
    float length_square() const;
    //! @brief �����̒�����Ԃ�.
    float length() const;
    //! @brief ������X������̊p�x��Ԃ�.
    float angle() const;
    //! @brief �����Ƃ̓��ς̒l��Ԃ�.
    float dot(const Vec2 _rhs) const;
    //! @brief �񎟌��ł̊O�ς��Ƃ�, ���Ȃ킿�O�����ɂ�����xy���ʏ�x�N�g�����m�̃N���X�ς�z������Ԃ�.
    float perp_dot(const Vec2 _rhs) const;
    //! @brief �����̊p�x����]�������x�N�g����Ԃ�.
    Vec2 rotate(const float angle) const;
    //! @brief ���K�������x�N�g����Ԃ�.
    Vec2 normalized() const;
    //! @brief min�x�N�g����max�x�N�g���ɂ���`�͈̔͂Ɏ��߂��x�N�g����Ԃ�
    Vec2 clamp(const Vec2 min, const Vec2 max) const;

    //! ���Z�q�I�[�o�[���[�h
    // unary plus �͎��g�̃C���X�^���X�̒l��Ԃ��΂悢�i�R�s�[�����H�j
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

    /// ����������Z�q
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
//// �p�x�v�Z.
//#define F_PI			((float)M_PI)
//#define F_2PI			((float)(M_PI*2.0))
//#define RAD2DEG(a)		(((a)*180.0f/F_PI))														// ���W�A�����x.
//#define DEG2RAD(a)		(((a)*F_PI/180.0f))														// �x�����W�A��.
//#define ANGLE(a)		DEG2RAD(a)																// �x�����W�A��.
//#define FIT_DEG(x)		(((x)>180.0f) ? ((x)-360.0f) : (((x)<=-180.0f) ? ((x)+360.0f) : (x)))	// �p�x�␳( -180.0 <= x <= 180.0 ).
//#define FIT_RAD(x)		(((x)>F_PI) ? ((x)-F_2PI) : (((x)<=-F_PI) ? ((x)+F_2PI) : (x)))			// ���W�A���␳( -F_PI <= x <= F_PI ).
//#define FIT_ANGLE(x)	(((x)>=360.0f) ? ((x)-360.0f) : ((x) < 0.0f) ? ((x)+360.0f) : (x))		// �p�x�␳( 0.0 <= x <= 360.0 ).
//#define IS_FIT_ANGLE(x)	(((x)<=360.0f) && ((x)>=0.0f))											// �p�x�`�F�b�N.

