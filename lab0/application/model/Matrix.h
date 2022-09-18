#pragma once

#include <list>
#include <iostream>
#include "Matrix.h"

namespace Models {

    template<class T>
    class Matrix {
    public:
        class Dot {
        public:
            int i;
            int j;
            T value;

            Dot(int i, int j, T value) : i(i), j(j), value(value) {}

            int getI() const {
                return i;
            }

            int getJ() const {
                return j;
            }

            const T & getValue() const {
                return value;
            }

            void setValue(const T & value) {
                Dot::value = value;
            }
            void setValue(T && value) {
                Dot::value = std::move(value);
            }

            Dot(const Dot & dot) {
                i = dot.i;
                j = dot.j;
                value = dot.value;
            }
            Dot(Dot && dot)  noexcept {
                i = dot.i;
                j = dot.j;
                value = std::move(dot.value);

                dot.i = 0;
                dot.j = 0;
                dot.value = T();
            }
            Dot & operator=(const Dot & dot) {
                i = dot.i;
                j = dot.j;
                value = dot.value;
                return *this;
            };
            Dot & operator=(Dot && dot)  noexcept {
                i = dot.i;
                j = dot.j;
                value = std::move(dot.value);

                dot.i = 0;
                dot.j = 0;
                dot.value = T();

                return *this;
            };

        };
        class Line {
            friend class Matrix;

            std::list<Dot> list;
        public:
            int index;

        public:
            Line() : index(-1) {};

            explicit Line(int index) : index(index) {};



            Line(const Line &) = delete;

            Line(Line && line) noexcept {
                list = std::move(line.list);
                index = line.index;

                line.index = 0;
            };

            Line & operator=(const Line &) = delete;

            Line & operator=(Line && line) noexcept {
                list = std::move(line.list);
                index = line.index;

                line.index = 0;
                return *this;
            };

            template<class iterator_type, class return_value>
            class _NormalIterator {
                friend class Matrix::Line;
                iterator_type it;

            public:
                explicit _NormalIterator(const iterator_type & it) {
                    this->it = iterator_type(it);
                }

                return_value operator*() const {
                    return (*it);
                }

                _NormalIterator & operator++() {
                    ++it;
                    return *this;
                }
                const _NormalIterator operator++(int) {
                    _NormalIterator res = *this;
                    ++*this;
                    return res;
                }
                _NormalIterator & operator--() {
                    --it;
                    return *this;
                }
                const _NormalIterator operator--(int) {
                    _NormalIterator res = *this;
                    --*this;
                    return res;
                }

                bool operator==(const _NormalIterator & other) const {
                    return other.it == it;
                }
                bool operator!=(const _NormalIterator & other) const {
                    return other.it != it;
                }

            };

            typedef _NormalIterator<typename std::list<Dot>::iterator, Dot &> NormalIterator;
            typedef _NormalIterator<typename std::list<Dot>::const_iterator, const Dot &> ConstNormalIterator;

            NormalIterator begin() {
                return NormalIterator(list.begin());
            }

            NormalIterator end() {
                return NormalIterator(list.end());
            }
            ConstNormalIterator begin() const {
                return ConstNormalIterator(list.cbegin());
            }

            ConstNormalIterator end() const {
                return ConstNormalIterator(list.cend());
            }

        private:
            void insert(const NormalIterator & position, Dot & value) {
                list.insert(position.it, value);
            }
            void insert(const NormalIterator & position, Dot && value) {
                list.insert(position.it, std::move(value));
            }
        };

    private:
        std::list<Line> list;

    public:
        Matrix() = default;

        void insert(int i, int j, const T & value) {
            Line & line = insertLine(i);

            for (auto it = line.begin(); it != line.end(); ++it) {
                if ((*it).j > j) {
                    line.insert(it, Dot(i, j, value));
                    return;
                } else if ((*it).j == j) {
                    *it = Dot(i, j, value);
                    return;
                }
            }
            line.insert(line.end(), Dot(i, j, value));
        }

    private:
        Line & insertLine(int i) {
            for(auto it = list.begin(); it != list.end(); ++it) {
                if ((*it).index > i) {
                    auto jt = it;
                    ++it;
                    list.insert(it, Line(i));
                    ++jt;
                    return *jt;
                } else if ((*it).index == i) {
                    return *it;
                }
            }
            list.insert(list.end(), Line(i));

            return *--list.end();
        }

    public:
        int length() const {
            return list.size();
        }

    public:

        template<class iterator_type, class return_value>
        class _NormalIterator {
            friend class Matrix;
            iterator_type it;

        public:
            explicit _NormalIterator(const iterator_type & it) {
                this->it = iterator_type(it);
            }

            return_value operator*() {
                return *it;
            }
            _NormalIterator & operator++() {
                ++it;
                return *this;
            }
            const _NormalIterator operator++(int) {
                _NormalIterator res = *this;
                ++*this;
                return res;
            }
            _NormalIterator & operator--() {
                --it;
                return *this;
            }
            const _NormalIterator operator--(int) {
                _NormalIterator res = *this;
                --*this;
                return res;
            }

            bool operator==(const _NormalIterator & other) const {
                return other.it == it;
            }
            bool operator!=(const _NormalIterator & other) const {
                return other.it != it;
            }

        };

        typedef _NormalIterator<typename std::list<Line>::iterator, Line &> NormalIterator;
        typedef _NormalIterator<typename std::list<Line>::const_iterator, const Line &> ConstNormalIterator;

        void insert(const Matrix::NormalIterator & position, const T & value) {
            list.insert(position.it, value);
        }
        void insert(const Matrix::NormalIterator & position, T && value) {
            list.insert(position.it, std::move(value));
        }



        NormalIterator begin() {
            return NormalIterator(list.begin());
        }

        NormalIterator end() {
            return NormalIterator(list.end());
        }

        ConstNormalIterator begin() const {
            return ConstNormalIterator(list.cbegin());
        }

        ConstNormalIterator end() const {
            return ConstNormalIterator(list.cend());
        }

        Matrix(const Matrix &) = delete;

        Matrix(Matrix && other) {
            this->list = std::move(other.list);
            other.list = std::list<Line>();
        };

        Matrix & operator=(const Matrix &) = delete;

        Matrix & operator=(Matrix && other) noexcept {
            this->list = std::move(other.list);
            other.list = std::list<Line>();
            return *this;
        };
    };

}
