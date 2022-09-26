#include "music_manager.hpp"
#include "macro.hpp"


MusicManager::MusicManager() {
    // �ŏ��ɗ��p�s�\�������l�Ŗ��߂�
    _info_list = std::array<MusicInfo, 10>{};
    _handle = -1;
    _loop_count = -1;
    set_param();
}

// �蓮�ŐF�X�ǉ�
void MusicManager::set_param() {
    _info_list[0] = MusicInfo("./dat/music/title.wav", 0);
    _info_list[1] = MusicInfo("./dat/music/0_0.wav", 0);
    _info_list[2] = MusicInfo("./dat/music/0_1.wav", 7459);
    _info_list[3] = MusicInfo("./dat/music/ed2.wav", 0);
}

MusicManager::MusicInfo::MusicInfo() : filename(""), loop_count(-1) {}
MusicManager::MusicInfo::MusicInfo(std::string filename, int loop_count) : filename(filename), loop_count(loop_count) {}

void MusicManager::play_music(int num) {
    // �����Ă���Ȃ��폜
    StopSoundMem(_handle);
    DeleteSoundMem(_handle);
    // �ԍ��ɑΉ������t�@�C�������[�h
    auto& info = _info_list[num];
    int loop_count = info.loop_count;
    if (loop_count == -1) APP_SYSTEM_ERROR("BGM�ԍ��������ł�");
    this->_loop_count = loop_count;
    _handle = LoadSoundMem(info.filename.c_str());

    // ���[�v���Z�b�g
    SetLoopPosSoundMem(_loop_count, _handle);
    // �Đ�
    PlaySoundMem(_handle, DX_PLAYTYPE_LOOP);
}
