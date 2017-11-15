#ifndef TERSE_NAMEDSCOPE_H
#define TERSE_NAMEDSCOPE_H

#include "Statement.h"
#include <vector>
#include <memory>
#include <string>

namespace Terse {

    class NamedScope : public Statement {
    public:
        void addStatement(std::shared_ptr<Statement> s) { block.push_back(s); }

        std::string name;
        std::vector<std::shared_ptr<Statement>> block;
    };

}

#endif
