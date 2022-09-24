#pragma once

#include <DxLib.h>

struct Vec2;

namespace utils {
    //! @brief valの小数以下point位を四捨五入する
    extern float round_point(float val, int point);
    //! @brief valを[min, max]の区間に収めるように修正した値を返す.
    template <typename T> T clamp(const T val, const T min, const T max);
    //! @brief -valからvalまでのランダムな数値を返す
    extern float rand_in_range(float val);
    //! @brief DxLibのDrawRotaGraphF関数を, 画面内のみの座標で扱えるようにラップした関数.
    extern int DrawRotaGraphF_Screen(float x, float y, float ExRate, float Angle, int GrHandle, int TransFlag = FALSE, int TurnFlag = FALSE);
    //! @brief 球同士の当たり判定を行う. r1, 2は半径.
    extern bool sphere_collision(Vec2 pos1, Vec2 pos2, float r1, float r2);
}

