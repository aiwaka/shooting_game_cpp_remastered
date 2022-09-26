#include "music_manager.hpp"
#include "macro.hpp"


MusicManager::MusicManager() {
    // 最初に利用不可能を示す値で埋める
    _info_list = std::array<MusicInfo, 10>{};
    _handle = -1;
    _loop_count = -1;
    set_param();
}

// 手動で色々追加
void MusicManager::set_param() {
    _info_list[0] = MusicInfo("./dat/music/title.wav", 0);
    _info_list[1] = MusicInfo("./dat/music/0_0.wav", 0);
    _info_list[2] = MusicInfo("./dat/music/0_1.wav", 7459);
    _info_list[3] = MusicInfo("./dat/music/ed2.wav", 0);
}

MusicManager::MusicInfo::MusicInfo() : filename(""), loop_count(-1) {}
MusicManager::MusicInfo::MusicInfo(std::string filename, int loop_count) : filename(filename), loop_count(loop_count) {}

void MusicManager::play_music(int num) {
    // 今鳴っている曲を削除
    StopSoundMem(_handle);
    DeleteSoundMem(_handle);
    // 番号に対応したファイルをロード
    auto& info = _info_list[num];
    int loop_count = info.loop_count;
    if (loop_count == -1) APP_SYSTEM_ERROR("BGM番号が無効です");
    this->_loop_count = loop_count;
    _handle = LoadSoundMem(info.filename.c_str());

    // ループをセット
    SetLoopPosSoundMem(_loop_count, _handle);
    // 再生
    PlaySoundMem(_handle, DX_PLAYTYPE_LOOP);
}
