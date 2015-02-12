#include <string>
#include <node.h>
#include <operations.h>
#include <boost/regex.hpp>
#include <generator.h>

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

class NodeBuilder{
private:
    Node* root = nullptr;
    string equation;
    bool operandCheck(const string check);
    bool operatorCheck(const char check);
    void traverse(Node* position, string padding);
    Node* build(Node* root, Node* operandNode, Node* operatorNode);
    double solveRec(Node*);

public:
    NodeBuilder();
    void parse(string equation);
    void print(string padding);
    double solve();
    void generate(int operandCount, int operandLengthMin,
                  int operandLengthMax, string operations);
};

NodeBuilder::NodeBuilder(){

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

void NodeBuilder::traverse(Node* position, string padding){
    if(!position){
        return;
    }
    padding = padding.append(padding);
    traverse(position->getLeft(), padding);
    cout << padding << position->getText() << endl;
    traverse(position->getRight(), padding);
}

void NodeBuilder::parse(string equation){
    this->equation = equation;
    this->root = nullptr;

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
                Node* operandNode = new Node(NodeType::Operand, operand);
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
            Node* operandNode = new Node(NodeType::Operand, operand);
            Node* operatorNode = new Node(NodeType::Operator, charIndex);
            this->root = build(this->root, operandNode, operatorNode);
            operand = "0";
        }
    }
}

void NodeBuilder::print(string padding){
    this->traverse(this->root, padding);
}

Node* NodeBuilder::build(Node* position, Node* operandNode, Node* operatorNode){
    if(!position){
        if(!operandNode && !operatorNode){
            return new Node(NodeType::Operand, "0");
        }
        else if(operandNode && !operatorNode){
            position = operandNode;
        }
        else{
            operatorNode->setLeft(operandNode);
            operandNode->setParent(operatorNode);
            Node* placeholder = nullptr;
            if(operatorNode->getText() == "+" || operatorNode->getText() == "-"){
                placeholder = new Node(operatorNode, NodeType::Operand, "0");
            }
            else{
                placeholder = new Node(operatorNode, NodeType::Operand, "1");
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
            Node* placeholder = nullptr;
            if(operatorNode->getText() == "+" || operatorNode->getText() == "-"){
                placeholder = new Node(operatorNode, NodeType::Operand, "0");
                placeholder->setPlaceholder(true);
                position->setRight(operandNode);
                operandNode->setParent(position);
                operatorNode->setRight(placeholder);
                operatorNode->setLeft(position);
                position->setParent(operatorNode);
                return operatorNode;
            }
            else{
                placeholder = new Node(operatorNode, NodeType::Operand, "1");
            }
        }
        else{

        }
    }
    return position;
}

double NodeBuilder::solve(){
    return this->solveRec(this->root);
}

double NodeBuilder::solveRec(Node* position){
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

void NodeBuilder::generate(int operandCount, int operandLengthMin,
                           int operandLengthMax, string operations){
//    for(int i = 0; i < operandCount; i++){
//        //char op = '';
//        //if (i < operandCount-1){
//            int op_index = rand() + operations.length();
//            char op = operations[op_index];
//        //}
//        string operand = Generator::operand(operandLengthMin, operandLengthMax);
//    }

}
