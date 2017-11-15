#ifndef TERSE_PARSER_H
#define TERSE_PARSER_H

#include "Lexer.h"
#include "AST/AST.h"
#include <utility>

namespace Terse {

    std::shared_ptr<Expression> parseExpression(Lexer& lex, bool ignoreNewlines = false, bool skipPost = false);
    std::shared_ptr<Expression> parseBinaryOp(Lexer& lex, std::shared_ptr<Expression> lhs, int op, bool ignoreNewlines = false);
    std::shared_ptr<Statement> parseStatement(Lexer& lex);
}

#endif
