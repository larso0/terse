#ifndef TERSE_OPERATOR_H
#define TERSE_OPERATOR_H

#include <string>

namespace Terse {

    namespace Associativity {
        enum {
            None = 0,
            Left = 1 << 16,
            Right = 2 << 16
        };
    }

    namespace OperatorType {
        enum {
            None = 0,
            Unary = 1 << 18,
            Binary = 2 << 18
        };
    }

    namespace Operator {
        enum {
            None = 0,
            IncrementPostfix = 1 | (1 << 8) | Associativity::Left | OperatorType::Unary,
            DecrementPostfix = 2 | (1 << 8) | Associativity::Left | OperatorType::Unary,
            MemberAccessUnary = 3 | (1 << 8) | Associativity::Right | OperatorType::Unary,
            MemberAccess = 4 | (1 << 8) | Associativity::Left | OperatorType::Binary,
            IncrementPrefix = 5 | (2 << 8) | Associativity::Right | OperatorType::Unary,
            DecrementPrefix = 6 | (2 << 8) | Associativity::Right | OperatorType::Unary,
            Negate = 7 | (2 << 8) | Associativity::Right | OperatorType::Unary,
            Not = 8 | (2 << 8) | Associativity::Right | OperatorType::Unary,
            Multiply = 9 | (3 << 8) | Associativity::Left | OperatorType::Binary,
            Divide = 10 | (3 << 8) | Associativity::Left | OperatorType::Binary,
            Remainder = 11 | (3 << 8) | Associativity::Left | OperatorType::Binary,
            Add = 12 | (4 << 8) | Associativity::Left | OperatorType::Binary,
            Subtract = 13 | (4 << 8) | Associativity::Left | OperatorType::Binary,
            Less = 14 | (5 << 8) | Associativity::Left | OperatorType::Binary,
            LessOrEqual = 15 | (5 << 8) | Associativity::Left | OperatorType::Binary,
            Greater = 16 | (5 << 8) | Associativity::Left | OperatorType::Binary,
            GreaterOrEqual = 17 | (5 << 8) | Associativity::Left | OperatorType::Binary,
            Equal = 18 | (6 << 8) | Associativity::Left | OperatorType::Binary,
            NotEqual = 19 | (6 << 8) | Associativity::Left | OperatorType::Binary,
            And = 20 | (7 << 8) | Associativity::Left | OperatorType::Binary,
            Or = 21 | (8 << 8) | Associativity::Left | OperatorType::Binary,
            Assign = 22 | (9 << 8) | Associativity::Right | OperatorType::Binary,
            AddAssign = 23 | (9 << 8) | Associativity::Right | OperatorType::Binary,
            SubtractAssign = 24 | (9 << 8) | Associativity::Right | OperatorType::Binary,
            MultiplyAssign = 25 | (9 << 8) | Associativity::Right | OperatorType::Binary,
            DivideAssign = 26 | (9 << 8) | Associativity::Right | OperatorType::Binary
        };
    }

    inline int precedenceOf(int op) {
        return (op & ~(~0 << 16)) >> 8;
    }

    inline int associativityOf(int op) {
        return op & (3 << 16);
    }

    inline int operatorType(int op) {
        return op & (~0 << 18);
    }

    int toOperator(const std::string& token, bool prevWasValue);

    std::string toToken(int op);

}

#endif
