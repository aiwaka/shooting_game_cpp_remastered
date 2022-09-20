#include <DxLib.h>
#include "global_define.hpp"
#include "image_manager.hpp"
#include "board.hpp"

bool Board::update() {
    return true;
}

void Board::draw() const {
    auto board_handle = ImageManager::get_instance()->get_board();
    DrawGraph(0, 0, board_handle[0], 1);
    DrawGraph(0, GlobalValues::IN_TOP_LEFT_Y, board_handle[1], 1);
    DrawGraph(0, GlobalValues::IN_TOP_LEFT_Y + GlobalValues::IN_HEIGHT, board_handle[2], 1);
    DrawGraph(GlobalValues::OUT_WIDTH, 0, board_handle[3], 1);
}