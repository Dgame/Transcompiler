#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <memory>
#include <vector>
#include <type_traits>

#include "Visitor.hpp"
#include "type_alias.hpp"

class Instruction;
class Expr;

template <typename T>
class Array final {
private:
    std::vector<std::unique_ptr<T>> _data;

public:
    static_assert(
        std::is_base_of<Instruction, T>::value || std::is_base_of<Expr, T>::value,
        "Type must be a child of class Instruction or class Expr"
    );

    void add(T* data) {
        _data.emplace_back(data);
    }

    T* operator [](u16_t index) const {
        return _data[index].get();
    }

    u16_t count() const {
        return _data.size();
    }
};

#endif
