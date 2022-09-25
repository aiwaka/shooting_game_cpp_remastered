#pragma once

#include <memory>
#include "abstract_scene.hpp"
#include "abstract_bg.hpp"

class TitleScene : public AbstractScene {
public:
    TitleScene(IOnSceneChangedListener* impl, const SceneParameter& param);
    virtual ~TitleScene() = default;

    void update() override;
    void draw() const override;

private:
    std::shared_ptr<AbstractBackground> _background;
};
