#include "Type.hpp"
#include "TypeVisitor.hpp"
#include "Expression.hpp"

const std::shared_ptr<const Type> Type::Void = std::make_shared<const Type>(BasicType::Void);
const std::shared_ptr<const Type> Type::Char = std::make_shared<const Type>(BasicType::Char);
const std::shared_ptr<const Type> Type::Bool = std::make_shared<const Type>(BasicType::Bool);

const std::shared_ptr<const Type> Type::Int8 = std::make_shared<const Type>(BasicType::Int_8);
const std::shared_ptr<const Type> Type::Int16 = std::make_shared<const Type>(BasicType::Int_16);
const std::shared_ptr<const Type> Type::Int32 = std::make_shared<const Type>(BasicType::Int_32);
const std::shared_ptr<const Type> Type::Int64 = std::make_shared<const Type>(BasicType::Int_64);

const std::shared_ptr<const Type> Type::Uint8 = std::make_shared<const Type>(BasicType::Uint_8);
const std::shared_ptr<const Type> Type::Uint16 = std::make_shared<const Type>(BasicType::Uint_16);
const std::shared_ptr<const Type> Type::Uint32 = std::make_shared<const Type>(BasicType::Uint_32);
const std::shared_ptr<const Type> Type::Uint64 = std::make_shared<const Type>(BasicType::Uint_64);

const std::shared_ptr<const Type> Type::Size_t = std::make_shared<const Type>(BasicType::Size_t);

const std::shared_ptr<const Type> Type::Float32 = std::make_shared<const Type>(BasicType::Float_32);
const std::shared_ptr<const Type> Type::Float64 = std::make_shared<const Type>(BasicType::Float_64);
const std::shared_ptr<const Type> Type::Float80 = std::make_shared<const Type>(BasicType::Float_80);

const std::shared_ptr<const TypePointer> TypePointer::TypeString = std::make_shared<const TypePointer>(Type::Char, StorageClass::Const);

const Type* TypeNext::toBaseType() const {
    const Type* type = _next.get();
    while (!type->isBaseType()) {
        type = type->getNext();
    }

    return type;
}

bool isNumeric(BasicType ty) {
    switch (ty) {
        case BasicType::Int_8:
        case BasicType::Int_16:
        case BasicType::Int_32:
        case BasicType::Int_64:
        case BasicType::Uint_8:
        case BasicType::Uint_16:
        case BasicType::Uint_32:
        case BasicType::Uint_64:
        case BasicType::Size_t:
        case BasicType::Float_32:
        case BasicType::Float_64:
        case BasicType::Float_80:
            return true;
        default:
            return false;
    }
}

bool isIntegral(BasicType ty) {
    switch (ty) {
        case BasicType::Int_8:
        case BasicType::Int_16:
        case BasicType::Int_32:
        case BasicType::Int_64:
        case BasicType::Uint_8:
        case BasicType::Uint_16:
        case BasicType::Uint_32:
        case BasicType::Uint_64:
        case BasicType::Size_t:
            return true;
        default:
            return false;
    }
}

bool isFloat(BasicType ty) {
    switch (ty) {
        case BasicType::Float_32:
        case BasicType::Float_64:
        case BasicType::Float_80:
            return true;
        default:
            return false;
    }
}

Signed isSigned(BasicType ty) {
    switch (ty) {
        case BasicType::Int_8:
        case BasicType::Int_16:
        case BasicType::Int_32:
        case BasicType::Int_64:
        case BasicType::Float_32:
        case BasicType::Float_64:
        case BasicType::Float_80:
            return Signed::Yes;
        case BasicType::Uint_8:
        case BasicType::Uint_16:
        case BasicType::Uint_32:
        case BasicType::Uint_64:
        case BasicType::Size_t:
            return Signed::No;
        default:
            return Signed::None;
    }
}

Match matchType(BasicType lhs, BasicType rhs) {
    if (lhs == rhs)
        return Match::Exact;

    if (isNumeric(lhs) && isNumeric(rhs)) {
        const u16_t lhs_size = BasicTypeSize[static_cast<u16_t>(lhs)];
        const u16_t rhs_size = BasicTypeSize[static_cast<u16_t>(rhs)];

        if (isIntegral(lhs) && isIntegral(rhs)) {
            if (isSigned(lhs) == isSigned(rhs)) {
                if (lhs_size >= rhs_size)
                    return Match::Exact;
            }

            return Match::Convert;
        }

        if (isFloat(lhs) && isFloat(rhs)) {
            if (lhs_size >= rhs_size)
                return Match::Exact;
            return Match::Convert;
        }

        if (isFloat(lhs) && isIntegral(rhs)) {
            if (lhs_size >= rhs_size)
                return Match::Exact;
            return Match::Convert;
        }
    }

    return Match::No;
}

BasicType deduceType(const Expr* exp) {
    TypeVisitor tv;
    exp->accept(&tv);

    return tv.getType();
}
