#pragma once

/**
 * @brief �V���O���g���̒��ۃN���X.
 */
template <typename T>
class Singleton {
protected:
    Singleton() = default;
    virtual ~Singleton() = default;
    Singleton(const Singleton& r) = default;
    Singleton& operator=(const Singleton& r) = default;

public:
    static T* get_instance() {
        static T instance;
        return &instance;
    }
};
