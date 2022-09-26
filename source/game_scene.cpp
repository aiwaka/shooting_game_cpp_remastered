#include <DxLib.h>
#include "game_scene.hpp"
#include "display_mission_effect.hpp"
#include "music_manager.hpp"

const char* GameScene::param_tag_stage = "param_tag_stage";
const char* GameScene::param_tag_level = "param_tag_level";

GameScene::GameScene(IOnSceneChangedListener* impl, const SceneParameter& param) : AbstractScene(impl, param) {
    _score = 0;
    //_counter = 0;

    // ���y���Đ�
    MusicManager::get_instance()->play_music(1);
    // �X�e�[�W���擾
    _stage = param.get_param(this->param_tag_stage);
    // �w�i�ԍ������
    int bg_idx = _stage + 2;

    // _background��AbstractBackground�̃|�C���^����, Background�͂�����p�����Ă���̂Ŋ��S�Ȍ`�ŃL���X�g�\
    _background = std::make_shared<Background>(bg_idx);
    //_level = param.get_param(this->param_tag_level);
    _board = std::make_shared<Board>(this);
    _enemy_bullet_manager = std::make_shared<EnemyBulletManager>(this);
    _enemy_manager = std::make_shared<EnemyManager>(this, _enemy_bullet_manager);
    _boss_manager = std::make_shared<BossManager>(this, _enemy_bullet_manager);
    _player_bullet_manager = std::make_shared<PlayerBulletManager>(this);
    _effect_manager = std::make_shared<EffectManager>(this);
    _player = std::make_shared<Player>(this, _player_bullet_manager);
    _item_manager = std::make_shared<ItemManager>(this);
}

void GameScene::update() {
    if (_player->get_lives_num() == -1) {
        // �I���A�V�[���`�F���W
        SceneParameter param;
        _impl_scene_changed->on_scene_changed(AppScenes::Title, param, true);
        return;
    }
    if (_enemy_manager->get_counter() == 100) {
        auto mission = std::make_shared<DisplayMissionEffect>();
        _effect_manager->push_effect(mission);
    }
    if (_enemy_manager->get_counter() == 3500) {
        // �I���A�V�[���`�F���W
        SceneParameter param;
        _impl_scene_changed->on_scene_changed(AppScenes::Title, param, true);
        return;
    }

    // �����̏������ɋC�����Ȃ���1�t���[���������x��邱�Ƃ����肻��
    _background->update();
    _player->update();
    _enemy_bullet_manager->update();
    _enemy_manager->update();
    _boss_manager->update();
    _player_bullet_manager->update();
    _item_manager->update();
    _effect_manager->update();
    _board->update();
    //++_counter;
}

void GameScene::draw() const {
    // �����ł̏��Ԃ��`�揇�ɂȂ�.
    _background->draw();
    _effect_manager->draw();
    _item_manager->draw();
    _player_bullet_manager->draw();
    _player->draw();
    _enemy_bullet_manager->draw();
    // �G�e����ɓG��`�悷��
    _boss_manager->draw();
    _enemy_manager->draw();
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

std::list<std::shared_ptr<Boss>> GameScene::get_all_boss_iterator() const {
    return this->_boss_manager->get_all_boss_iterator();
}
void GameScene::set_effect(std::shared_ptr<AbstractEffect> effect) {
    _effect_manager->push_effect(effect);
}

void GameScene::spawn_items(std::array<int, 6>& items, Vec2 pos) {
    for (int type : items) {
        _item_manager->push_item(pos, type);
    }
}
