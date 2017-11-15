#ifndef TERSE_SCOPEVALUE_H
#define TERSE_SCOPEVALUE_H

#include "Value.h"
#include "Environment.h"
#include <memory>
#include <vector>

namespace Terse {

    class ScopeValue : public Value {
    public:
        ScopeValue() {}
        ScopeValue(std::shared_ptr<Environment> env) :
                scope(std::make_shared<Environment>(env)) {}

        std::string toString() override {
            return "scope";
        }

        void print() override {
            std::cout << "scope";
        }

        std::shared_ptr<Environment> scope;
    };

}

#endif
