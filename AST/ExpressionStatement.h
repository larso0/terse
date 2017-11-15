#ifndef TERSE_EXPRESSIONSTATEMENT_H
#define TERSE_EXPRESSIONSTATEMENT_H

#include "Statement.h"
#include "Expression.h"
#include <memory>

namespace Terse {

    class ExpressionStatement : public Statement {
    public:
        ExpressionStatement() {}
        ExpressionStatement(std::shared_ptr<Expression> e) : expression(e) {}

        virtual ~ExpressionStatement() {}

        std::shared_ptr<Expression> expression;
    };

}

#endif
