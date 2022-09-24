#include "game_scene.hpp"
#include <DxLib.h>

const char* GameScene::param_tag_stage = "param_tag_stage";
const char* GameScene::param_tag_level = "param_tag_level";

GameScene::GameScene(IOnSceneChangedListener* impl, const SceneParameter& param) : AbstractScene(impl, param) {
    _score = 0;

    // _backgroundはAbstractBackgroundのポインタだが, Backgroundはそれを継承しているので完全な形でキャスト可能
    _background = std::make_shared<Background>();
    //_level = param.get_param(this->param_tag_level);
    _board = std::make_shared<Board>(this);
    _enemy_manager = std::make_shared<EnemyManager>(this);
    _player_bullet_manager = std::make_shared<PlayerBulletManager>(this);
    _effect_manager = std::make_shared<EffectManager>(this);
    _player = std::make_shared<Player>(_player_bullet_manager);
}

void GameScene::update() {
    // ここの処理順に気をつけないと1フレーム処理が遅れることがありそう
    _background->update();
    _player->update();
    _enemy_manager->update();
    _player_bullet_manager->update();
    _effect_manager->update();
    _board->update();
}

void GameScene::draw() const {
    // ここでの順番が描画順になる.
    _background->draw();
    _player->draw();
    _enemy_manager->draw();
    _player_bullet_manager->draw();
    _effect_manager->draw();
    _board->draw();
    //DrawFormatString(100, 100, GetColor(255, 255, 255), "level %d", _level);
}


Vec2 GameScene::get_player_pos() const {
    return _player->get_pos();
}

std::array<int, 5> GameScene::get_player_info_for_board() const {
    return std::array<int, 5>{_score, _player->get_hp(), _player->get_power(), _player->get_lives_num(), _player->get_bombs_num()};
}
std::list<std::shared_ptr<AbstractEnemy>> GameScene::get_all_enemies_iterator() const {
    return this->_enemy_manager->get_all_enemies_iterator();
}
void GameScene::set_effect(std::shared_ptr<AbstractEffect> effect) {
    _effect_manager->push_effect(effect);
}
