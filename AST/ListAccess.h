#ifndef TERSE_LISTACCESS_H
#define TERSE_LISTACCESS_H

#include "Expression.h"
#include <memory>

namespace Terse {

    class ListAccess : public Expression {
    public:
        ListAccess() {}
        ListAccess(std::shared_ptr<Expression> expr, std::shared_ptr<Expression> i) : expression(expr), index(i) {}

        std::shared_ptr<Expression> expression;
        std::shared_ptr<Expression> index;
    };

}

#endif
