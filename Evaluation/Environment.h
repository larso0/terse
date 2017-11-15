#ifndef TERSE_ENVIRONMENT_H
#define TERSE_ENVIRONMENT_H

#include <unordered_map>
#include <string>
#include <memory>
#include "Value.h"

namespace Terse {

    class Environment {
    public:
        Environment() {}
        Environment(std::shared_ptr<Environment> parent) : parent(parent) {}

        std::shared_ptr<Value> get(const std::string& key);
        void set(const std::string& key, std::shared_ptr<Value> value);
        std::shared_ptr<Environment> copy();

    private:
        std::shared_ptr<Environment> parent;
        std::unordered_map<std::string, std::shared_ptr<Value>> env;

        void copyInto(Environment* e);
    };

}

#endif
