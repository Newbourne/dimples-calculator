#include <string>

using namespace std;

enum NodeType { Operator, Operand };

class Node{
private:
    Node* parent = NULL;
    Node* left = NULL;
    Node* right = NULL;
    NodeType nodeType;
    string text;
    bool isPlaceholder = false;
public:
    Node(Node* parent, NodeType nodeType, string text);
    Node(Node* parent, NodeType nodeType, char text);
    Node(NodeType nodeType, string text);
    Node(NodeType nodeType, char text);
    NodeType getNodeType();
    string getText();
    Node* getParent();
    Node* getLeft();
    Node* getRight();
    void setParent(Node* node);
    void setRight(Node* node);
    void setLeft(Node* node);
    void setPlaceholder(bool);
    bool getPlaceholder();
};

Node::Node(Node* parent, NodeType nodeType, string text){
    this->parent = parent;
    this->nodeType = nodeType;
    this->text = text;
}

Node::Node(Node* parent, NodeType nodeType, char text){
    this->parent = parent;
    this->nodeType = nodeType;
    string text2;
    text2.push_back(text);
    this->text = text2;
}

Node::Node(NodeType nodeType, string text){
    this->nodeType = nodeType;
    this->text = text;
}

Node::Node(NodeType nodeType, char text){
    this->nodeType = nodeType;
    string text2;
    text2.push_back(text);
    this->text = text2;
}

NodeType Node::getNodeType(){
    return this->nodeType;
}

string Node::getText(){
    return this->text;
}

Node* Node::getParent(){
    return this->parent;
}

Node* Node::getLeft(){
    return this->left;
}

Node* Node::getRight(){
    return this->right;
}

void Node::setParent(Node* node){
    this->parent = node;
}

void Node::setLeft(Node* node){
    this->left = node;
}

void Node::setRight(Node* node){
    this->right = node;
}

void Node::setPlaceholder(bool isPlaceholder){
    this->isPlaceholder = isPlaceholder;
}

bool Node::getPlaceholder(){
    return this->isPlaceholder;
}
