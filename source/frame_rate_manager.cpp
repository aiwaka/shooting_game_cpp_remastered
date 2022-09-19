#pragma once

#include <DxLib.h>
#include "frame_rate_manager.hpp"
#include "global_define.hpp"
#include "utils.hpp"

// 無名名前空間で内部リンケージとする
namespace {
    const size_t LIST_LEN_MAX = 120;
    const int FPS = 60;
    // リスト更新の間隔. 60フレームに一回更新する.
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
    // リストが空なら待たなくていい
    if (list_len == 0) {
        return 0;
    }
    // リストの先頭のカウントからどれくらい進んでいるかを計算することで毎フレーム誤差を修正できる.
    // 理論上リストの先頭から今までにかかるべき時間
    int should_take_time = static_cast<int>(1000.0f * static_cast<float>(list_len) / static_cast<float>(FPS));
    // 待つべき時間は今の理論上のカウント-現在のカウントでOK
    int wait_time = _list.front() + should_take_time - GetNowCount();
    wait_time = wait_time > 0 ? wait_time : 0;
    return static_cast<unsigned int>(wait_time);
}

void FrameRateManager::updateAverage() {
    size_t list_len = _list.size();
    if (list_len < LIST_LEN_MAX) {
        return;
    }
    // LIST_LEN_MAX-1フレームにかかった時間（ms）
    int taken_time = _list.back() - _list.front();
    // 1フレームの間の平均時間
    float average = static_cast<float>(taken_time) / static_cast<float>(static_cast<int>(list_len) - 1);
    if (average == 0.0f) {
        return;
    }
    this->_fps = utils::round_point(1000.0f / average, 2);
}
