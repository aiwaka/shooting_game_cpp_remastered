#include "se_manager.hpp"
#include "macro.hpp"

SoundEffectManager::SoundEffectManager() {
    // �ŏ��ɗ��p�s�\�������l�Ŗ��߂�
    _se_list = std::array<int, 30>{};
    _play_flag = std::array<int, 30>{};
    for (int i = 0; i < 30; ++i) {
        _se_list[i] = -1;
        _play_flag[i] = 0;
    }
    load();
}

void SoundEffectManager::load() {
    // 0
    app_load_sound("dat/se/enemy_death.wav", 0);
    app_load_sound("dat/se/chshot.wav", 1);
    app_load_sound("dat/se/player_dead.wav", 2);
    app_load_sound("dat/se/hit.wav", 3);
    app_load_sound("dat/se/boss_death.wav", 4);
    // 5
    app_load_sound("dat/se/enemy_shot.wav", 5);
    app_load_sound("dat/se/boss_change.wav", 6);
    app_load_sound("dat/se/bom0.wav", 7);
    app_load_sound("dat/se/bom1.wav", 8);
    app_load_sound("dat/se/kettei.wav", 9);
    // 10
    app_load_sound("dat/se/item_get.wav", 10);
}

void SoundEffectManager::release() {
    const size_t size = _se_list.size();
    for (size_t i = 0; i < size; ++i) {
        DeleteSoundMem(_se_list[i]);
        _se_list[i] = -1;
    }
}

void SoundEffectManager::app_load_sound(std::string filename, int target_num) {
    if (target_num < 0 && _se_list.size() <= target_num) APP_SYSTEM_ERROR("SE�ԍ����s���ł�");
    int handle = LoadSoundMem(filename.c_str());
    _se_list[target_num] = handle;
}


void  SoundEffectManager::set_se(int num) {
    if (num < 0 && _se_list.size() <= num) APP_SYSTEM_ERROR("SE�ԍ����s���ł�");
    _play_flag[num] = 1;
}
void  SoundEffectManager::play_se() {
    for (int i = 0; i < 30; ++i) {
        if (_play_flag[i] == 1) {
            // �Đ��t���O�������Ă���ꍇ, �Đ������ǂ����𒲂ׂĎ~�߂Ă���Đ�����
            if (CheckSoundMem(_se_list[i]) != 0) {
                StopSoundMem(_se_list[i]);
            }
            PlaySoundMem(_se_list[i], DX_PLAYTYPE_BACK);
            _play_flag[i] = 0;
        }
    }
}
