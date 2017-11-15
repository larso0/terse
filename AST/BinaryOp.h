#ifndef TERSE_BINARYOP_H
#define TERSE_BINARYOP_H

#include "Expression.h"
#include "Operator.h"
#include <memory>

namespace Terse {

    class BinaryOp : public Expression {
    public:
        BinaryOp() : op(Operator::None) {}

        BinaryOp(int op, std::shared_ptr<Expression> l, std::shared_ptr<Expression> r) :
                op(op), left(l), right(r) {}

        int op;
        std::shared_ptr<Expression> left, right;
    };

}

#endif
