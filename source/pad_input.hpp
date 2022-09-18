#pragma once

#include <array>
#include "singleton.hpp"

enum PadInputType {
    Up,
    Down,
    Left,
    Right,
    Shot,
    Bomb,
    Slow,
    Start,
    Sub,
};

class PadInput final : public Singleton<PadInput> {
public:
    PadInput();
    ~PadInput() = default;
    void update();
    //! @brief パッドのボタンIDに対する入力を取得
    int get(PadInputType id) const;

private:
    /**
     * @brief パッドと、それに対応するキーボードの入力状態をマージする.
     * @brief キーボード入力と押下時間を比べて大きい方を採用することでパッド入力を想定した部分をキーボードでも操作できるようにする.
     */
    void merge();

    const static int PAD_KEY_NUM = 16;
    //! @brief どのボタンがどの入力に割り当てられているかを示す
    std::array<int, PAD_KEY_NUM> _id_assign;
    //! @brief パッドの入力状態
    std::array<int, PAD_KEY_NUM> _pad_input;
};
