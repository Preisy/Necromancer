#pragma once

#include <unordered_map>
#include <memory>

template<class Key, class Value>
class Repository {
    class SingletonRepository {
        static inline SingletonRepository* instance = nullptr;

        std::unordered_map<Key, std::shared_ptr<Value>> data;
        int lastPrimaryKey = 0;

        SingletonRepository() = default;

        SingletonRepository(const SingletonRepository &) = default;

        SingletonRepository & operator=(const SingletonRepository &) = default;

    public:
        friend class Repository;

        static SingletonRepository* getInstance() {
            if (instance == nullptr) instance = new SingletonRepository();
            return instance;
        }
    };

    SingletonRepository* instance = SingletonRepository::getInstance();

public:
    using iterator = typename std::unordered_map<Key, std::shared_ptr<Value>>::iterator;

    iterator begin() {
        return instance->data.begin();
    }
    iterator end() {
        return instance->data.end();
    }

    std::pair<iterator, bool> insert(const std::shared_ptr<Value> & el) {
        return instance->data.insert({++instance->lastPrimaryKey, el});
    }

    std::pair<iterator, bool> insert(std::shared_ptr<Value> && el) {
        return instance->data.insert({++instance->lastPrimaryKey, std::move(el)});
    }

    template<class...Args>
    std::pair<iterator, bool> emplace(Args && ...args) {
        return instance->data.emplace(++instance->lastPrimaryKey, std::make_shared<Value>(std::forward<Args>(args)...));
    }

    iterator erase(iterator el) {
        return instance->data.erase(el);
    }

    bool erase(const Key & key) {
        return instance->data.erase(key) == 1;
    }

    iterator find(const Key & key) {
        return instance->data.find(key);
    }

    Value& operator[](const Key & key) {
        return instance->data[key];
    }

    Value& operator[](Key && key) {
        return instance->data[std::move(key)];
    }

};
