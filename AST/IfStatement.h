#ifndef TERSE_IFSTATEMENT_H
#define TERSE_IFSTATEMENT_H

#include "Statement.h"
#include "Expression.h"
#include <memory>
#include <utility>
#include <vector>

namespace Terse {

    class IfStatement : public Statement {
    public:
        std::vector<std::pair<std::shared_ptr<Expression>, std::vector<std::shared_ptr<Statement>>>> ifs;
        std::vector<std::shared_ptr<Statement>> otherwise;
    };

}

#endif
