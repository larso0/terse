#ifndef TERSE_EVALUATOR_H
#define TERSE_EVALUATOR_H

#include "Values.h"
#include "../AST/AST.h"
#include "Environment.h"

namespace Terse {

    std::shared_ptr<Value> evaluateExpression(std::shared_ptr<Expression> e,
                                              std::shared_ptr<Environment> env);

    std::shared_ptr<Value> evaluateUnaryOp(std::shared_ptr<UnaryOp> uop,
                                           std::shared_ptr<Environment> env);

    std::shared_ptr<Value> evaluateBinaryOp(std::shared_ptr<BinaryOp> bop,
                                            std::shared_ptr<Environment> env);

    std::shared_ptr<Value> evaluateStatement(std::shared_ptr<Statement> s,
                                             std::shared_ptr<Environment> env);


    class LazyValue : public Value::Lazy {
    public:
        LazyValue(std::shared_ptr<Expression> expr,
                  std::shared_ptr<Environment> env) : expr(expr), env(env) {}

        std::shared_ptr<Value> get() override {
            return evaluateExpression(expr, env);
        }

        std::shared_ptr<Expression> expr;
        std::shared_ptr<Environment> env;
    };

}

#endif
