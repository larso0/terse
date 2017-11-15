#ifndef TERSE_CHAR_H
#define TERSE_CHAR_H

#include "Expression.h"

namespace Terse {

    class Char : public Expression {
    public:
        Char(char value = 0) : value(value) {}

        char value;
    };

}

#endif
