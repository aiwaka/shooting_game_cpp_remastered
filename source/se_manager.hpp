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

    //! @brief num番の効果音の再生をセットする.
    void set_se(int num);
    void play_se();

private:
    /**
     * @brief 効果音を読み込み, ハンドルをリストに格納する.
     */
    void app_load_sound(std::string filename, int target_num);
    std::array<int, 30> _se_list;
    //! @brief 1フレームに同じ効果音は一つしか再生してほしくない. 毎フレームフラグが立っているかどうか見てから再生する.
    std::array<int, 30> _play_flag;
};
