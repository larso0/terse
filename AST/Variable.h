#ifndef TERSE_VARIABLE_H
#define TERSE_VARIABLE_H

#include "Expression.h"
#include <string>

namespace Terse {

    class Variable : public Expression {
    public:
        Variable(const std::string& name = "") : name(name) {}

        std::string name;
    };

}

#endif
