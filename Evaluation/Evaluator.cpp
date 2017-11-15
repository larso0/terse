#include "Evaluator.h"
#include "CharValue.h"

using namespace std;

namespace Terse {

    shared_ptr<Value> evaluateExpression(shared_ptr<Expression> e,
                                         shared_ptr<Environment> env) {
        if (dynamic_cast<Int*>(e.get())) {
            return make_shared<IntValue>(static_cast<Int*>(e.get())->value);
        }

        if (dynamic_cast<Float*>(e.get())) {
            return make_shared<FloatValue>(static_cast<Float*>(e.get())->value);
        }

        if (dynamic_cast<Char*>(e.get())) {
            return make_shared<CharValue>(static_cast<Char*>(e.get())->value);
        }

        if (dynamic_cast<Variable*>(e.get())) {
            return env->get(static_cast<Variable*>(e.get())->name);
        }

        if (dynamic_cast<List*>(e.get())) {
            auto l = static_cast<List*>(e.get());
            auto lv = make_shared<ListValue>();
            for (auto expr : static_cast<List*>(e.get())->list) {
                lv->listAdd(evaluateExpression(expr, env));
            }
            return lv;
        }

        if (dynamic_cast<UnaryOp*>(e.get())) {
            return evaluateUnaryOp(static_pointer_cast<UnaryOp>(e), env);
        }

        if (dynamic_cast<BinaryOp*>(e.get())) {
            return evaluateBinaryOp(static_pointer_cast<BinaryOp>(e), env);
        }

        if (dynamic_cast<FunctionApplication*>(e.get())) {
            auto fa = static_cast<FunctionApplication*>(e.get());
            auto fv = dynamic_pointer_cast<FunctionValue>(evaluateExpression(fa->function, env));
            if (!fv) {
                throw runtime_error("Expected function, got something else.");
            }
            vector<shared_ptr<Value>> args;
            for (auto expr : fa->arguments) {
                args.push_back(evaluateExpression(expr, env));
            }
            return fv->call(args);
        }

        if (dynamic_cast<ListAccess*>(e.get())) {
            auto la = static_cast<ListAccess*>(e.get());
            auto lv = dynamic_pointer_cast<ListValue>(evaluateExpression(la->expression, env));
            if (!lv) {
                throw runtime_error("Expected list exception, got something else.");
            }
            return lv->listAccess(evaluateExpression(la->index, env));
        }

        if (dynamic_cast<String*>(e.get())) {
            auto s = static_cast<String*>(e.get());
            auto sv = make_shared<StringValue>();
            for (char c : s->value) {
                sv->list.push_back(make_shared<CharValue>(c));
            }
            return sv;
        }

        throw runtime_error("Failed to evaluate: Unknown expression.");
    }

    shared_ptr<Value> evaluateUnaryOp(shared_ptr<UnaryOp> uop,
                                      shared_ptr<Environment> env) {
        shared_ptr<Value> result;
        shared_ptr<Value> operand = evaluateExpression(uop->expression, env);
        if (dynamic_cast<Undefined*>(operand.get())) {
            throw runtime_error("Failed to evaluate unary operator \"" +
                                toToken(uop->op) +
                                "\", operand evaluated to undefined.");
        }
        switch (uop->op) {
            case Operator::IncrementPostfix:
                result = operand->copy();
                operand->increment();
                break;
            case Operator::DecrementPostfix:
                result = operand->copy();
                operand->decrement();
                break;
            case Operator::IncrementPrefix:
                operand->increment();
                result = operand->copy();
                break;
            case Operator::DecrementPrefix:
                operand->decrement();
                result = operand->copy();
                break;
            case Operator::Negate:
                result = operand->negate();
                break;
            case Operator::Not:
                result = operand->notOp();
                break;
            default:
                throw runtime_error("Unknown unary operator \"" +
                                    toToken(uop->op) + "\".");

        }

        return result;
    }

    shared_ptr<Value> evaluateBinaryOp(shared_ptr<BinaryOp> bop,
                                       shared_ptr<Environment> env) {
        int op = bop->op;

        shared_ptr<Value> result;
        shared_ptr<Value> left = evaluateExpression(bop->left, env);
        LazyValue right(bop->right, env);

        switch (bop->op) {
            case Operator::MemberAccess: {
                auto scope = dynamic_cast<ScopeValue*>(left.get());
                if (!scope) {
                    throw runtime_error("Expected scope, got something else.");
                }
                result = evaluateExpression(bop->right, scope->scope);
                break;
            }
            case Operator::Multiply:
                result = left->multiply(right.get());
                break;
            case Operator::Divide:
                result = left->divide(right.get());
                break;
            case Operator::Remainder:
                result = left->remainder(right.get());
                break;
            case Operator::Add:
                result = left->add(right.get());
                break;
            case Operator::Subtract:
                result = left->subtract(right.get());
                break;
            case Operator::Less:
                result = left->less(right.get());
                break;
            case Operator::LessOrEqual:
                result = left->lessOrEqual(right.get());
                break;
            case Operator::Greater:
                result = left->greater(right.get());
                break;
            case Operator::GreaterOrEqual:
                result = left->greaterOrEqual(right.get());
                break;
            case Operator::Equal:
                result = left->equal(right.get());
                break;
            case Operator::NotEqual:
                result = left->notEqual(right.get());
                break;
            case Operator::And:
                result = left->andOp(right);
                break;
            case Operator::Or:
                result = left->orOp(right);
                break;
            case Operator::Assign:
                left->assign(right.get());
                result = left;
                break;
            case Operator::AddAssign:
                left->assign(right.get());
                result = left;
                break;
            case Operator::SubtractAssign:
                left->subtractAssign(right.get());
                result = left;
                break;
            case Operator::MultiplyAssign:
                left->multiplyAssign(right.get());
                result = left;
                break;
            case Operator::DivideAssign:
                left->divideAssign(right.get());
                result = left;
                break;
            default:
                throw runtime_error("Unknown binary operator \"" + toToken(op) + "\".");
        }

        return result;
    }

    int evaluateInt(shared_ptr<Expression> e, shared_ptr<Environment> env) {
        auto val = evaluateExpression(e, env);
        IntValue* iVal = dynamic_cast<IntValue*>(val.get());
        if (iVal) return iVal->value;
        throw runtime_error("Condition did not evaluate to int.");
    }

    std::shared_ptr<Value> evaluateBlock(vector<shared_ptr<Statement>>& block, shared_ptr<Environment> env) {
        for (auto statement : block) {
            try {
                evaluateStatement(statement, env);
            } catch (shared_ptr<Value> ret) {
                return ret;
            }
        }
        return make_shared<Undefined>();
    }

    std::shared_ptr<Value> evaluateStatement(shared_ptr<Statement> s,
                                             shared_ptr<Environment> env) {
        if (dynamic_cast<Pass*>(s.get())) {
            return make_shared<Undefined>();
        }

        if (dynamic_cast<LetStatement*>(s.get())) {
            auto let = static_cast<LetStatement*>(s.get());
            for (auto& d : let->declarations) {
                env->set(d.first, evaluateExpression(d.second, env));
            }
            return make_shared<Undefined>();
        }

        if (dynamic_cast<FunctionDefinition*>(s.get())) {
            auto fd = static_pointer_cast<FunctionDefinition>(s);
            auto fv = make_shared<FunctionValue>();
            auto fscope = env->copy();
            fv->call = [fd, fv, fscope](vector<shared_ptr<Value>>& args) -> shared_ptr<Value> {
                if (args.size() != fd->parameters.size()) {
                    throw runtime_error("Mismatching parameters / arguments");
                }
                auto callScope = make_shared<Environment>(fscope);
                for (unsigned i = 0; i < args.size(); i++) {
                    callScope->set(fd->parameters[i], args[i]);
                }
                callScope->set(fd->name, fv);
                return evaluateBlock(fd->block, callScope);
            };
            env->set(fd->name, fv);
            return make_shared<Undefined>();
        }

        if (dynamic_cast<NamedScope*>(s.get())) {
            auto ns = static_cast<NamedScope*>(s.get());
            auto sc = make_shared<ScopeValue>(env);
            evaluateBlock(ns->block, sc->scope);
            env->set(ns->name, sc);
            return make_shared<Undefined>();
        }

        if (dynamic_cast<ReturnStatement*>(s.get())) {
            auto expr = static_cast<ReturnStatement*>(s.get())->expression;
            if (expr) throw evaluateExpression(expr, env);
            throw static_pointer_cast<Value>(make_shared<Undefined>());
        }

        if (dynamic_cast<ExpressionStatement*>(s.get())) {
            return evaluateExpression(static_cast<ExpressionStatement*>(s.get())->expression, env);
        }

        if (dynamic_cast<IfStatement*>(s.get())) {
            auto ifStat = static_cast<IfStatement*>(s.get());
            auto iter = ifStat->ifs.begin();
            for (; iter != ifStat->ifs.end(); iter++) {
                if (evaluateInt(iter->first, env)) {
                    auto scopeEnv = make_shared<Environment>(env);
                    for (auto statement : iter->second) {
                        evaluateStatement(statement, scopeEnv);
                    }
                    break;
                }
            }
            if (iter == ifStat->ifs.end() && ifStat->otherwise.size() > 0) {
                auto scopeEnv = make_shared<Environment>(env);
                for (auto statement : ifStat->otherwise) {
                    evaluateStatement(statement, scopeEnv);
                }
            }
            return make_shared<Undefined>();
        }

        if (dynamic_cast<DoWhile*>(s.get())) {
            auto dowh = static_cast<DoWhile*>(s.get());
            do {
                auto scope = make_shared<Environment>(env);
                for (auto statement : dowh->block) {
                    evaluateStatement(statement, scope);
                }
            } while (evaluateInt(dowh->condition, env));
            return make_shared<Undefined>();
        }

        if (dynamic_cast<While*>(s.get())) {
            auto wh = static_cast<While*>(s.get());
            while (evaluateInt(wh->condition, env)) {
                auto scope = make_shared<Environment>(env);
                for (auto statement : wh->block) {
                    evaluateStatement(statement, scope);
                }
            }
            return make_shared<Undefined>();
        }

        if (dynamic_cast<ForEach*>(s.get())) {
            auto foreach = static_cast<ForEach*>(s.get());
            auto list = dynamic_pointer_cast<ListValue>(evaluateExpression(foreach->list, env));
            if (!list) {
                throw runtime_error("Expected a list, got something else.");
            }
            for (auto val : list->list) {
                auto scope = make_shared<Environment>(env);
                scope->set(foreach->var, val);
                for (auto statement : foreach->block) {
                    evaluateStatement(statement, scope);
                }
            }
            return make_shared<Undefined>();
        }

        throw runtime_error("Failed to evaluate: Unknown statement.");
    }

}