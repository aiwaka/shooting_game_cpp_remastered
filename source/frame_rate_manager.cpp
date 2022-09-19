#pragma once

#include <DxLib.h>
#include "frame_rate_manager.hpp"
#include "global_define.hpp"
#include "utils.hpp"

// �������O��Ԃœ��������P�[�W�Ƃ���
namespace {
    const size_t LIST_LEN_MAX = 120;
    const int FPS = 60;
    // ���X�g�X�V�̊Ԋu. 60�t���[���Ɉ��X�V����.
    const int UPDATE_INTERVAL = 60;
}

FrameRateManager::FrameRateManager() : _counter(0), _fps(0) {}

void FrameRateManager::wait() {
    _counter++;
    Sleep(getWaitTime());
    regist();
    if (_counter == UPDATE_INTERVAL) {
        updateAverage();
        _counter = 0;
    }
}

void FrameRateManager::draw() const {
    if (_fps == 0) {
        return;
    }
    DrawFormatString(0, GlobalValues::SCREEN_HEIGHT - 30, GetColor(255, 255, 255), "%04.1ffps", _fps);
}

void FrameRateManager::regist() {
    _list.push_back(GetNowCount());
    if (_list.size() > LIST_LEN_MAX) {
        _list.pop_front();
    }
}

unsigned int FrameRateManager::getWaitTime() const {
    size_t list_len = _list.size();
    // ���X�g����Ȃ�҂��Ȃ��Ă���
    if (list_len == 0) {
        return 0;
    }
    // ���X�g�̐擪�̃J�E���g����ǂꂭ�炢�i��ł��邩���v�Z���邱�ƂŖ��t���[���덷���C���ł���.
    // ���_�ナ�X�g�̐擪���獡�܂łɂ�����ׂ�����
    int should_take_time = static_cast<int>(1000.0f * static_cast<float>(list_len) / static_cast<float>(FPS));
    // �҂ׂ����Ԃ͍��̗��_��̃J�E���g-���݂̃J�E���g��OK
    int wait_time = _list.front() + should_take_time - GetNowCount();
    wait_time = wait_time > 0 ? wait_time : 0;
    return static_cast<unsigned int>(wait_time);
}

void FrameRateManager::updateAverage() {
    size_t list_len = _list.size();
    if (list_len < LIST_LEN_MAX) {
        return;
    }
    // LIST_LEN_MAX-1�t���[���ɂ����������ԁims�j
    int taken_time = _list.back() - _list.front();
    // 1�t���[���̊Ԃ̕��ώ���
    float average = static_cast<float>(taken_time) / static_cast<float>(static_cast<int>(list_len) - 1);
    if (average == 0.0f) {
        return;
    }
    this->_fps = utils::round_point(1000.0f / average, 2);
}
