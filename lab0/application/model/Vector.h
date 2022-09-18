#pragma once

namespace Models {

    template<class T>
    class Vector {
    T* arr = nullptr;
    int len = 0;

public:
    Vector() = default;

    explicit Vector(int len) : len(len) {
        arr = new T[len]();
    }

    int getLen() { return len; };

    T& operator[](int index) {
        if (index >= len)
            throw std::out_of_range("index out of range");
        return arr[index];
    }

    ~Vector() {
        delete[] arr;
    }

    Vector(const Vector &) = delete;
    Vector(Vector &&) = delete;
    Vector& operator=(const Vector &) = delete;
    Vector& operator=(Vector && other) noexcept {
        arr = other.arr;
        len = other.len;
        other.arr = nullptr;
        other.len = 0;

        return *this;
    };
};

}
