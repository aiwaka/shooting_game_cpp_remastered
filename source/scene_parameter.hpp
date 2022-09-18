#pragma once

#include <map>
#include <string>

class SceneParameter {
public:
    const static int Error = -1;

    SceneParameter() = default;
    virtual ~SceneParameter() = default;

    void set_param(std::string key, int val);
    int get_param(std::string key) const;

private:
    std::map<std::string, int> _param_map;
};
