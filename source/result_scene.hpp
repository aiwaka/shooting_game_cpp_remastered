#pragma once

#include <memory>
#include <vector>
#include <string>
#include <utility>
#include "abstract_scene.hpp"
#include "abstract_bg.hpp"

class ResultScene : public AbstractScene {
public:
    // パラメータのラベルとして利用する
    const static char* param_tag_level;
    const static char* param_tag_score;

    ResultScene(IOnSceneChangedListener* impl, const SceneParameter& param);
    virtual ~ResultScene() = default;

    bool update() override;
    void draw() const override;

private:
    int _level;
    int _score;
    std::shared_ptr<AbstractBackground> _background;
};
