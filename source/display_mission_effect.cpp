#include "display_mission_effect.hpp"
#include "global_define.hpp"
#include "image_manager.hpp"
#include "utils.hpp"

DisplayMissionEffect::DisplayMissionEffect() : AbstractEffect()
{
    _handle = ImageManager::get_instance()->get_mission_display();
}

bool DisplayMissionEffect::update() {
    if (get_counter() == 400) finish();
    return true;
}

void DisplayMissionEffect::draw() const {
    int counter = get_counter();
    int opacity = counter < 32 ? counter * 8 : counter > 336 ? 255 - (counter - 336) * 4 : 255;
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, opacity);
    utils::DrawRotaGraphF_Screen(static_cast<float>(GlobalValues::CENTER_X), static_cast<float>(GlobalValues::CENTER_Y), 1.0, 0.0, _handle, 1);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}