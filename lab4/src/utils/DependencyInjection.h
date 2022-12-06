#pragma once

template<class T>
class Factory;


#define injectAsSingleton(Class, ...) \
template<>                            \
class Factory<Class> {                \
    class FactorySingleton {          \
        static inline Class* inst = nullptr; \
        FactorySingleton() = default;               \
        FactorySingleton(const FactorySingleton &) = default;\
    public:\
        static Class* getInstance() {\
            if (inst == nullptr) inst = new Class(__VA_ARGS__); \
            return inst;\
        } \
    };                                 \
public:                               \
    Class* inst = FactorySingleton::getInstance();                                       \
};                                    \

#define injectAsRuntime(Class) \
template<>                            \
class Factory<Class> {                \
    class FactorySingleton {          \
        static inline Class* inst = nullptr; \
        FactorySingleton() = default;               \
        FactorySingleton(const FactorySingleton &) = default;\
    public:\
        static Class* getInstance() { \
            if (inst == nullptr)      \
                inst = reinterpret_cast<Class*>(new uint8_t[sizeof(Class)]); \
            return inst;\
        }; \
    };                                 \
public:                               \
    Class* inst = FactorySingleton::getInstance();                                       \
};

template<class T>
concept InjectedClass = std::is_default_constructible_v<Factory<T>>;


template<InjectedClass T>
class Injected {
    Factory<T> factory;

public:
    T* operator->() {
        return factory.inst;
    }
};

template<class T, class...Args>
Injected<T> configureInjecting(Args&&...args) {
    Factory<T> factory;
    *factory.inst = T(std::forward<Args>(args)...);
    return Injected<T>();
}











