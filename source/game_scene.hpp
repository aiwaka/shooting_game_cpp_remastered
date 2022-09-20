#pragma once

#include <memory>
#include "abstract_scene.hpp"
#include "player.hpp"
#include "board.hpp"
#include "abstract_bg.hpp"
#include "background.hpp"
#include "enemy_manager.hpp"

class GameScene : public AbstractScene {
public:
    const static char* param_tag_stage;
    const static char* param_tag_level;

    GameScene(IOnSceneChangedListener* impl, const SceneParameter& param);
    virtual ~GameScene() = default;

    void update() override;
    void draw() const override;

    // ���@�̈ʒu��₢���킹����悤�ɂ���
    Vec2 get_player_pos() const;
private:
    //int _level;
    // �����ŃV�[�����œ��������̂ւ̃|�C���^��ێ����Ă���, update��draw��K�p���邱�ƂōX�V���s���Ă���.
    std::shared_ptr<Player> _player;
    std::shared_ptr<Board> _board;
    std::shared_ptr<AbstractBackground> _background;
    std::shared_ptr<EnemyManager> _enemy_manager;
};
