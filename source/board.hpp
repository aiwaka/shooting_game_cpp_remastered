#pragma once

#include "task.hpp"

class GameScene;

class Board final : public Task {
public:
    Board(GameScene* scene);
    virtual ~Board() = default;
    bool update() override;
    void draw() const override;

private:
    GameScene* _game_scene;
    //void drawFrame() const;
    void _draw_board_info() const;
    //! @brief 数字画像を用いて与えられた数字を描画する.
    //! @param pos_x, pos_y : 表示する位置の左上の点の座標
    //! @param num : 表示する数値
    //! @param max_digit : 最大桁数
    void _draw_num(int pos_x, int pos_y, int num, int max_digit) const;
};
