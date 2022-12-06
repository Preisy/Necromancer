#pragma once
template<class T>
class SingletonRepository {
    static inline SingletonRepository* instance = nullptr;
    T* data = nullptr;

    template<class...Args>
    SingletonRepository() {

    }

    SingletonRepository(const SingletonRepository &) = default;

public:
    static SingletonRepository* getInstance() {
        if (instance == nullptr) instance = new SingletonRepository();
        return instance;
    }
};
