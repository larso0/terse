#include "Lexer.h"
#include "Parser.h"
#include "Evaluation/Evaluator.h"
#include <fstream>

using namespace std;
using namespace Terse;

class ExitReturn {
public:
    ExitReturn(int v) : value(v) {}

    int value;
};

int main(int argc, char** argv) {
    ifstream file;
    if (argc == 2) {
        file.open(argv[1]);
    }

    shared_ptr<Lexer> lex;
    if (file.is_open()) {
        lex = make_shared<Lexer>(file);
    } else {
        lex = make_shared<Lexer>();
    }
    shared_ptr<Environment> env = make_shared<Environment>();

    //Print function in environment
    auto printFun = make_shared<FunctionValue>();
    printFun->call = [](vector<shared_ptr<Value>>& args) -> shared_ptr<Value> {
        for (auto val : args) {
            val->print();
        }
        return make_shared<Undefined>();
    };
    env->set("print", printFun);

    //Function to get the length of a list
    auto lenFun = make_shared<FunctionValue>();
    lenFun->call = [](vector<shared_ptr<Value>>& args) -> shared_ptr<Value> {
        if (args.size() != 1) {
            throw invalid_argument("Mismathing arguments.");
        }
        auto list = dynamic_cast<ListValue*>(args[0].get());
        if (!list) {
            throw invalid_argument("Argument is not a list.");
        }
        return make_shared<IntValue>(list->list.size());
    };
    env->set("length", lenFun);

    //Append elements to a list with the append function
    auto appFun = make_shared<FunctionValue>();
    appFun->call = [](vector<shared_ptr<Value>>& args) -> shared_ptr<Value> {
        if (args.size() < 2) {
            throw invalid_argument("Too few arguments.");
        }
        auto list = dynamic_cast<ListValue*>(args[0].get());
        if (!list) {
            throw invalid_argument("First argument must be a list.");
        }
        for (auto iter = args.begin() + 1; iter != args.end(); iter++) {
            list->listAdd(*iter);
        }
        return make_shared<Undefined>();
    };
    env->set("append", appFun);

    auto require = make_shared<FunctionValue>();
    require->call = [&env](vector<shared_ptr<Value>>& args) -> shared_ptr<Value> {
        if (args.size() != 1) {
            throw invalid_argument("Mismatching arguments.");
        }
        auto s = dynamic_cast<StringValue*>(args[0].get());
        if (!s) {
            throw invalid_argument("Argument is not a string.");
        }
        string ss = s->stringContent();
        ifstream file(ss);
        if (!file.is_open()) {
            throw runtime_error("Can't open file \"" + ss + "\".");
        }
        Lexer lex(file);
        lex.ignoreNewlines();
        while (lex.good()) {
            evaluateStatement(parseStatement(lex), env);
            lex.ignoreNewlines();
        }
        return make_shared<Undefined>();
    };
    env->set("require", require);

    //Allow to exit using the exit function with optional exit return code (default 0)
    int retVal = 0;
    bool running = true;
    auto exitFun = make_shared<FunctionValue>();
    exitFun->call = [&retVal, &running](vector<shared_ptr<Value>>& args) -> shared_ptr<Value> {
        if (args.size() > 0) {
            if (args.size() == 1 && dynamic_cast<IntValue*>(args[0].get())) {
                throw ExitReturn(static_cast<IntValue*>(args[0].get())->value);
            } else {
                throw invalid_argument("Invalid arguments for exit function.");
            }
        }
        throw ExitReturn(0);
    };
    env->set("exit", exitFun);

    lex->ignoreNewlines();
    while (running && lex->good()) {
        try {
            auto ret = evaluateStatement(parseStatement(*lex), env);
            if (!dynamic_cast<Undefined*>(ret.get())) {
                cout << "Value: " << ret->toString() << endl;
            }
        } catch (const ExitReturn& e) {
            return e.value;
        } catch (const exception& e) {
            cerr << e.what() << endl;
        }
        lex->ignoreNewlines();
    }

    return 0;
}
