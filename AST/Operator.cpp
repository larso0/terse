#include "Operator.h"

using namespace std;

namespace Terse {

    int toOperator(const string& t, bool prevWasValue) {
        if (t == "!") return Operator::Not;
        if (t == "++") return prevWasValue ? Operator::IncrementPostfix : Operator::IncrementPrefix;
        if (t == "--") return prevWasValue ? Operator::DecrementPostfix : Operator::DecrementPrefix;
        if (t == "+") return Operator::Add;
        if (t == "-") return prevWasValue ? Operator::Subtract : Operator::Negate;
        if (t == "*") return Operator::Multiply;
        if (t == "/") return Operator::Divide;
        if (t == "%") return Operator::Remainder;
        if (t == "=") return Operator::Equal;
        if (t == "!=") return Operator::NotEqual;
        if (t == "<") return Operator::Less;
        if (t == "<=") return Operator::LessOrEqual;
        if (t == ">") return Operator::Greater;
        if (t == ">=") return Operator::GreaterOrEqual;
        if (t == "|") return Operator::Or;
        if (t == "&") return Operator::And;
        if (t == ":=") return Operator::Assign;
        if (t == "+=") return Operator::AddAssign;
        if (t == "-=") return Operator::SubtractAssign;
        if (t == "*=") return Operator::MultiplyAssign;
        if (t == "/=") return Operator::DivideAssign;
        if (t == ".") return prevWasValue ? Operator::MemberAccess : Operator::MemberAccessUnary;
        return Operator::None;
    }

    string toToken(int op) {
        switch (op) {
            case Operator::IncrementPostfix:
            case Operator::IncrementPrefix: return "++";
            case Operator::DecrementPostfix:
            case Operator::DecrementPrefix: return "--";
            case Operator::Negate:
            case Operator::Subtract: return "-";
            case Operator::Not: return "!";
            case Operator::Multiply: return "*";
            case Operator::Divide: return "/";
            case Operator::Remainder: return "%";
            case Operator::Add: return "+";
            case Operator::Less: return "<";
            case Operator::LessOrEqual: return "<=";
            case Operator::Greater: return ">";
            case Operator::GreaterOrEqual: return ">=";
            case Operator::Equal: return "=";
            case Operator::NotEqual: return "!=";
            case Operator::And: return "&";
            case Operator::Or: return "|";
            case Operator::Assign: return ":=";
            case Operator::AddAssign: return "+=";
            case Operator::SubtractAssign: return "-=";
            case Operator::MultiplyAssign: return "*=";
            case Operator::DivideAssign: return "/=";
            case Operator::MemberAccess:
            case Operator::MemberAccessUnary: return ".";
            default: return "unknown";
        }
    }

}