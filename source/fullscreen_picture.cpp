#include <DxLib.h>
#include "global_define.hpp"
#include "image_manager.hpp"
#include "fullscreen_picture.hpp"

FullScreenPicture::FullScreenPicture(int initial_type) {
    set_bg(initial_type);
}

void FullScreenPicture::set_bg(int type) {
    _bg_type = type;
    _handle = ImageManager::get_instance()->get_background()[type];
}

bool FullScreenPicture::update() {
    return true;
}

void FullScreenPicture::draw() const {
    DrawGraphF(0, 0, _handle, 0);
}