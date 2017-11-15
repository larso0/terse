#ifndef TERSE_FUNCTIONDEFINITION_H
#define TERSE_FUNCTIONDEFINITION_H

#include "Statement.h"
#include <vector>
#include <memory>
#include <string>

namespace Terse {

    class FunctionDefinition : public Statement {
    public:
        FunctionDefinition() {}
        FunctionDefinition(const std::string& name) : name(name) {}

        void addParameter(const std::string& p) { parameters.push_back(p); }

        void addStatement(std::shared_ptr<Statement> s) { block.push_back(s); }

        std::string name;
        std::vector<std::string> parameters;
        std::vector<std::shared_ptr<Statement>> block;
    };

}

#endif
