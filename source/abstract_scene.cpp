#include "abstract_scene.hpp"

AbstractScene::AbstractScene(IOnSceneChangedListener* impl, const SceneParameter& param) : _impl_scene_changed(impl) {}