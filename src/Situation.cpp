#include <string>
#include <boost/regex.hpp>
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/random_generator.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.

#include "Situation.h"

using namespace std;

Situation::Situation(){
    srand (time(NULL));
    //default construct the random number generator and seed it
    boost::uuids::random_generator gen;
    boost::uuids::uuid u = gen();
    this->uuid = to_string(u);
}

Situation::Situation(string source) : Situation(){
    this->source = source;
}

Situation::~Situation(){
    if(this->categories) delete this->categories;
    if(this->root) delete this->root;
}

bool Situation::operandCheck(const string check){
    if(boost::regex_match(check, operandRegex)){
        return true;
    }
    else{
        return false;
    }
}

bool Situation::operatorCheck(const char check){
    std::string validate;
    validate.push_back(check);
    if(boost::regex_match(validate, operatorRegex)){
        return true;
    }
    else{
        return false;
    }
}

double Situation::solve(MathNode* position){
    double value_left = 0;
    double value_right = 0;

    if(position->getNodeType() == NodeType::Operand){
        return atof(position->getText().c_str());
    }

    if(position->getLeft()){
        value_left = solve(position->getLeft());
    }

    if(position->getRight()){
        value_right = solve(position->getRight());
    }

    double value = 0;
    if(position->getText() == "+")
        value = Operations::add(value_left, value_right);
    else if(position->getText() == "-")
        value = Operations::subtract(value_left, value_right);
    return value;
}

MathNode* Situation::buildTree(MathNode* position, MathNode* operandNode, MathNode* operatorNode){
    if(!position){
        if(!operandNode && !operatorNode){
            return new MathNode(NodeType::Operand, "0");
        }
        else if(operandNode && !operatorNode){
            position = operandNode;
        }
        else{
            operatorNode->setLeft(operandNode);
            operandNode->setParent(operatorNode);
            MathNode* placeholder = nullptr;
            if(operatorNode->getText() == "+" || operatorNode->getText() == "-"){
                placeholder = new MathNode(operatorNode, NodeType::Operand, "0");
            }
            else{
                placeholder = new MathNode(operatorNode, NodeType::Operand, "1");
            }
            placeholder->setPlaceholder(true);
            operatorNode->setRight(placeholder);
            position = operatorNode;
        }
    }
    else{
        if(position->getRight()->getPlaceholder() && !operatorNode){
            position->setRight(operandNode);
            operandNode->setParent(position);
            position->setPlaceholder(false);
        }
        else if(position->getRight()->getPlaceholder() && operatorNode){
            MathNode* placeholder = nullptr;
            if(operatorNode->getText() == "+" || operatorNode->getText() == "-"){
                placeholder = new MathNode(operatorNode, NodeType::Operand, "0");
                placeholder->setPlaceholder(true);
                position->setRight(operandNode);
                operandNode->setParent(position);
                operatorNode->setRight(placeholder);
                operatorNode->setLeft(position);
                position->setParent(operatorNode);
                return operatorNode;
            }
            else{
                placeholder = new MathNode(operatorNode, NodeType::Operand, "1");
            }
        }
        else{

        }
    }
    return position;
}

string Situation::buildEquation(MathNode* position){
    if(!position){
        return "";
    }
        
    if(position->getNodeType() == NodeType::Operand){
        return position->getText();
    }
    
    return buildEquation(position->getLeft()) + position->getText() + buildEquation(position->getRight());
}

void Situation::parse(string equation){
    this->equation = equation;

    string operand = "0";
    for(int i=0; i<(int)equation.length(); i++){
        char charIndex = equation[i];

        if(charIndex == ' '){
            continue;
        }

        string tempOperand = operand;
        tempOperand.push_back(charIndex);

        if(operandCheck(tempOperand)){
            operand.push_back(charIndex);
            if(i == (int)equation.length()-1){
                MathNode* operandNode = new MathNode(NodeType::Operand, operand);
                this->root = buildTree(this->root, operandNode, nullptr);
            }
            else
                continue;
        }
        else if(operatorCheck(charIndex)){
            if(i == 0){
                // leading character is operator
                if(charIndex != '-'){
                    // ignore all leading operators not satisfied
                    continue;
                }
            }
            MathNode* operandNode = new MathNode(NodeType::Operand, operand);
            MathNode* operatorNode = new MathNode(NodeType::Operator, charIndex);
            this->root = buildTree(this->root, operandNode, operatorNode);
            operand = "0";
        }
    }
    this->equation = this->buildEquation(this->root);
    this->solution = this->solve(this->root);
}

void Situation::generate(int operandCount, int operandLengthMin,
                           int operandLengthMax, string operations){
    if(this->root){
        delete this->root;
        this->root = nullptr;
    }

    for(int i = 0; i < operandCount; i++){
        if (i == operandCount-1){
            string operand_str = Generator::operand(operandLengthMin, operandLengthMax);
            MathNode* operandNode = new MathNode(NodeType::Operand, operand_str);
            this->root = this->buildTree(this->root, operandNode, nullptr);
        }
        else{
            int op_index = rand() % operations.length();
            char op = operations[op_index];
            string operand_str = Generator::operand(operandLengthMin, operandLengthMax);
            MathNode* operandNode = new MathNode(NodeType::Operand, operand_str);
            MathNode* operatorNode = new MathNode(NodeType::Operator, op);
            this->root = this->buildTree(this->root, operandNode, operatorNode);
        }
    }
    this->equation = this->buildEquation(this->root);
    this->solution = this->solve(this->root);
}

string* Situation::getCategories(){
    return this->categories;
}

string Situation::getUUID(){
    return this->uuid;
}

string Situation::getSource(){
    return this->source;
}

string Situation::getEquation(){
    return this->equation;
}

double Situation::getSolution(){
    return this->solution;
}