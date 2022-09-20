#pragma once

#include <DxLib.h>

namespace utils {
    //! @brief valの小数以下point位を四捨五入する
    extern float round_point(float val, int point);
    //! @brief valを[min, max]の区間に収めるように修正した値を返す.
    extern float clamp(const float val, const float min, const float max);
    //! @brief DxLibのDrawRotaGraphF関数を, 画面内のみの座標で扱えるようにラップした関数.
    extern int DrawRotaGraphF_Screen(float x, float y, float ExRate, float Angle, int GrHandle, int TransFlag = FALSE, int TurnFlag = FALSE);
}
