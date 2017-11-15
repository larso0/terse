#include "Lexer.h"
#include "SyntaxError.h"
#include <stdexcept>
#include <sstream>
#include <cstring>

using namespace std;

namespace Terse {

    static const char *TOKEN_CHARS = "(),.[]:+-*/%!=<>|&'\"\n";

    static bool isToken(int c) {
        return strchr(TOKEN_CHARS, c) != nullptr;
    }

    static bool isWhitespace(int c) {
        return c == ' ' || c == '\t';
    }

    Lexer::Lexer(istream &in) : in(in), indent(0), updateIndent(true), line(0), column(0) {
    }

    void Lexer::checkLineColumn(int c) {
        if (c == '\n') {
            line++;
            column = 0;
        } else {
            column++;
        }
    }

    void Lexer::flush() {
        int c;
        while ((c = get()) != EOF) {
            if (isWhitespace(c)) {
                if (updateIndent) indent++;
            } else if (c == '/') {
                int c2 = peek();
                if (c2 == '/') {
                    ignoreChar();
                    while ((c = peek()) != EOF && c != '\n') ignoreChar();
                    indent = 0;
                    updateIndent = true;
                } else if (c2 == '*') {
                    ignoreChar();
                    while ((c = get()) != EOF) {
                        if (c == '*' && peek() == '/') {
                            ignoreChar();
                            break;
                        }
                    }
                    updateIndent = false;
                } else {
                    in.unget();
                    break;
                }
            } else {
                in.unget();
                break;
            }
        }
        updateIndent = false;
    }

    unsigned Lexer::getIndent() const {
        return lookAheadQueue.empty() ? 0 : lookAheadQueue.front().indent;
    }

    const string& Lexer::token(bool ignoreNl) {
        if (ignoreNl) ignoreNewlines();
        return lookAhead(0);
    }

    void Lexer::ignore() {
        lookAhead(1);
        lookAheadQueue.pop_front();
    }

    void Lexer::ignoreNewlines() {
        try {
            while (lookAhead(0) == "\n") ignore();
        } catch (...) {}
    }

    void Lexer::expect(const string &tok, bool ignoreNewlines) {
        const string& n = token(ignoreNewlines);
        if (n != tok) {
            stringstream ss;
            ss << "Expected token \"" << tok
               << "\", but got ";
            if (n == "\n") ss << "newline.";
            else ss << '\"' << n << "\".";
            auto err = SyntaxError(ss.str(), line, column);
            ignore();
            throw err;
        }
        ignore();
    }

    bool Lexer::good() {
        return lookAheadQueue.size() > 1 || peek() != EOF;
    }

    const std::string& Lexer::lookAhead(unsigned steps) {
        for (unsigned i = lookAheadQueue.size(); i <= steps; i++) enqueueToken();
        if (lookAheadQueue.size() <= steps) throw runtime_error("Not enough tokens.");
        return lookAheadQueue[steps].token;
    }

    unsigned Lexer::lookAheadIndent(unsigned steps) {
        for (unsigned i = lookAheadQueue.size(); i <= steps; i++) enqueueToken();
        return lookAheadQueue[steps].indent;
    }

    void Lexer::enqueueToken() {
        flush();

        int c = peek();
        if (c == EOF) return;

        stringstream ss;

        if (isToken(c)) {
            ss << (char) c;
            ignoreChar();
            if (c == '\n') {
                indent = 0;
                updateIndent = true;
            } else if (c == '\"') {
                //Token is a string, read until closing quote.
                while ((c = get()) != EOF && c != '\"') {
                    ss << (char) c;
                    if (c == '\\') {
                        c = get();
                        if (c != EOF) ss << (char) c;
                    }
                }
                if (c != EOF) ss << '\"';
                else throw runtime_error("Reached EOF in string literal.");
            } else if (c == '\'') {
                //Token is a character literal, read until closing quote.
                while ((c = get()) != EOF && c != '\'') {
                    ss << (char) c;
                    if (c == '\\') {
                        c = get();
                        if (c != EOF) ss << (char) c;
                    }
                }
                if (c != EOF) ss << '\'';
                else throw runtime_error("Reached EOF in character literal.");
            } else {
                //Check for two char tokens
                int c2 = peek();
                if (c2 == c && (c == '+' || c == '-') ||
                    c == ':' && c2 == '=' ||
                    c2 == '=' && strchr("!<>+-*/", c)) {
                    ss << (char) c2;
                    ignoreChar();
                }
            }
        } else {
            do {
                if (isWhitespace(c) || isToken(c)) break;
                ss << (char) c;
                ignoreChar();
            } while ((c = peek()) != EOF);
        }

        lookAheadQueue.push_back({ ss.str(), indent });
    }
}


