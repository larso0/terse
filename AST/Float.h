#ifndef TERSE_FLOAT_H
#define TERSE_FLOAT_H

#include "Expression.h"

namespace Terse {

    class Float : public Expression {
    public:
        Float(float value = 0) : value(value) {}

        float value;
    };

}

#endif
