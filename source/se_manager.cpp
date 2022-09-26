#include "se_manager.hpp"
#include "macro.hpp"

SoundEffectManager::SoundEffectManager() {
    load();
}

void SoundEffectManager::load() {
    // 0
    app_load_sound("dat/se/enemy_death.wav");
    app_load_sound("dat/se/chshot.wav");
    app_load_sound("dat/se/player_dead.wav");
    app_load_sound("dat/se/hit.wav");
    app_load_sound("dat/se/boss_death.wav");
    // 5
    app_load_sound("dat/se/enemy_shot.wav");
    app_load_sound("dat/se/boss_change.wav");
    app_load_sound("dat/se/bom0.wav");
    app_load_sound("dat/se/bom1.wav");
    app_load_sound("dat/se/kettei.wav");
    // 10
    app_load_sound("dat/se/item_get.wav");
}

void SoundEffectManager::release() {
    const size_t size = _se_list.size();
    for (size_t i = 0; i < size; ++i) {
        DeleteSoundMem(_se_list[i]);
    }
    _se_list.clear();
}

void SoundEffectManager::app_load_sound(std::string filename) {
    int handle = LoadSoundMem(filename.c_str());
    _se_list.push_back(handle);
}


void  SoundEffectManager::play_se(int num) const {
    if (num < 0 && _se_list.size() <= num) APP_SYSTEM_ERROR("SE”Ô†‚ª•s³‚Å‚·");
    PlaySoundMem(_se_list[num], DX_PLAYTYPE_BACK);
}
