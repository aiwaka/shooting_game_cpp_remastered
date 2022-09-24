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
    //! @brief �����摜��p���ė^����ꂽ������`�悷��.
    //! @param pos_x, pos_y : �\������ʒu�̍���̓_�̍��W
    //! @param num : �\�����鐔�l
    //! @param max_digit : �ő包��
    void _draw_num(int pos_x, int pos_y, int num, int max_digit) const;
};
