#ifndef TERSE_INT_H
#define TERSE_INT_H

#include "Expression.h"

namespace Terse {

    class Int : public Expression {
    public:
        Int(int value = 0) : value(value) {}

        int value;
    };

}

#endif
