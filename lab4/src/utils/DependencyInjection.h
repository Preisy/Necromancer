#pragma once

#include <type_traits>
#include <utility>

template<class T>
class Factory;


#define injectAsSingleton(Class, ...) \
template<>                            \
class Factory<Class> {                \
    class FactorySingleton {          \
        Class data = Class(__VA_ARGS__); \
                                      \
        static inline FactorySingleton* inst = nullptr; \
        FactorySingleton() = default;               \
        FactorySingleton(const FactorySingleton &) = delete; \
        FactorySingleton& operator=(const FactorySingleton &) = delete; \
        friend class Factory;\
    public:\
        static FactorySingleton* getInstance() {\
            if (inst == nullptr) inst = new FactorySingleton(); \
            return inst;\
        } \
    };                                 \
public:                               \
    Class* inst = &FactorySingleton::getInstance()->data;                                       \
};                                    \

#define injectAsRuntime(Class, ...) \
template<>                            \
class Factory<Class> {                \
    class FactorySingleton {          \
        static inline Class* inst = nullptr; \
        FactorySingleton() = default;               \
        FactorySingleton(const FactorySingleton &) = default;\
    public:\
        static Class* getInstance() { \
            if (inst == nullptr)      \
                inst = new Class(__VA_ARGS__); \
            return inst;\
        }; \
    };                                 \
public:                               \
    Class* inst = FactorySingleton::getInstance();                                       \
};

#define injectAsObject(Interface, Implementation, ...) \
template<>                         \
class Factory<Interface> {             \
public:                            \
    Interface* inst = new Implementation(__VA_ARGS__); \
    ~Factory() {                   \
        delete inst;                               \
    }                              \
};                                                     \

template<class T>
concept InjectedClass = std::is_default_constructible_v<Factory<T>>;


template<InjectedClass T>
class Injected {
    Factory<T> factory;

public:
    T* operator->() {
        return factory.inst;
    }
    T & operator*() {
        return *factory.inst;
    }
};

template<class T, class...Args>
Injected<T> configureInjecting(Args&&...args) {
    Factory<T> factory;
    factory.inst->~T();
    ::new (factory.inst) T(std::forward<Args>(args)...);
    return Injected<T>();
}











