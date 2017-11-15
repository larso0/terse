#include "Parser.h"
#include "SyntaxError.h"
#include "AST/IfStatement.h"
#include <regex>

using namespace std;

namespace Terse {

    static regex intRegex("0|([1-9][0-9]*)");
    static regex fractionRegex("[0-9]*");
    static regex nameRegex("[_]*[a-zA-Z][a-zA-Z_0-9]*");
    static regex charRegex("'([^\"\\\\\n]|(\\\\[nrt\'\\\\]))'");
    static regex stringRegex("\"([^\"\\\\\n]|(\\\\[nrt\"\\\\]))*\"");

    void replaceSubstring(string& subject, const string& search, const string& replace) {
        if (search.empty()) { return; }
        typename string::size_type pos = 0;
        while ((pos = subject.find(search, pos)) != string::npos) {
            subject.replace(pos, search.length(), replace);
            pos += replace.length();
        }
    }

    shared_ptr<Expression> parseAppl(Lexer& lex, std::shared_ptr<Expression> lhs, bool ignoreNewlines) {
        shared_ptr<Expression> result = lhs;
        while (lex.token(ignoreNewlines) == "(" || lex.token(ignoreNewlines) == "[") {
            //Parse function application
            while (lex.token(ignoreNewlines) == "(") {
                shared_ptr<FunctionApplication> funApp = make_shared<FunctionApplication>(result);
                lex++;
                if (lex.token(true) == ")") {
                    lex++;
                } else {
                    funApp->addArgument(parseExpression(lex, true, false));
                    while (lex.token(true) == ",") {
                        lex++;
                        funApp->addArgument(parseExpression(lex, true, false));
                    }
                    lex.expect(")", true);
                }
                result = funApp;
            }

            //Parse list access
            while (lex.token(ignoreNewlines) == "[") {
                lex++;
                result = make_shared<ListAccess>(result, parseExpression(lex, true));
                lex.expect("]", true);
            }
        }
        return result;
    }

    shared_ptr<Expression> parseExpression(Lexer& lex, bool ignoreNewlines, bool skipPost) {
        shared_ptr<Expression> result = nullptr;
        string tok = lex.token(ignoreNewlines);
        int op = toOperator(tok, false);

        if (tok == "\n") {
            auto err = SyntaxError("Unexpected newline.", lex.line, lex.column);
            lex++;
            throw err;
        } else if (tok == "(") {
            //Parse expression inside parethesis
            lex++;
            result = parseExpression(lex, true, false);
            lex.expect(")", true);
        } else if (operatorType(op) == OperatorType::Unary) {
            //Parse prefix unary operator
            lex++;
            result = make_shared<UnaryOp>(op, parseExpression(lex, ignoreNewlines, true));
        } else if (tok == "[") {
            //Parse a list literal
            lex++;
            auto l = make_shared<List>();
            if (lex.token(true) != "]") {
                l->list.push_back(parseExpression(lex, true));
                while (lex.token(true) == ",") {
                    lex++;
                    l->list.push_back(parseExpression(lex, true));
                }
            }
            lex.expect("]", true);
            result = l;
        } else if (regex_match(tok, intRegex)) {
            //Parse numbers
            lex++;
            if (lex.token() == ".") {
                //Float value
                lex++;
                tok += ".";
                if (!regex_match(lex.token(), fractionRegex)) {
                    auto err = SyntaxError("Error parsing float.", lex.line, lex.column);
                    lex++;
                    throw err;
                }
                tok += lex.token();
                lex++;
                result = make_shared<Float>(stof(tok));
            } else {
                result = make_shared<Int>(stoi(tok));
            }
        } else if (regex_match(tok, nameRegex)) {
            //Parse a variable
            result = make_shared<Variable>(tok);
            lex++;
        } else if (regex_match(tok, charRegex)) {
            //Parse a character literal
            string s = tok.substr(1, tok.size() - 2);
            char c;
            if (s == "\\n") c = '\n';
            else if (s == "\\r") c = '\r';
            else if (s == "\\t") c = '\t';
            else if (s == "\\'") c = '\'';
            else if (s == "\\\\") c = '\\';
            else c = s[0];
            result = make_shared<Char>(c);
            lex++;
        } else if (regex_match(tok, stringRegex)) {
            //Parse a string literal
            auto str = make_shared<String>(tok.substr(1, tok.size() - 2));
            replaceSubstring(str->value, "\\n", "\n");
            replaceSubstring(str->value, "\\r", "\r");
            replaceSubstring(str->value, "\\t", "\t");
            replaceSubstring(str->value, "\\\"", "\"");
            replaceSubstring(str->value, "\\\\", "\\");
            result = str;
            lex++;
        } else {
            auto err = SyntaxError("Unexpected token \"" + tok + "\".", lex.line, lex.column);
            lex++;
            throw err;
        }

        if (skipPost) {
            return result;
        }

        if (lex.token(ignoreNewlines) == "(" || lex.token(ignoreNewlines) == "[") {
            result = parseAppl(lex, result, ignoreNewlines);
        }

        //Parse postfix and infix operators
        op = toOperator(lex.token(ignoreNewlines), true);
        while (op != Operator::None) {
            if (operatorType(op) == OperatorType::Unary) {
                //Parse postfix unary operator
                lex++;
                result = make_shared<UnaryOp>(op, result);
                op = toOperator(lex.token(ignoreNewlines), true);
            } else if (operatorType(op) == OperatorType::Binary) {
                //Parse binary operators
                result = parseBinaryOp(lex, result, op, ignoreNewlines);
                op = toOperator(lex.token(ignoreNewlines), true);
            }
        }

        return result;
    }

    shared_ptr<Expression> parseBinaryOp(Lexer& lex, shared_ptr<Expression> lhs, int op, bool ignoreNewlines) {
        shared_ptr<Expression> result;

        if (associativityOf(op) == Associativity::Right) {
            //Parse right associative binary operator
            lex++;
            result = make_shared<BinaryOp>(op, lhs, parseExpression(lex, ignoreNewlines, false));
        } else {
            //Parse left associative binary operator
            result = lhs;
            int op2 = op;
            int precedence = precedenceOf(op);
            int precedence2 = precedence;
            do {
                lex++;
                auto rhs = parseExpression(lex, ignoreNewlines, true);
                string tok = lex.token(ignoreNewlines);
                int op3 = toOperator(tok, true);
                if (op3 != Operator::None && precedenceOf(op3) < precedence2) {
                    //Parse recursively for higher precedence operators
                    rhs = parseBinaryOp(lex, rhs, op3, ignoreNewlines);
                } else if ((tok == "(" || tok == "[") && precedence2 > 1) {
                    rhs = parseAppl(lex, rhs, ignoreNewlines);
                }
                result = make_shared<BinaryOp>(op2, result, rhs);
                if ((tok == "(" || tok == "[") && precedence2 == 1) {
                    result = parseAppl(lex, result, ignoreNewlines);
                }
                op2 = toOperator(lex.token(ignoreNewlines), true);
                precedence2 = precedenceOf(op2);
            } while (operatorType(op2) == OperatorType::Binary &&
                     associativityOf(op2) == Associativity::Left &&
                     precedence2 <= precedence);
        }

        return result;
    }

    string parseName(Lexer& lex, bool ignoreNL = false) {
        string name = lex.token(ignoreNL);
        if (!regex_match(name, nameRegex)) {
            auto err = SyntaxError("Expected name token, got \"" + name + "\".", lex.line, lex.column);
            lex++;
            throw err;
        }
        lex++;
        return name;
    }

    void parseBlock(Lexer& lex, vector<shared_ptr<Statement>>& block, unsigned indent) {
        lex.ignoreNewlines();
        unsigned nextIndent = lex.getIndent();
        if (nextIndent <= indent) {
            throw SyntaxError("Indentation error.", lex.line, lex.column);
        }
        do {
            block.push_back(parseStatement(lex));
            lex.ignoreNewlines();
        } while (lex.getIndent() >= nextIndent);
    }

    shared_ptr<Statement> parseStatement(Lexer& lex) {
        string tok = lex.token(true);
        if (tok == "let") {
            auto lets = make_shared<LetStatement>();
            do {
                lex++;
                string name = parseName(lex);
                lex.expect("=");
                lets->addDeclaration(name, parseExpression(lex));
            } while (lex.token() == ",");
            lex.expect("\n");
            return lets;
        }

        if (tok == "fn") {
            auto fd = make_shared<FunctionDefinition>();
            unsigned indent = lex.getIndent();
            lex++;
            fd->name = parseName(lex);
            lex.expect("(");

            if (lex.token(true) != ")") {
                fd->addParameter(parseName(lex, true));
                while (lex.token(true) == ",") {
                    lex++;
                    fd->addParameter(parseName(lex, true));
                }
            }
            lex.expect(")", true);
            lex.expect("\n");
            parseBlock(lex, fd->block, indent);

            return fd;
        }

        if (tok == "sc") {
            auto sc = make_shared<NamedScope>();
            unsigned indent = lex.getIndent();
            lex++;
            sc->name = parseName(lex);
            lex.expect("\n");
            parseBlock(lex, sc->block, indent);
            return sc;
        }

        if (tok == "pass") {
            lex++;
            lex.expect("\n");
            return make_shared<Pass>();
        }

        if (tok == "return") {
            lex++;
            auto ret = make_shared<ReturnStatement>();
            if (lex.token(false) != "\n") ret->expression = parseExpression(lex);
            lex.expect("\n");
            return ret;
        }

        if (tok == "if") {
            unsigned indent = lex.getIndent();
            auto ifStat = make_shared<IfStatement>();

            while (lex.token() == "if") {
                lex++;
                auto cond = parseExpression(lex);
                lex.expect("\n");
                vector<shared_ptr<Statement>> block;
                parseBlock(lex, block, indent);
                ifStat->ifs.push_back(make_pair(cond, block));
                lex.ignoreNewlines();
                if (lex.token() == "else" && lex.lookAhead(1) == "if") lex++;
            }

            if (lex.token() == "else") {
                lex++;
                lex.expect("\n");
                parseBlock(lex, ifStat->otherwise, indent);
            }

            return ifStat;
        }

        if (tok == "while") {
            unsigned indent = lex.getIndent();
            auto wh = make_shared<While>();
            lex++;
            wh->condition = parseExpression(lex);
            lex.expect("\n");
            parseBlock(lex, wh->block, indent);
            return wh;
        }

        if (tok == "do") {
            unsigned indent = lex.getIndent();
            auto dowh = make_shared<DoWhile>();
            lex++;
            lex.expect("\n");
            parseBlock(lex, dowh->block, indent);
            lex.expect("while");
            dowh->condition = parseExpression(lex);
            lex.expect("\n");
            return dowh;
        }

        if (tok == "for") {
            unsigned indent = lex.getIndent();
            lex++;
            auto foreach = make_shared<ForEach>();
            foreach->var = parseName(lex);
            lex.expect("in");
            foreach->list = parseExpression(lex);
            lex.expect("\n");
            parseBlock(lex, foreach->block, indent);
            return foreach;
        }

        unsigned indent = lex.getIndent();
        auto expr = parseExpression(lex);

        return make_shared<ExpressionStatement>(expr);
    }
}