#ifndef TERSE_FOREACH_H
#define TERSE_FOREACH_H

#include "Statement.h"
#include "Expression.h"
#include <memory>
#include <vector>
#include <string>

namespace Terse {

    class ForEach : public Statement {
    public:
        std::string var;
        std::shared_ptr<Expression> list;
        std::vector<std::shared_ptr<Statement>> block;
    };

}

#endif
