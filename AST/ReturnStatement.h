#ifndef TERSE_RETURNSTATEMENT_H
#define TERSE_RETURNSTATEMENT_H

#include "ExpressionStatement.h"

namespace Terse {

    class ReturnStatement : public ExpressionStatement {
    public:
        ReturnStatement() {}
        ReturnStatement(std::shared_ptr<Expression> expr) : ExpressionStatement(expr) {}
    };

}

#endif
