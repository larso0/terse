#ifndef TERSE_FLOATVALUE_H
#define TERSE_FLOATVALUE_H

#include "Value.h"

namespace Terse {

    class FloatValue : public Value {
    public:
        FloatValue() : value(0) {}

        FloatValue(float v) : value(v) {}

        std::shared_ptr<Value> copy() override {
            return std::make_shared<FloatValue>(value);
        }

        void increment() override {
            value++;
        }

        void decrement() override {
            value--;
        }

        std::shared_ptr<Value> negate() override {
            return std::make_shared<FloatValue>(-value);
        }

        std::shared_ptr<Value> notOp() override {
            return std::make_shared<FloatValue>(!value);
        }

        std::shared_ptr<Value> multiply(std::shared_ptr<Value> rhs) override {
            auto fval = dynamic_cast<FloatValue*>(rhs.get());
            if (!fval) {
                throw std::runtime_error("Non-number operand.");
            }
            return std::make_shared<FloatValue>(value * fval->value);
        }

        std::shared_ptr<Value> divide(std::shared_ptr<Value> rhs) override {
            auto fval = dynamic_cast<FloatValue*>(rhs.get());
            if (!fval) {
                throw std::runtime_error("Non-number operand.");
            }
            return std::make_shared<FloatValue>(value / fval->value);
        }

        std::shared_ptr<Value> add(std::shared_ptr<Value> rhs) override {
            auto fval = dynamic_cast<FloatValue*>(rhs.get());
            if (!fval) {
                throw std::runtime_error("Non-number operand.");
            }
            return std::make_shared<FloatValue>(value + fval->value);
        }

        std::shared_ptr<Value> subtract(std::shared_ptr<Value> rhs) override {
            auto fval = dynamic_cast<FloatValue*>(rhs.get());
            if (!fval) {
                throw std::runtime_error("Non-number operand.");
            }
            return std::make_shared<FloatValue>(value - fval->value);
        }

        std::shared_ptr<Value> less(std::shared_ptr<Value> rhs) override {
            auto fval = dynamic_cast<FloatValue*>(rhs.get());
            if (!fval) {
                throw std::runtime_error("Non-number operand.");
            }
            return std::make_shared<FloatValue>(value < fval->value);
        }

        std::shared_ptr<Value> lessOrEqual(std::shared_ptr<Value> rhs) override {
            auto fval = dynamic_cast<FloatValue*>(rhs.get());
            if (!fval) {
                throw std::runtime_error("Non-number operand.");
            }
            return std::make_shared<FloatValue>(value <= fval->value);
        }

        std::shared_ptr<Value> greater(std::shared_ptr<Value> rhs) override {
            auto fval = dynamic_cast<FloatValue*>(rhs.get());
            if (!fval) {
                throw std::runtime_error("Non-number operand.");
            }
            return std::make_shared<FloatValue>(value > fval->value);
        }

        std::shared_ptr<Value> greaterOrEqual(std::shared_ptr<Value> rhs) override {
            auto fval = dynamic_cast<FloatValue*>(rhs.get());
            if (!fval) {
                throw std::runtime_error("Non-number operand.");
            }
            return std::make_shared<FloatValue>(value >= fval->value);
        }

        std::shared_ptr<Value> equal(std::shared_ptr<Value> rhs) override {
            auto fval = dynamic_cast<FloatValue*>(rhs.get());
            if (!fval) {
                throw std::runtime_error("Non-number operand.");
            }
            return std::make_shared<FloatValue>(value == fval->value);
        }

        std::shared_ptr<Value> notEqual(std::shared_ptr<Value> rhs) override {
            auto fval = dynamic_cast<FloatValue*>(rhs.get());
            if (!fval) {
                throw std::runtime_error("Non-number operand.");
            }
            return std::make_shared<FloatValue>(value != fval->value);
        }

        std::shared_ptr<Value> andOp(Lazy& rhs) override {
            float result = 0;
            if (value) {
                auto fval = std::dynamic_pointer_cast<FloatValue>(rhs.get());
                if (!fval) {
                    throw std::runtime_error("Non-number operand.");
                }
                result = fval->value;
            }
            return std::make_shared<FloatValue>(result);
        }

        std::shared_ptr<Value> orOp(Lazy& rhs) override {
            float result = 1;
            if (!value) {
                auto fval = std::dynamic_pointer_cast<FloatValue>(rhs.get());
                if (!fval) {
                    throw std::runtime_error("Non-number operand.");
                }
                result = fval->value;
            }
            return std::make_shared<FloatValue>(result);
        }

        void assign(std::shared_ptr<Value> val) override {
            if (dynamic_cast<FloatValue*>(val.get())) {
                value = static_cast<FloatValue*>(val.get())->value;
            } else {
                throw std::runtime_error("Expected float value, got something else.");
            }
        }

        void addAssign(std::shared_ptr<Value> val) override {
            if (dynamic_cast<FloatValue*>(val.get())) {
                value += static_cast<FloatValue*>(val.get())->value;
            } else {
                throw std::runtime_error("Expected float value, got something else.");
            }
        }

        void subtractAssign(std::shared_ptr<Value> val) override {
            if (dynamic_cast<FloatValue*>(val.get())) {
                value -= static_cast<FloatValue*>(val.get())->value;
            } else {
                throw std::runtime_error("Expected float value, got something else.");
            }
        }

        void multiplyAssign(std::shared_ptr<Value> val) override {
            if (dynamic_cast<FloatValue*>(val.get())) {
                value *= static_cast<FloatValue*>(val.get())->value;
            } else {
                throw std::runtime_error("Expected float value, got something else.");
            }
        }

        void divideAssign(std::shared_ptr<Value> val) override {
            if (dynamic_cast<FloatValue*>(val.get())) {
                value /= static_cast<FloatValue*>(val.get())->value;
            } else {
                throw std::runtime_error("Expected float value, got something else.");
            }
        }

        std::string toString() override {
            return std::to_string(value);
        }

        void print() override {
            std::cout << value;
        }

        float value;
    };

}


#endif
