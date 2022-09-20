#pragma once

#include <DxLib.h>

namespace utils {
    //! @brief val�̏����ȉ�point�ʂ��l�̌ܓ�����
    extern float round_point(float val, int point);
    //! @brief val��[min, max]�̋�ԂɎ��߂�悤�ɏC�������l��Ԃ�.
    extern float clamp(const float val, const float min, const float max);
    //! @brief DxLib��DrawRotaGraphF�֐���, ��ʓ��݂̂̍��W�ň�����悤�Ƀ��b�v�����֐�.
    extern int DrawRotaGraphF_Screen(float x, float y, float ExRate, float Angle, int GrHandle, int TransFlag = FALSE, int TurnFlag = FALSE);
}
