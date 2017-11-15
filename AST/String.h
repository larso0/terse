#ifndef TERSE_STRING_H
#define TERSE_STRING_H

#include "Expression.h"
#include <string>

namespace Terse {

    class String : public Expression {
    public:
        String(const std::string& v) : value(v) {}

        std::string value;
    };

}

#endif
