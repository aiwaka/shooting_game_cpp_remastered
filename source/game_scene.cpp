#include <DxLib.h>
#include <algorithm>
#include "game_scene.hpp"
#include "result_scene.hpp"
#include "display_mission_effect.hpp"
#include "global_define.hpp"
#include "music_manager.hpp"

const char* GameScene::param_tag_stage = "param_tag_stage";
const char* GameScene::param_tag_level = "param_tag_level";

GameScene::GameScene(IOnSceneChangedListener* impl, const SceneParameter& param) : AbstractScene(impl, param) {
    _score = 0;
    //_counter = 0;

    // ���y���Đ�
    MusicManager::get_instance()->play_music(1);
    // �X�e�[�W�ƃ��x�����擾
    _stage = param.get_param(this->param_tag_stage);
    _level = param.get_param(this->param_tag_level);
    int player_max_hp = 0;
    GlobalValues::Level game_level = static_cast<GlobalValues::Level>(_level);
    switch (game_level)
    {
    case GlobalValues::Easy:
        player_max_hp = 99;
        break;
    case GlobalValues::Normal:
        player_max_hp = 60;
        break;
    case GlobalValues::Hard:
        player_max_hp = 30;
        break;
    case GlobalValues::Inferno:
        player_max_hp = 1;
        break;
    default:
        break;
    }

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
    _player = std::make_shared<Player>(this, _player_bullet_manager, player_max_hp);
    _item_manager = std::make_shared<ItemManager>(this);
}

bool GameScene::update() {
    if (_player->get_lives_num() == -1) {
        // �I���A�V�[���`�F���W
        SceneParameter param;

        param.set_param(ResultScene::param_tag_level, _level);
        param.set_param(ResultScene::param_tag_score, _score);
        _impl_scene_changed->on_scene_changed(AppScenes::Result, param, true);
        return true;
    }
    if (_enemy_manager->get_counter() == 100) {
        auto mission = std::make_shared<DisplayMissionEffect>();
        _effect_manager->push_effect(mission);
    }
    if (_enemy_manager->get_counter() == 3500) {
        // �I���A�V�[���`�F���W
        SceneParameter param;

        param.set_param(ResultScene::param_tag_level, _level);
        param.set_param(ResultScene::param_tag_score, _score);
        _impl_scene_changed->on_scene_changed(AppScenes::Result, param, true);
        return true;
    }

    // ���ׂĂ̏�����true�ȏꍇ��true��Ԃ��ă��[�v�𑱍s
    std::vector<bool> result_set = std::vector<bool>(0);
    // �����̏������ɋC�����Ȃ���1�t���[���������x��邱�Ƃ����肻��
    result_set.push_back(_background->update());
    result_set.push_back(_player->update());
    result_set.push_back(_enemy_bullet_manager->update());
    result_set.push_back(_enemy_manager->update());
    result_set.push_back(_boss_manager->update());
    result_set.push_back(_player_bullet_manager->update());
    result_set.push_back(_item_manager->update());
    result_set.push_back(_effect_manager->update());
    result_set.push_back(_board->update());

    // ���ׂĂ�Task���p�������N���X��update�̌��ʂ�true�ł����OK, �����Ȃ���false���Ԃ�Q�[���I��
    return std::all_of(result_set.begin(), result_set.end(), [](bool b) {return b; });
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
