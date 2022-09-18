#pragma once

#include <list>

class FrameRateManager {
public:
    FrameRateManager();
    //! @brief �t���[�����[�g�Ǘ��̂��߂ɑҋ@��X�V���s��.
    void wait();
    //! @brief fps�`��. �X�V���̏����͍s��Ȃ��̂ŕ`�悳�������Ȃ��ꍇ�͌Ăяo���Ȃ���΂���.
    void draw() const;

private:
    //! @brief �uWindows���N�����Ă���̌o�ߎ��ԁims�j�v����ׂĕۑ�����z��
    std::list<int> _list;
    float _fps;
    unsigned int _counter;

    //! @brief �Ăяo�����ƌ��݂̎��Ԃ��L�^��, ���X�g�T�C�Y�����ȏ�ɂȂ�ΌÂ����̂���������.
    void regist();
    //! @brief ���߂̈�莞�ԋ�Ԃ���FPS���v�Z
    void updateAverage();
    //! @brief FPS���w�肳�ꂽ���̂ɂ��邽�߂ɂ��̃t���[���ő҂ׂ����ԁims�j���v�Z����
    unsigned int getWaitTime() const;

};
