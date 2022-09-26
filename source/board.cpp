#include <DxLib.h>
#include "global_define.hpp"
#include "image_manager.hpp"
#include "game_scene.hpp"
#include "board.hpp"


Board::Board(GameScene* scene) : _game_scene(scene)
{}

bool Board::update() {
    return true;
}

void Board::draw() const {
    auto board_handle = ImageManager::get_instance()->get_board();
    DrawGraph(0, 0, board_handle[0], 1);
    DrawGraph(0, GlobalValues::IN_TOP_LEFT_Y, board_handle[1], 1);
    DrawGraph(0, GlobalValues::IN_TOP_LEFT_Y + GlobalValues::IN_HEIGHT, board_handle[2], 1);
    // ボードの画像への割り振りが微妙な形なので少々補正が必要
    DrawGraph(GlobalValues::OUT_WIDTH - GlobalValues::IN_TOP_LEFT_X, 0, board_handle[3], 1);

    this->_draw_board_info();
}

void Board::_draw_board_info() const {
    static const int INFO_X = GlobalValues::OUT_WIDTH - 22;
    static const int INFO_Y = 90;
    static const int COL_INTERVAL = 30;
    static const unsigned int WHITE = 4294967295; // 32bit unsigned intの最大値

    auto info = _game_scene->get_player_info_for_board();
    const char* strings[5] = { "SCORE : ", "HP : ", "POWER : ", "LIFE : ", "BOMB : " };
    for (int i = 0; i < 5; ++i) {
        DrawString(INFO_X, INFO_Y + COL_INTERVAL * i, strings[i], WHITE);
        _draw_num(INFO_X + 80, INFO_Y + COL_INTERVAL * i, info[i], 8);
    }
}

void Board::_draw_num(int pos_x, int pos_y, int num, int max_digit) const {
    auto handles = ImageManager::get_instance()->get_numbers();
    for (int i = 1; i <= max_digit; ++i) {
        DrawRotaGraph(pos_x + 15 * (max_digit - i), pos_y, 0.5, 0.0, handles[num % 10], 1);
        num /= 10;
    }
}
