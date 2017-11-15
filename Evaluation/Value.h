#ifndef TERSE_VALUE_H
#define TERSE_VALUE_H

#include <memory>
#include <stdexcept>
#include <string>
#include <iostream>

namespace Terse {

    class Value {
    public:
        class Lazy {
        public:
            ~Lazy() {}
            virtual std::shared_ptr<Value> get() = 0;
        };

        virtual ~Value() {}

        virtual std::shared_ptr<Value> copy() {
            throw std::runtime_error("Invalid usage of value.");
        }

        virtual void increment() {
            throw std::runtime_error("Invalid usage of value.");
        }

        virtual void decrement() {
            throw std::runtime_error("Invalid usage of value.");
        }

        virtual std::shared_ptr<Value> negate() {
            throw std::runtime_error("Invalid usage of value.");
        }

        virtual std::shared_ptr<Value> notOp() {
            throw std::runtime_error("Invalid usage of value.");
        }

        virtual std::shared_ptr<Value> multiply(std::shared_ptr<Value> rhs) {
            throw std::runtime_error("Invalid usage of value.");
        }

        virtual std::shared_ptr<Value> divide(std::shared_ptr<Value> rhs) {
            throw std::runtime_error("Invalid usage of value.");
        }

        virtual std::shared_ptr<Value> remainder(std::shared_ptr<Value> rhs) {
            throw std::runtime_error("Invalid usage of value.");
        }

        virtual std::shared_ptr<Value> add(std::shared_ptr<Value> rhs) {
            throw std::runtime_error("Invalid usage of value.");
        }

        virtual std::shared_ptr<Value> subtract(std::shared_ptr<Value> rhs) {
            throw std::runtime_error("Invalid usage of value.");
        }

        virtual std::shared_ptr<Value> less(std::shared_ptr<Value> rhs) {
            throw std::runtime_error("Invalid usage of value.");
        }

        virtual std::shared_ptr<Value> lessOrEqual(std::shared_ptr<Value> rhs) {
            throw std::runtime_error("Invalid usage of value.");
        }

        virtual std::shared_ptr<Value> greater(std::shared_ptr<Value> rhs) {
            throw std::runtime_error("Invalid usage of value.");
        }

        virtual std::shared_ptr<Value> greaterOrEqual(std::shared_ptr<Value> rhs) {
            throw std::runtime_error("Invalid usage of value.");
        }

        virtual std::shared_ptr<Value> equal(std::shared_ptr<Value> rhs) {
            throw std::runtime_error("Invalid usage of value.");
        }

        virtual std::shared_ptr<Value> notEqual(std::shared_ptr<Value> rhs) {
            throw std::runtime_error("Invalid usage of value.");
        }

        virtual std::shared_ptr<Value> andOp(Lazy& rhs) {
            throw std::runtime_error("Invalid usage of value.");
        }

        virtual std::shared_ptr<Value> orOp(Lazy& rhs) {
            throw std::runtime_error("Invalid usage of value.");
        }

        virtual void assign(std::shared_ptr<Value> rhs) {
            throw std::runtime_error("Invalid usage of value.");
        }

        virtual void addAssign(std::shared_ptr<Value> rhs) {
            throw std::runtime_error("Invalid usage of value.");
        }

        virtual void subtractAssign(std::shared_ptr<Value> rhs) {
            throw std::runtime_error("Invalid usage of value.");
        }

        virtual void multiplyAssign(std::shared_ptr<Value> rhs) {
            throw std::runtime_error("Invalid usage of value.");
        }

        virtual void divideAssign(std::shared_ptr<Value> rhs) {
            throw std::runtime_error("Invalid usage of value.");
        }

        virtual std::string toString() {
            return "?";
        }

        virtual void print() {
            std::cout << '?';
        }
    };

}

#endif
