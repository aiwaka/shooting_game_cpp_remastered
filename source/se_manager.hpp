#pragma once

#include <DxLib.h>
#include <string>
#include <array>
#include "singleton.hpp"

class SoundEffectManager final : public Singleton<SoundEffectManager> {
public:
    SoundEffectManager();
    ~SoundEffectManager() = default;
    void load();
    void release();

    //! @brief num�Ԃ̌��ʉ��̍Đ����Z�b�g����.
    void set_se(int num);
    void play_se();

private:
    /**
     * @brief ���ʉ���ǂݍ���, �n���h�������X�g�Ɋi�[����.
     */
    void app_load_sound(std::string filename, int target_num);
    std::array<int, 30> _se_list;
    //! @brief 1�t���[���ɓ������ʉ��͈�����Đ����Ăق����Ȃ�. ���t���[���t���O�������Ă��邩�ǂ������Ă���Đ�����.
    std::array<int, 30> _play_flag;
};
