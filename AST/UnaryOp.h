#ifndef TERSE_UNARYOP_H
#define TERSE_UNARYOP_H

#include "Expression.h"
#include "Operator.h"
#include <memory>

namespace Terse {

    class UnaryOp : public Expression {
    public:
        UnaryOp() : op(Operator::None) {}

        UnaryOp(int op, std::shared_ptr<Expression> e) : op(op), expression(e) {}

        int op;
        std::shared_ptr<Expression> expression;
    };

}

#endif
