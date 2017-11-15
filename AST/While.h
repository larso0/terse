#ifndef TERSE_WHILE_H
#define TERSE_WHILE_H

#include "Statement.h"
#include "Expression.h"
#include <memory>
#include <vector>

namespace Terse {

    class While : public Statement {
    public:
        virtual ~While(){}

        std::shared_ptr<Expression> condition;
        std::vector<std::shared_ptr<Statement>> block;
    };

    class DoWhile : public While {};

}

#endif
