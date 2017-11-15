cmake_minimum_required(VERSION 3.6)
project(Terse)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Main.cpp
    Lexer.cpp
    Lexer.h
    AST/Expression.h
    Parser.cpp
    Parser.h
    AST/Int.h
    AST/Variable.h
    AST/UnaryOp.h
    AST/BinaryOp.h
    AST/AST.h
    AST/Operator.h
    AST/Operator.cpp
    AST/Statement.h
    AST/FunctionDefinition.h
    AST/FunctionApplication.h
    SyntaxError.h
    AST/LetStatement.h
    AST/ExpressionStatement.h
    AST/ReturnStatement.h
    Evaluation/Environment.h
    Evaluation/Value.h
    Evaluation/Environment.cpp
    Evaluation/IntValue.h
    Evaluation/Undefined.h
    Evaluation/Evaluator.h
    Evaluation/Values.h
    Evaluation/Evaluator.cpp
    Evaluation/FunctionValue.h AST/IfStatement.h AST/While.h AST/List.h AST/ListAccess.h Evaluation/ListValue.h AST/Pass.h AST/String.h Evaluation/StringValue.h AST/Char.h Evaluation/CharValue.h AST/ForEach.h AST/NamedScope.h Evaluation/ScopeValue.h AST/Float.h Evaluation/FloatValue.h)

add_executable(Terse ${SOURCE_FILES})