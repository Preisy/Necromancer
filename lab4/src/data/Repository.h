#pragma once

#include <unordered_map>
#include <memory>
#include <optional>

template<class Model>
class Repository {
    class SingletonRepository {
        static inline SingletonRepository* instance = nullptr;

        std::unordered_map<int, Model> data;

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
//    std::optional<const Model &> insert(int id, Model && model) {
//        auto res = instance->data.insert({id, std::make_shared<Model>(std::move(model))});
//        if (bool status = res.second) {
//            return {*res.first->second};
//        } else {
//            return {};
//        }
//    }

    bool insert(int id, Model && model) {
        auto res = instance->data.emplace(id, std::move(model));
        return res.second;
    }


    bool insert(int id, const Model & model) {
        auto res = instance->data.emplace(id, model);
        return res.second;
    }

    std::optional<Model> find(int id) {
        auto res = instance->data.find(id);
        if (res == instance->data.end())
            return {};
        else
            return {res->second};
    }

    bool erase(int id) {
        return instance->data.erase(id) == 1;
    }

    std::unordered_map<int, Model> getAll() {
        auto res = std::unordered_map<int, Model>(instance->data.size());
        auto it = (*instance->data.begin());
        for (const auto & item : instance->data) {
            res.emplace(item.first, item.second);
        }
        return res;
    }

    ~Repository() = default;
};