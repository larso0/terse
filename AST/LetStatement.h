#ifndef TERSE_LETSTATEMENT_H
#define TERSE_LETSTATEMENT_H

#include "Statement.h"
#include "Expression.h"
#include <memory>
#include <vector>
#include <utility>

namespace Terse {

    class LetStatement : public Statement {
    public:
        LetStatement() {}

        void addDeclaration(const std::string& name, std::shared_ptr<Expression> value) {
            declarations.push_back(std::make_pair(name, value));
        }

        std::vector<std::pair<std::string, std::shared_ptr<Expression>>> declarations;
    };

}

#endif
