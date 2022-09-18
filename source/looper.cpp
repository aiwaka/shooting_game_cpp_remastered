#include "looper.hpp"
#include "title_scene.hpp"
#include "error.hpp"

Looper::Looper() {
    SceneParameter param;
    // タイトルシーンを作成して追加し初期化
    // Looperはリスナー抽象クラスを継承しており, シーンのリスナーにはthisポインタを渡す.
    _scene_stack.push(std::make_shared<TitleScene>(this, param));
}
Looper::~Looper() {}

/**
 * @brief スタックの一番上にあるシーンについて処理を行う
 */
bool Looper::loop() const {
    _scene_stack.top()->update();
    _scene_stack.top()->draw();
    return true;
}

/**
 * @brief シーン変更（各シーンからコールバックされる）
 * @param scene 変更するシーンのenum
 * @param parameter 前のシーンから引き継ぐパラメータ
 * @param stackClear 現在のシーンのスタックをクリアするか
 */
void Looper::on_scene_changed(const GameScene scene, const SceneParameter& param, const bool stack_clear) {}