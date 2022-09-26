#pragma once

#include <DxLib.h>
#include <string>
#include <vector>
#include <array>
#include "singleton.hpp"

class SoundEffectManager final : public Singleton<SoundEffectManager> {
public:
    SoundEffectManager();
    ~SoundEffectManager() = default;
    void load();
    void release();

    void play_se(int num) const;

private:
    /**
     * @brief 効果音を読み込み, ハンドルをリストに格納する.
     */
    void app_load_sound(std::string filename);
    std::vector<int> _se_list;
};
