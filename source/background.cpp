#include <DxLib.h>
#include "global_define.hpp"
#include "image_manager.hpp"
#include "background.hpp"


const static int IMG_HEIGHT = 480;
const static float SCROLL_SPEED = 2.0f;

// NOTE: player�N���X�̃R���X�g���N�^�ł̓n���h����ۑ�����悤�Ȃ��Ƃ͂��Ă��Ȃ�.
//       �n���h���̃R�s�[�Ȃǂقڕ���0�Ȃ̂ł��̓s�x�擾����ق����悳��...?
Background::Background() {
    for (size_t i = 0; i < BG_NUM; ++i) {
        auto handle = ImageManager::get_instance()->get_background();
        _list[i] = std::make_shared<Quadrangle>(0.0f, static_cast<float>(IMG_HEIGHT * static_cast<int>(i)), handle);
    }
}

bool Background::update() {
    for (size_t i = 0; i < BG_NUM; ++i) {
        _list[i]->pos.y += SCROLL_SPEED;
        if (_list[i]->pos.y > IMG_HEIGHT) {
            _list[i]->pos.y -= IMG_HEIGHT * BG_NUM;
        }
    }
    return true;
}

void Background::draw() const {
    SetDrawArea(0, 0, GlobalValues::OUT_WIDTH, GlobalValues::OUT_HEIGHT);
    for (size_t i = 0; i < BG_NUM; ++i) {
        DrawGraphF(_list[i]->pos.x, _list[i]->pos.y, _list[i]->img, 0);
    }
    SetDrawArea(0, 0, GlobalValues::SCREEN_WIDTH, GlobalValues::SCREEN_HEIGHT);
}