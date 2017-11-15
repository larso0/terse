#ifndef TERSE_INTVALUE_H
#define TERSE_INTVALUE_H

#include "Value.h"

namespace Terse {

    class IntValue : public Value {
    public:
        IntValue() : value(0) {}

        IntValue(int v) : value(v) {}

        std::shared_ptr<Value> copy() override {
            return std::make_shared<IntValue>(value);
        }

        void increment() override {
            value++;
        }

        void decrement() override {
            value--;
        }

        std::shared_ptr<Value> negate() override {
            return std::make_shared<IntValue>(-value);
        }

        std::shared_ptr<Value> notOp() override {
            return std::make_shared<IntValue>(!value);
        }

        std::shared_ptr<Value> multiply(std::shared_ptr<Value> rhs) override {
            auto ival = dynamic_cast<IntValue*>(rhs.get());
            if (!ival) {
                throw std::runtime_error("Non-number operand.");
            }
            return std::make_shared<IntValue>(value * ival->value);
        }

        std::shared_ptr<Value> divide(std::shared_ptr<Value> rhs) override {
            auto ival = dynamic_cast<IntValue*>(rhs.get());
            if (!ival) {
                throw std::runtime_error("Non-number operand.");
            }
            return std::make_shared<IntValue>(value / ival->value);
        }

        std::shared_ptr<Value> remainder(std::shared_ptr<Value> rhs) override {
            auto ival = dynamic_cast<IntValue*>(rhs.get());
            if (!ival) {
                throw std::runtime_error("Non-number operand.");
            }
            return std::make_shared<IntValue>(value % ival->value);
        }

        std::shared_ptr<Value> add(std::shared_ptr<Value> rhs) override {
            auto ival = dynamic_cast<IntValue*>(rhs.get());
            if (!ival) {
                throw std::runtime_error("Non-number operand.");
            }
            return std::make_shared<IntValue>(value + ival->value);
        }

        std::shared_ptr<Value> subtract(std::shared_ptr<Value> rhs) override {
            auto ival = dynamic_cast<IntValue*>(rhs.get());
            if (!ival) {
                throw std::runtime_error("Non-number operand.");
            }
            return std::make_shared<IntValue>(value - ival->value);
        }

        std::shared_ptr<Value> less(std::shared_ptr<Value> rhs) override {
            auto ival = dynamic_cast<IntValue*>(rhs.get());
            if (!ival) {
                throw std::runtime_error("Non-number operand.");
            }
            return std::make_shared<IntValue>(value < ival->value);
        }

        std::shared_ptr<Value> lessOrEqual(std::shared_ptr<Value> rhs) override {
            auto ival = dynamic_cast<IntValue*>(rhs.get());
            if (!ival) {
                throw std::runtime_error("Non-number operand.");
            }
            return std::make_shared<IntValue>(value <= ival->value);
        }

        std::shared_ptr<Value> greater(std::shared_ptr<Value> rhs) override {
            auto ival = dynamic_cast<IntValue*>(rhs.get());
            if (!ival) {
                throw std::runtime_error("Non-number operand.");
            }
            return std::make_shared<IntValue>(value > ival->value);
        }

        std::shared_ptr<Value> greaterOrEqual(std::shared_ptr<Value> rhs) override {
            auto ival = dynamic_cast<IntValue*>(rhs.get());
            if (!ival) {
                throw std::runtime_error("Non-number operand.");
            }
            return std::make_shared<IntValue>(value >= ival->value);
        }

        std::shared_ptr<Value> equal(std::shared_ptr<Value> rhs) override {
            auto ival = dynamic_cast<IntValue*>(rhs.get());
            if (!ival) {
                throw std::runtime_error("Non-number operand.");
            }
            return std::make_shared<IntValue>(value == ival->value);
        }

        std::shared_ptr<Value> notEqual(std::shared_ptr<Value> rhs) override {
            auto ival = dynamic_cast<IntValue*>(rhs.get());
            if (!ival) {
                throw std::runtime_error("Non-number operand.");
            }
            return std::make_shared<IntValue>(value != ival->value);
        }

        std::shared_ptr<Value> andOp(Lazy& rhs) override {
            int result = 0;
            if (value) {
                auto ival = std::dynamic_pointer_cast<IntValue>(rhs.get());
                if (!ival) {
                    throw std::runtime_error("Non-number operand.");
                }
                result = ival->value;
            }
            return std::make_shared<IntValue>(result);
        }

        std::shared_ptr<Value> orOp(Lazy& rhs) override {
            int result = 1;
            if (!value) {
                auto ival = std::dynamic_pointer_cast<IntValue>(rhs.get());
                if (!ival) {
                    throw std::runtime_error("Non-number operand.");
                }
                result = ival->value;
            }
            return std::make_shared<IntValue>(result);
        }

        void assign(std::shared_ptr<Value> val) override {
            if (dynamic_cast<IntValue*>(val.get())) {
                value = static_cast<IntValue*>(val.get())->value;
            } else {
                throw std::runtime_error("Expected int value, got something else.");
            }
        }

        void addAssign(std::shared_ptr<Value> val) override {
            if (dynamic_cast<IntValue*>(val.get())) {
                value += static_cast<IntValue*>(val.get())->value;
            } else {
                throw std::runtime_error("Expected int value, got something else.");
            }
        }

        void subtractAssign(std::shared_ptr<Value> val) override {
            if (dynamic_cast<IntValue*>(val.get())) {
                value -= static_cast<IntValue*>(val.get())->value;
            } else {
                throw std::runtime_error("Expected int value, got something else.");
            }
        }

        void multiplyAssign(std::shared_ptr<Value> val) override {
            if (dynamic_cast<IntValue*>(val.get())) {
                value *= static_cast<IntValue*>(val.get())->value;
            } else {
                throw std::runtime_error("Expected int value, got something else.");
            }
        }

        void divideAssign(std::shared_ptr<Value> val) override {
            if (dynamic_cast<IntValue*>(val.get())) {
                value /= static_cast<IntValue*>(val.get())->value;
            } else {
                throw std::runtime_error("Expected int value, got something else.");
            }
        }

        std::string toString() override {
            return std::to_string(value);
        }

        void print() override {
            std::cout << value;
        }

        int value;
    };

}

#endif
