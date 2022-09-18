#pragma once

#include <array>
#include "singleton.hpp"

/**
 * @brief シングルトンとしてキーボード入力を管理するクラス. なおKeyCodeはenum的に扱うので命名規則の例外としている.
 */
class Keyboard final : public Singleton<Keyboard> {
    //friend Singleton<Keyboard>;

public:
    Keyboard() = default;
    bool update();
    //! @brief KeyCodeのキーが押されているフレーム数を取得.
    int get_pressing_count(int KeyCode);
    int get_releasing_count(int KeyCode);

private:
    // キーの総数
    static const int KEY_NUM = 256;
    std::array<int, KEY_NUM> _pressing_count;
    std::array<int, KEY_NUM> _releasing_count;
    // KeyCodeが有効であるか
    bool is_available_code(int KeyCode);
};
