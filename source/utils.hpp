#pragma once

#include <DxLib.h>

struct Vec2;

namespace utils {
    //! @brief val�̏����ȉ�point�ʂ��l�̌ܓ�����
    extern float round_point(float val, int point);
    //! @brief val��[min, max]�̋�ԂɎ��߂�悤�ɏC�������l��Ԃ�.
    template <typename T> T clamp(const T val, const T min, const T max);
    //! @brief -val����val�܂ł̃����_���Ȑ��l��Ԃ�
    extern float rand_in_range(float val);
    //! @brief DxLib��DrawRotaGraphF�֐���, ��ʓ��݂̂̍��W�ň�����悤�Ƀ��b�v�����֐�.
    extern int DrawRotaGraphF_Screen(float x, float y, float ExRate, float Angle, int GrHandle, int TransFlag = FALSE, int TurnFlag = FALSE);
    //! @brief �����m�̓����蔻����s��. r1, 2�͔��a.
    extern bool sphere_collision(Vec2 pos1, Vec2 pos2, float r1, float r2);
}

