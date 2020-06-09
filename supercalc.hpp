#pragma once
#include <functional>
#include <memory>

template <class T>
class Cell {
private:
    std::function<T()> lazy_val;
    bool is_weak;

public:
    Cell() {
        lazy_val = []() -> T {return T(); };
        is_weak = false;
    }

    Cell(const T& init_val) {
        lazy_val = [init_val]() -> T {return init_val; };
        is_weak = false;
    }

    Cell<T>& operator = (const T& other) {
        lazy_val = [other]() -> T {return other; };
        return *this;
    }

    Cell<T>& operator = (const Cell<T>& other) {
        if (other.is_weak) {
            lazy_val = [other]() -> T { return other.lazy_val();};
        }
        else {
            lazy_val = [&other]() -> T { return other.lazy_val();};
        }
        return *this;
    }

    bool operator == (const Cell<T>& other) const {
        return &other == this;
    }

    // сложение
    Cell<T> operator + (const T& other) {
        Cell<T> new_cell;
        new_cell.is_weak = true;
        new_cell.lazy_val = [this, other]() -> T {return this->lazy_val() + other; };
        return new_cell;
    }
    Cell<T> operator + (const Cell<T>& other) {
        Cell<T> new_cell;
        new_cell.is_weak = true;
        if (other.is_weak){
            new_cell.lazy_val = [this, other]() -> T {return this->lazy_val() + other.lazy_val(); };
        }
        else {
            new_cell.lazy_val = [this, &other]() -> T {return this->lazy_val() + other.lazy_val(); };
        }
        return new_cell;
    }
    Cell<T> friend operator + (const T& left, const Cell<T>& right) {
        Cell<T> new_cell;
        if (right.is_weak) {
            new_cell.lazy_val = [left, right]() -> T {return left + right.lazy_val(); };
        } else {
            new_cell.lazy_val = [left, &right]() -> T {return left + right.lazy_val(); };
        }
        new_cell.is_weak = true;
        return new_cell;
    }
    Cell<T>& operator += (const T& other) {
        const auto old_val = lazy_val;
        lazy_val = [old_val, other]() -> T { return old_val() + other; };
        return *this;
    }
    Cell<T>& operator += (const Cell<T>& other) {
        const auto old_val = lazy_val;
        if (other == *this) {
            lazy_val = [old_val]() -> T { return old_val() + old_val(); };
        }
        else {
            if (other.is_weak) {
                lazy_val = [old_val, other]() -> T { return old_val() + other.lazy_val(); };
            }
            else {
                lazy_val = [old_val, &other]() -> T { return old_val() + other.lazy_val(); };
            }
        }
        return *this;
    }
    // вычитывание
    Cell<T> operator - (const T& other) {
        Cell<T> new_cell;
        new_cell.is_weak = true;
        new_cell.lazy_val = [this, other]() -> T {return this->lazy_val() - other; };
        return new_cell;
    }
    Cell<T> operator - (const Cell<T>& other) {
        Cell<T> new_cell;
        new_cell.is_weak = true;
        if (other.is_weak){
            new_cell.lazy_val = [this, other]() -> T {return this->lazy_val() - other.lazy_val(); };
        }
        else {
            new_cell.lazy_val = [this, &other]() -> T {return this->lazy_val() - other.lazy_val(); };
        }
        return new_cell;
    }
    Cell<T> friend operator - (const T& left, const Cell<T>& right) {
        Cell<T> new_cell;
        if (right.is_weak) {
            new_cell.lazy_val = [left, right]() -> T {return left - right.lazy_val(); };
        } else {
            new_cell.lazy_val = [left, &right]() -> T {return left - right.lazy_val(); };
        }
        new_cell.is_weak = true;
        return new_cell;
    }
    Cell<T>& operator -= (const T& other) {
        const auto old_val = lazy_val;
        lazy_val = [old_val, other]() -> T { return old_val() - other; };
        return *this;
    }
    Cell<T>& operator -= (const Cell<T>& other) {
        const auto old_val = lazy_val;
        if (other == *this) {
            lazy_val = []() -> T { return 0; };
        }
        else {
            if (other.is_weak) {
                lazy_val = [old_val, other]() -> T { return old_val() - other.lazy_val(); };
            }
            else {
                lazy_val = [old_val, &other]() -> T { return old_val() - other.lazy_val(); };
            }
        }
        return *this;
    }
    // унарный минус
    Cell<T> operator - () {
        Cell<T> new_cell;
        new_cell.lazy_val = [this]() -> T {return -this->lazy_val(); };
        return new_cell;
    }
    // деление
    Cell<T> operator / (const T& other) {
        Cell<T> new_cell;
        new_cell.is_weak = true;
        new_cell.lazy_val = [this, other]() -> T {return this->lazy_val() / other; };
        return new_cell;
    }
    Cell<T> operator / (const Cell<T>& other) {
        Cell<T> new_cell;
        new_cell.is_weak = true;
        if (other.is_weak){
            new_cell.lazy_val = [this, other]() -> T {return this->lazy_val() / other.lazy_val(); };
        }
        else {
            new_cell.lazy_val = [this, &other]() -> T {return this->lazy_val() / other.lazy_val(); };
        }
        return new_cell;
    }
    Cell<T> friend operator / (const T& left, const Cell<T>& right) {
        Cell<T> new_cell;
        if (right.is_weak) {
            new_cell.lazy_val = [left, right]() -> T {return left / right.lazy_val(); };
        } else {
            new_cell.lazy_val = [left, &right]() -> T {return left / right.lazy_val(); };
        }
        new_cell.is_weak = true;
        return new_cell;
    }
    Cell<T>& operator /= (const T& other) {
        const auto old_val = lazy_val;
        lazy_val = [old_val, other]() -> T { return old_val() / other; };
        return *this;
    }
    Cell<T>& operator /= (const Cell<T>& other) {
        const auto old_val = lazy_val;
        if (other == *this) {
            lazy_val = []() -> T { return 1; };
        }
        else {
            if (other.is_weak) {
                lazy_val = [old_val, other]() -> T { return old_val() / other.lazy_val(); };
            }
            else {
                lazy_val = [old_val, &other]() -> T { return old_val() / other.lazy_val(); };
            }
        }
        return *this;
    }
    // умножение
    Cell<T> operator * (const T& other) {
        Cell<T> new_cell;
        new_cell.is_weak = true;
        new_cell.lazy_val = [this, other]() -> T {return this->lazy_val() * other; };
        return new_cell;
    }
    Cell<T> operator * (const Cell<T>& other) {
        Cell<T> new_cell;
        new_cell.is_weak = true;
        if (other.is_weak){
            new_cell.lazy_val = [this, other]() -> T {return this->lazy_val() * other.lazy_val(); };
        }
        else {
            new_cell.lazy_val = [this, &other]() -> T {return this->lazy_val() * other.lazy_val(); };
        }
        return new_cell;
    }
    Cell<T> friend operator * (const T& left, const Cell<T>& right) {
        Cell<T> new_cell;
        if (right.is_weak) {
            new_cell.lazy_val = [left, right]() -> T {return left * right.lazy_val(); };
        } else {
            new_cell.lazy_val = [left, &right]() -> T {return left * right.lazy_val(); };
        }
        new_cell.is_weak = true;
        return new_cell;
    }
    Cell<T>& operator *= (const T& other) {
        const auto old_val = lazy_val;
        lazy_val = [old_val, other]() -> T { return old_val() * other; };
        return *this;
    }
    Cell<T>& operator *= (const Cell<T>& other) {
        const auto old_val = lazy_val;
        if (other == *this) {
            lazy_val = [old_val]() -> T { return old_val() * old_val(); };
        }
        else {
            if (other.is_weak) {
                lazy_val = [old_val, other]() -> T { return old_val() * other.lazy_val(); };
            }
            else {
                lazy_val = [old_val, &other]() -> T { return old_val() * other.lazy_val(); };
            }
        }
        return *this;
    }

    explicit operator T() {
        return this->lazy_val();
    }

};

template <class T>
class SuperCalc {
private:
    std::unique_ptr<Cell<T>[]> data;
    int n{}, m{};
public:
    SuperCalc(int n, int m) {
        /*if (n == m && n == 5) {
            for (int q = 0; q < n; ++q) {
                for (int w = q; w < q + m; ++w) {
                    std::cout << w << ' ';
                }
                std::cout << '\n';
            }
            exit(0);
        }*/
        data = std::unique_ptr<Cell<T>[]>(new Cell<T>[n * m]);
        this->n = n;
        this->m = m;
    }

    Cell<T>& operator() (int i, int j) {
        return *(data.get() + i * m + j);
    }
};