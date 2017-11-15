#ifndef TERSE_CHARVALUE_H
#define TERSE_CHARVALUE_H

#include "Value.h"
#include <sstream>

namespace Terse {

    class CharValue : public Value {
    public:
        CharValue() : value(0) {}

        CharValue(char v) : value(v) {}

        std::shared_ptr<Value> copy() override {
            return std::make_shared<CharValue>(value);
        }

        std::shared_ptr<Value> less(std::shared_ptr<Value> rhs) override {
            auto ival = dynamic_cast<CharValue*>(rhs.get());
            if (!ival) {
                throw std::runtime_error("Non-character operand.");
            }
            return std::make_shared<IntValue>(value < ival->value);
        }

        std::shared_ptr<Value> lessOrEqual(std::shared_ptr<Value> rhs) override {
            auto ival = dynamic_cast<CharValue*>(rhs.get());
            if (!ival) {
                throw std::runtime_error("Non-character operand.");
            }
            return std::make_shared<IntValue>(value <= ival->value);
        }

        std::shared_ptr<Value> greater(std::shared_ptr<Value> rhs) override {
            auto ival = dynamic_cast<CharValue*>(rhs.get());
            if (!ival) {
                throw std::runtime_error("Non-character operand.");
            }
            return std::make_shared<IntValue>(value > ival->value);
        }

        std::shared_ptr<Value> greaterOrEqual(std::shared_ptr<Value> rhs) override {
            auto ival = dynamic_cast<CharValue*>(rhs.get());
            if (!ival) {
                throw std::runtime_error("Non-character operand.");
            }
            return std::make_shared<IntValue>(value >= ival->value);
        }

        std::shared_ptr<Value> equal(std::shared_ptr<Value> rhs) override {
            auto ival = dynamic_cast<CharValue*>(rhs.get());
            if (!ival) {
                throw std::runtime_error("Non-character operand.");
            }
            return std::make_shared<IntValue>(value == ival->value);
        }

        std::shared_ptr<Value> notEqual(std::shared_ptr<Value> rhs) override {
            auto ival = dynamic_cast<CharValue*>(rhs.get());
            if (!ival) {
                throw std::runtime_error("Non-character operand.");
            }
            return std::make_shared<IntValue>(value != ival->value);
        }

        void assign(std::shared_ptr<Value> val) override {
            if (dynamic_cast<CharValue*>(val.get())) {
                value = static_cast<CharValue*>(val.get())->value;
            } else {
                throw std::runtime_error("Expected character value, got something else.");
            }
        }

        std::string toString() override {
            std::stringstream ss;
            ss << '\'';
            if (value == '\n') ss << "\\n";
            else if (value == '\r') ss << "\\r";
            else if (value == '\t') ss << "\\t";
            else if (value == '\'') ss << "\\'";
            else if (value == '\\') ss << "\\\\";
            else ss << value;
            ss << '\'';
            return ss.str();
        }

        void print() override {
            std::cout << value;
        }

        char value;
    };

}

#endif
