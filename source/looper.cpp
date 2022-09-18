#include "looper.hpp"
#include "error.hpp"
#include "title_scene.hpp"
#include "game_scene.hpp"
#include "macro.hpp"

Looper::Looper() {
    SceneParameter param;
    // タイトルシーンを作成して追加し初期化
    // Looperはリスナー抽象クラスを継承しており, シーンのリスナーにはthisポインタを渡す.
    _scene_stack.push(std::make_shared<TitleScene>(this, param));
}

/**
 * @brief スタックの一番上にあるシーンについて処理を行う
 */
bool Looper::loop() {
    _scene_stack.top()->update();
    _scene_stack.top()->draw();
    _frm.draw();
    // このwaitにより一定時間間隔でupdateやdrawが実行されることになる.
    _frm.wait();
    return true;
}

/**
 * @brief シーン変更（各シーンからコールバックとして呼び出される）
 * @param scene 変更先のシーン
 * @param parameter 前のシーンから引き継ぐパラメータ
 * @param stackClear 現在のシーンのスタックをクリアするか
 */
void Looper::on_scene_changed(const AppScenes scene, const SceneParameter& param, const bool stack_clear) {
    if (stack_clear) {
        while (!_scene_stack.empty()) {
            _scene_stack.pop();
        }
    }
    switch (scene)
    {
    case Title:
        _scene_stack.push(std::make_shared<TitleScene>(this, param));
        break;
    case Game:
        _scene_stack.push(std::make_shared<GameScene>(this, param));
        break;
    default:
        APP_SYSTEM_ERROR("シーンエラー");
        break;
    }
}