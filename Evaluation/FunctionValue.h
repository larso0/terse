#ifndef TERSE_FUNCTIONVALUE_H
#define TERSE_FUNCTIONVALUE_H

#include "Value.h"
#include "Environment.h"
#include <functional>
#include <memory>
#include <vector>

namespace Terse {
    
    class FunctionValue : public Value {
    public:
        FunctionValue() {}

        std::shared_ptr<Value> copy() override {
            auto fv = std::make_shared<FunctionValue>();
            fv->call = call;
            return fv;
        }

        void assign(std::shared_ptr<Value> val) override {
            if (dynamic_cast<FunctionValue*>(val.get())) {
                call = static_cast<FunctionValue*>(val.get())->call;
            } else {
                throw std::runtime_error("Expected function value, got something else.");
            }
        }

        std::string toString() override {
            return "function";
        }

        void print() override {
            std::cout << "function";
        }

        std::function<std::shared_ptr<Value>(std::vector<std::shared_ptr<Value>>&)> call;
    };    
    
}

#endif
