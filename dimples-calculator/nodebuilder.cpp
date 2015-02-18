#include <string>
#include <ostream>
#include <boost/regex.hpp>
#include "MathNode.h"
#include "Operations.h"
#include "Generator.h"
#include "NodeBuilder.h"

using namespace std;

NodeBuilder::NodeBuilder(){
    srand (time(NULL));
}

NodeBuilder::~NodeBuilder(){
    if(this->root){
        delete this->root;
    }
}

bool NodeBuilder::operandCheck(const string check){
    if(boost::regex_match(check, operandRegex)){
        return true;
    }
    else{
        return false;
    }
}

bool NodeBuilder::operatorCheck(const char check){
    std::string validate;
    validate.push_back(check);
    if(boost::regex_match(validate, operatorRegex)){
        return true;
    }
    else{
        return false;
    }
}

void NodeBuilder::traverse(MathNode* position, string padding){
    if(!position){
        return;
    }
    padding = padding.append(padding);
    traverse(position->getLeft(), padding);
    //cout << padding << position->getText() << endl;
    traverse(position->getRight(), padding);
}

MathNode* NodeBuilder::build(MathNode* position, MathNode* operandNode, MathNode* operatorNode){
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

double NodeBuilder::solveRec(MathNode* position){
    double value_left = 0;
    double value_right = 0;

    if(position->getNodeType() == NodeType::Operand){
        return atof(position->getText().c_str());
    }

    if(position->getLeft()){
        value_left = solveRec(position->getLeft());
    }

    if(position->getRight()){
        value_right = solveRec(position->getRight());
    }

    double value = 0;
    if(position->getText() == "+")
        value = Operations::add(value_left, value_right);
    else if(position->getText() == "-")
        value = Operations::subtract(value_left, value_right);
    return value;
}

string NodeBuilder::getEquation(MathNode* position){
    if(!position)
        return "";
    if(position->getNodeType() == NodeType::Operand)
        return position->getText();
    return getEquation(position->getLeft()) + position->getText() + getEquation(position->getRight());
}

void NodeBuilder::parse(string equation){
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
                this->root = build(this->root, operandNode, nullptr);
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
            this->root = build(this->root, operandNode, operatorNode);
            operand = "0";
        }
    }
}

void NodeBuilder::print(string padding){
    this->traverse(this->root, padding);
}

double NodeBuilder::solve(){
    return this->solveRec(this->root);
}

void NodeBuilder::generate(int operandCount, int operandLengthMin,
                           int operandLengthMax, string operations){
    if(this->root){
        delete this->root;
        this->root = nullptr;
    }

    for(int i = 0; i < operandCount; i++){
        if (i == operandCount-1){
            string operand_str = Generator::operand(operandLengthMin, operandLengthMax);
            MathNode* operandNode = new MathNode(NodeType::Operand, operand_str);
            this->root = this->build(this->root, operandNode, nullptr);
        }
        else{
            int op_index = rand() % operations.length();
            char op = operations[op_index];
            string operand_str = Generator::operand(operandLengthMin, operandLengthMax);
            MathNode* operandNode = new MathNode(NodeType::Operand, operand_str);
            MathNode* operatorNode = new MathNode(NodeType::Operator, op);
            this->root = this->build(this->root, operandNode, operatorNode);
        }
    }
}

string NodeBuilder::buildEquation(){
    return this->getEquation(this->root);
}

