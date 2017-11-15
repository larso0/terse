#ifndef TERSE_FUNCTIONAPPLICATION_H
#define TERSE_FUNCTIONAPPLICATION_H

#include "Expression.h"
#include <vector>
#include <memory>

namespace Terse {

    class FunctionApplication : public Expression {
    public:
        FunctionApplication() {}
        FunctionApplication(std::shared_ptr<Expression> f) : function(f) {}

        void addArgument(std::shared_ptr<Expression> a) { arguments.push_back(a); }

        std::shared_ptr<Expression> function;
        std::vector<std::shared_ptr<Expression>> arguments;
    };

}

#endif
