#include "title_scene.hpp"
#include <DxLib.h>

TitleScene::TitleScene(IOnSceneChangedListener* impl, const SceneParameter& param) : AbstractScene(impl, param) {}

void TitleScene::update() {

}

void TitleScene::draw() {
    DrawString(100, 100, "title", GetColor(255, 255, 255));
}