#pragma once

#include <stack>
#include <memory>
#include "abstract_scene.hpp"
#include "i_on_changed_listener.hpp"
#include "frame_rate_manager.hpp"

class Looper final : public IOnSceneChangedListener {
public:
    Looper();
    ~Looper() = default;
    bool loop();
    void on_scene_changed(const AppScenes scene, const SceneParameter& param, const bool clear_stack) override;

private:
    // シーンのスマートポインタをスタックすることでシーンスタックを表現する.
    // 抽象シーンのスタックとすることで継承後の型によらずに同じ名前の処理を行うことができる.
    std::stack<std::shared_ptr<AbstractScene>> _scene_stack;
    // ループを司るクラスがFPS管理を行う.
    FrameRateManager _frm;
};
