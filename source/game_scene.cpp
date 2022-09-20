#include "game_scene.hpp"
#include <DxLib.h>

const char* GameScene::param_tag_stage = "param_tag_stage";
const char* GameScene::param_tag_level = "param_tag_level";

GameScene::GameScene(IOnSceneChangedListener* impl, const SceneParameter& param) : AbstractScene(impl, param) {
    // _background��AbstractBackground�̃|�C���^����, Background�͂�����p�����Ă���̂Ŋ��S�Ȍ`�ŃL���X�g�\
    _background = std::make_shared<Background>();
    //_level = param.get_param(this->param_tag_level);
    _player = std::make_shared<Player>();
    _board = std::make_shared<Board>();
    _enemy_manager = std::make_shared<EnemyManager>();
}

void GameScene::update() {
    _background->update();
    _player->update();
    _enemy_manager->update();
    _board->update();
}

void GameScene::draw() const {
    // �����ł̏��Ԃ��`�揇�ɂȂ�.
    _background->draw();
    _player->draw();
    _enemy_manager->draw();
    _board->draw();
    //DrawFormatString(100, 100, GetColor(255, 255, 255), "level %d", _level);
}


