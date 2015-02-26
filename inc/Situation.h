#ifndef SITUATION_H
#define SITUATION_H

#include <string>
#include <boost/regex.hpp>
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/random_generator.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.

#include "Operations.h"
#include "Generator.h"
#include "MathNode.h"

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

class Situation {
public:
    Situation();
    Situation(string source);
    ~Situation();
    void parse(string equation);
    void generate(int operandCount, int operandLengthMin,
                  int operandLengthMax, string operations);
    void setCategories(string* categories);
    string* getCategories();
    string getUUID();
    string getSource();
    string getEquation();
    double getSolution();
    
private:
    MathNode* root = nullptr;
    string* categories;
    string uuid;
    string source;
    string equation;
    double solution;

private:
    bool operandCheck(const string check);
    bool operatorCheck(const char check);
    double solve(MathNode* position);
    string buildEquation(MathNode* position);
    MathNode* buildTree(MathNode* root, MathNode* operandNode, MathNode* operatorNode);
    //void print(string padding);
    //void traverse(MathNode* position, string padding);
};

#endif

// void Situation::print(string padding){
//     this->traverse(this->root, padding);
// }

// void NodeBuilder::traverse(MathNode* position, string padding){
//     if(!position){
//         return;
//     }
//     padding = padding.append(padding);
//     traverse(position->getLeft(), padding);
//     //cout << padding << position->getText() << endl;
//     traverse(position->getRight(), padding);
// }