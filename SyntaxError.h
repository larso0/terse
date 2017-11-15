#ifndef TERSE_SYNTAXERROR_H
#define TERSE_SYNTAXERROR_H

#include <stdexcept>
#include <sstream>

namespace Terse {

    class SyntaxError : public std::runtime_error {
    public:
        SyntaxError(const std::string& err, unsigned line, unsigned col) : std::runtime_error(errStr(err, line, col)) {}

    private:
        static std::string errStr(const std::string& err, unsigned line, unsigned col) {
            std::stringstream ss;
            ss << "Syntax error: " << err << " near (" << line << ", " << col << ')';
            return ss.str();
        }
    };

}

#endif
