#include "Environment.h"
#include <stdexcept>

using namespace std;

namespace Terse {

    shared_ptr<Value> Environment::get(const string& key) {
        auto found = env.find(key);
        if (found != env.end()) {
            return found->second;
        }
        if (parent) {
            return parent->get(key);
        }
        throw runtime_error("Variable \"" + key + "\" not in the environment.");
    }
    
    void Environment::set(const string& key, shared_ptr<Value> value) {
        if (env.find(key) != env.end()) {
            throw runtime_error("Variable \"" + key + "\" already exist in this scope.");
        }
        env[key] = value;
    }

    shared_ptr<Environment> Environment::copy() {
        shared_ptr<Environment> env = make_shared<Environment>();
        copyInto(env.get());
        return env;
    }

    void Environment::copyInto(Environment* e) {
        for (auto iter = env.begin(); iter != env.end(); iter++) {
            e->env.emplace(*iter);
        }
        if (parent) {
            parent->copyInto(e);
        }
    }

}