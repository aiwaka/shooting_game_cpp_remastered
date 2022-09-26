#include <DxLib.h>
#include "global_define.hpp"
#include "image_manager.hpp"
#include "background.hpp"

const static float SCROLL_SPEED = 2.0f;

Background::Background(int initial_type) {
    _handles = ImageManager::get_instance()->get_background();
    _img_height = 0;
    set_bg(initial_type);
}

void Background::set_bg(int type) {
    _bg_type = type;
    auto handle = _handles[type];
    GetGraphSize(handle, nullptr, &_img_height);
    for (size_t i = 0; i < BG_NUM; ++i) {
        _list[i] = std::make_shared<Quadrangle>(0.0f, static_cast<float>(_img_height * static_cast<int>(i)), handle);
    }
}

bool Background::update() {
    switch (_bg_type)
    {
    case 0:
    case 1:
    case 5:
    case 6:
        break;
    case 2:
    case 3:
    case 4:
        for (size_t i = 0; i < BG_NUM; ++i) {
            _list[i]->pos.y += SCROLL_SPEED;
            if (_list[i]->pos.y > 2 * _img_height) {
                _list[i]->pos.y -= _img_height * BG_NUM;
            }
        }
        break;
    default:
        break;
    }

    return true;
}

void Background::draw() const {
    SetDrawArea(0, 0, GlobalValues::OUT_WIDTH, GlobalValues::OUT_HEIGHT);
    switch (_bg_type)
    {
    case 0:
    case 1:
    case 5:
        DrawGraphF(_list[0]->pos.x, _list[0]->pos.y, _list[0]->img, 0);
        break;
    case 6:
        // É{ÉXópîwåi
        DrawGraph(GlobalValues::IN_TOP_LEFT_X, GlobalValues::IN_TOP_LEFT_Y, _handles[6], 0);
        DrawGraph(GlobalValues::IN_TOP_LEFT_X, GlobalValues::IN_TOP_LEFT_Y, _handles[5], 1);
        break;
    case 2:
    case 3:
    case 4:
        for (size_t i = 0; i < BG_NUM; ++i) {
            DrawGraphF(_list[i]->pos.x, _list[i]->pos.y, _list[i]->img, 0);
        }
        break;
    default:
        break;
    }
    SetDrawArea(0, 0, GlobalValues::SCREEN_WIDTH, GlobalValues::SCREEN_HEIGHT);
}