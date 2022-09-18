#include "scene_parameter.hpp"

void SceneParameter::set_param(std::string key, int val) {
    _param_map.insert(std::make_pair(key, val));
}

int SceneParameter::get_param(std::string key) const {
    decltype(_param_map)::const_iterator iter = _param_map.find(key);
    if (_param_map.end() == iter) {
        return this->Error;
    }
    else {
        return iter->second;
    }
}