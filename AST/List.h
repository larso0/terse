#ifndef TERSE_LIST_H
#define TERSE_LIST_H

#include "Expression.h"
#include <memory>
#include <vector>

namespace Terse {

    class List : public Expression {
    public:
        std::vector<std::shared_ptr<Expression>> list;
    };

}

#endif
