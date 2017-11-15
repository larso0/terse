#ifndef TERSE_LISTVALUE_H
#define TERSE_LISTVALUE_H

#include "Value.h"
#include <vector>
#include <memory>
#include <sstream>
#include <type_traits>

namespace Terse {

    class ListValue : public Value {
    public:
        virtual ~ListValue() {}

        virtual std::shared_ptr<Value> copy() override {
            auto lv = std::make_shared<ListValue>();
            for (auto v : list) {
                lv->list.push_back(v->copy());
            }
            return lv;
        }

        virtual void assign(std::shared_ptr<Value> val) override {
            if (dynamic_cast<ListValue*>(val.get())) {
                list.clear();
                for (auto v : static_cast<ListValue*>(val.get())->list) {
                    list.push_back(v);
                }
            } else {
                throw std::runtime_error("List type mismatch");
            }
        }

        virtual void listAdd(std::shared_ptr<Value> val) {
            list.push_back(val->copy());
        }

        std::shared_ptr<Value> listAccess(std::shared_ptr<Value> val) {
            auto i = dynamic_cast<IntValue*>(val.get());
            if (!i) {
                throw std::runtime_error("Expected integer index for list access, got something else.");
            }
            if (i->value < 0 || i->value >= list.size()) {
                throw std::out_of_range("Index out of range.");
            }
            return list[i->value];
        }

        virtual std::string toString() {
            std::stringstream ss;
            ss << '[';
            auto iter = list.begin();
            if (iter != list.end()) {
                ss << (*iter)->toString();
                iter++;
            }
            for (; iter != list.end(); iter++) {
                ss << ", ";
                ss << (*iter)->toString();
            }
            ss << ']';
            return ss.str();
        }

        virtual void print() {
            std::cout << '[';
            auto iter = list.begin();
            if (iter != list.end()) {
                std::cout <<(*iter)->toString();
                iter++;
            }
            for (; iter != list.end(); iter++) {
                std::cout << ", ";
                std::cout <<(*iter)->toString();
            }
            std::cout << ']';
        }

        std::vector<std::shared_ptr<Value>> list;
    };

}

#endif
