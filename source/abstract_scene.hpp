#pragma once

#include "i_on_changed_listener.hpp"
#include "scene_parameter.hpp"

class IOnSceneChangedListener;

/**
 * @brief シーンに必要なものをまとめた抽象クラス
 */
class AbstractScene {
protected:
    IOnSceneChangedListener* _impl_scene_changed;
public:
    /**
     * @brief 抽象クラスのコンストラクタ.
     * @param impl シーン変更のリスナー
     * @param parameter 前のシーンから渡されたパラメータ
     */
    AbstractScene(IOnSceneChangedListener* impl, const SceneParameter& param);
    virtual ~AbstractScene() = default;
    virtual void update() = 0;
    virtual void draw() const = 0;
};
