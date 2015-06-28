#ifndef TYPES_HPP
#define TYPES_HPP

#include <memory>
#include "type_alias.hpp"
#include "Visitor.hpp"

class Expr;

enum class StorageClass {
    None = 0x0,
    Const = 0x1,
};

enum class BasicType {
    None,
    Void,
    Bool,
    Char,

    Uint_8,
    Uint_16,
    Uint_32,
    Uint_64,

    Int_8,
    Int_16,
    Int_32,
    Int_64,

    Size_t,

    Float_32,
    Float_64,
    Float_80
};

#if ENV_64_BIT
    #define SIZE_T_SIZE 64
#else
    #define SIZE_T_SIZE 32
#endif

static u16_t BasicTypeSize[] = {0, 0, 8, 1, 8, 16, 32, 64, 8, 16, 32, 64, SIZE_T_SIZE, 32, 64, 80};

class Type {
private:
    BasicType _base;
    StorageClass _stc;

public:
    static const std::shared_ptr<const Type> Void;
    static const std::shared_ptr<const Type> Char;
    static const std::shared_ptr<const Type> Bool;

    static const std::shared_ptr<const Type> Int8;
    static const std::shared_ptr<const Type> Int16;
    static const std::shared_ptr<const Type> Int32;
    static const std::shared_ptr<const Type> Int64;

    static const std::shared_ptr<const Type> Uint8;
    static const std::shared_ptr<const Type> Uint16;
    static const std::shared_ptr<const Type> Uint32;
    static const std::shared_ptr<const Type> Uint64;

    static const std::shared_ptr<const Type> Size_t;

    static const std::shared_ptr<const Type> Float32;
    static const std::shared_ptr<const Type> Float64;
    static const std::shared_ptr<const Type> Float80;

    explicit Type(BasicType base, StorageClass stc = StorageClass::None) : _base(base), _stc(stc) { }

    StorageClass getSTC() const {
        return _stc;
    }

    virtual bool isBaseType() const {
        return true;
    }

    const Type* getNext() const {
        return nullptr;
    }

    BasicType getBasicType() const {
        return _base;
    }

    virtual void accept(Visitor* v) const {
        v->visit(this);
    }
};

class TypeNext : public Type {
private:
    const std::shared_ptr<const Type> _next;

public:
    explicit TypeNext(const std::shared_ptr<const Type> next, StorageClass stc = StorageClass::None) :  Type(BasicType::None, stc), _next(next) { }

    virtual bool isBaseType() const {
        return false;
    }

    virtual const Type* toBaseType() const;

    const Type* getNext() const {
        return _next.get();
    }

    virtual void accept(Visitor*) const = 0;
};

class TypePointer : public TypeNext {
public:
    static const std::shared_ptr<const TypePointer> TypeString;

    explicit TypePointer(const std::shared_ptr<const Type> next, StorageClass stc = StorageClass::None) : TypeNext(next, stc) { }

    virtual void accept(Visitor* v) const {
        v->visit(this);
    }
};

class TypeDynamicArray : public TypeNext {
public:
    explicit TypeDynamicArray(const std::shared_ptr<const Type> next, StorageClass stc = StorageClass::None) : TypeNext(next, stc) { }

    virtual void accept(Visitor* v) const {
        v->visit(this);
    }
};

class TypeStaticArray : public TypeNext {
private:
    u32_t _dim = 0;

public:
    explicit TypeStaticArray(const std::shared_ptr<const Type> next, u32_t dim, StorageClass stc = StorageClass::None) : TypeNext(next, stc), _dim(dim) { }

    u32_t getDim() const {
        return _dim;
    }

    virtual void accept(Visitor* v) const {
        v->visit(this);
    }
};

bool isNumeric(BasicType);
bool isIntegral(BasicType);
bool isFloat(BasicType);

enum class Signed : u16_t {
    None,
    No,
    Yes,
};

Signed isSigned(BasicType);

enum class Match : u16_t {
    No,
    Exact,
    Convert,
};

Match matchType(BasicType, BasicType);
BasicType deduceType(const Expr*);

#endif
