#pragma once

#include <DxLib.h>
#include <string>
#include <array>
#include "singleton.hpp"

class MusicManager final : public Singleton<MusicManager> {
public:
    MusicManager();
    ~MusicManager() = default;

    //! @brief 読み込み・開放等を行う
    void play_music(int num);

private:
    //! @brief BGMファイルのパス, ループタイミング等をセットする
    void set_param();
    struct MusicInfo {
        std::string filename;
        int loop_count;
        MusicInfo();
        MusicInfo(std::string filename, int loop_count);
    };
    std::array<MusicInfo, 10> _info_list;
    int _handle;
    int _loop_count;
};
