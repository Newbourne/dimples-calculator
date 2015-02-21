#ifndef NODEBUILDER_H
#define NODEBUILDER_H

#include <string>
#include <ostream>
#include <boost/regex.hpp>
#include "MathNode.h"
#include "Operations.h"
#include "Generator.h"

using namespace std;

/*
    Given a string representation of a math problem.
    Recursively parse the string and calculate the answer.
    Must be able to work with the following operators:
    +       Addtion
    -       Subtraction
    x or *  Multiplication
    /       Division (Obelus?)
    ^       Exponents
            Square Root (later)
    ()      Parenthesis

    Must follow the order of operations.
 */

static const boost::regex operandRegex("^(\\-?)(\\d+)?(\\d|\\.)?(\\d)+");
static const boost::regex operatorRegex("(\\+|\\-|\\(|\\)|/|\\*|x|\\^)");

class NodeBuilder {
private:
    MathNode* root = nullptr;
    string equation;
    bool operandCheck(const string check);
    bool operatorCheck(const char check);
    void traverse(MathNode* position, string padding);
    MathNode* build(MathNode* root, MathNode* operandNode, MathNode* operatorNode);
    double solveRec(MathNode*);
    string getEquation(MathNode*);

public:
    NodeBuilder();
    ~NodeBuilder();
    void parse(string equation);
    void print(string padding);
    double solve();
    void generate(int operandCount, int operandLengthMin,
                  int operandLengthMax, string operations);
    string buildEquation();
};

#endif
