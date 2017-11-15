#ifndef TERSE_LEXER_H_
#define TERSE_LEXER_H_

#include <string>
#include <iostream>
#include <deque>

namespace Terse {

    /*
     * Lexer for the terse language.
     * Get tokens one by one from an input stream, keeping track of indentation
     * levels.
     */
    class Lexer {
    public:

        /*
         * Constructor for custom input stream.
         */
        Lexer(std::istream& in = std::cin);

        /*
         * Get the current indentation level.
         * Initial indentation is 0.
         * The indentation level of a token that comes after a block comment,
         * is the same indentation level as before the start of the block
         * comment.
         */
        unsigned getIndent() const;

        /*
         * Fetch the current token.
         */
        const std::string& token(bool ignoreNewlines = false);

        /*
         * Ignore tokens
         */
        void ignore();
        void ignoreNewlines();

        Lexer& operator++(int) {
            ignore();
            return *this;
        }
        Lexer& operator++() {
            ignore();
            return *this;
        }

        /*
         * Expect a given token as the next one.
         * If the fetched token is not equal to the expected one, a
         * runtime_error is thrown.
         */
        void expect(const std::string& token, bool ignoreNewlines = false);

        /*
         * Returns true if there are more tokens to be fetched.
         */
        bool good();

        /*
         * Fetch a token at a certain number of steps forward without discarding
         * the token or the intermediate tokens.
         */
        const std::string& lookAhead(unsigned steps);

        /*
         * Get the indentation level of a token at a certain number of steps.
         */
        unsigned lookAheadIndent(unsigned steps);

        /*
         * Removes whitespace and comments from the input stream until a token
         * is reached, keeping track of indentation.
         */
        void flush();

        unsigned line, column;

    private:
        std::istream& in;
        unsigned indent;
        bool updateIndent;

        struct Token {
            std::string token;
            unsigned indent;
        };
        std::deque<Token> lookAheadQueue;

        /*
         * Reads a token from the input stream and enqueues it to the lookAhead
         * queue.
         */
        void enqueueToken();

        void checkLineColumn(int c);

        int peek() { return in.peek(); }
        int get() {
            int c = in.get();
            checkLineColumn(c);
            return c;
        }
        void ignoreChar() {
            checkLineColumn(in.get());
        }
    };

}

#endif
