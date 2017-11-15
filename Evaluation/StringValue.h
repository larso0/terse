#ifndef TERSE_STRINGVALUE_H
#define TERSE_STRINGVALUE_H

#include "ListValue.h"
#include "CharValue.h"

namespace Terse {

    class StringValue : public ListValue {
    public:

        std::shared_ptr<Value> copy() override {
            auto lv = std::make_shared<StringValue>();
            for (auto v : list) {
                lv->list.push_back(v->copy());
            }
            return lv;
        }

        void assign(std::shared_ptr<Value> val) override {
            if (!dynamic_cast<StringValue*>(val.get())) {
                throw std::runtime_error("Can't assign list to string.");
            }
            ListValue::assign(val);
        }

        void listAdd(std::shared_ptr<Value> val) override {
            if (!dynamic_cast<CharValue*>(val.get())) {
                throw std::runtime_error("Can't add non-char element to string.");
            }
            ListValue::listAdd(val);
        }

        std::string toString() override {
            std::stringstream ss;
            ss << '"';
            for (auto e : list) {
                auto c = static_cast<CharValue*>(e.get());
                if (c->value == '\n') ss << "\\n";
                else if (c->value == '\r') ss << "\\r";
                else if (c->value == '\t') ss << "\\t";
                else if (c->value == '\"') ss << "\\\"";
                else if (c->value == '\\') ss << "\\\\";
                else ss << c->value;
            }
            ss << '"';
            return ss.str();
        }

        std::string stringContent() {
            std::stringstream ss;
            for (auto e : list) {
                auto c = static_cast<CharValue*>(e.get());
                ss << c->value;
            }
            return ss.str();
        }

        void print() override {
            for (auto e : list) {
                auto c = static_cast<CharValue*>(e.get());
                std::cout << c->value;
            }
        }
    };

}

#endif
