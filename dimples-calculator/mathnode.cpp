#include <string>
#include "MathNode.h"

using namespace std;

MathNode::MathNode(MathNode* parent, NodeType nodeType, string text){
    this->parent = parent;
    this->nodeType = nodeType;
    this->text = text;
}

MathNode::MathNode(MathNode* parent, NodeType nodeType, char text){
    this->parent = parent;
    this->nodeType = nodeType;
    string text2;
    text2.push_back(text);
    this->text = text2;
}

MathNode::MathNode(NodeType nodeType, string text){
    this->nodeType = nodeType;
    this->text = text;
}

MathNode::MathNode(NodeType nodeType, char text){
    this->nodeType = nodeType;
    string text2;
    text2.push_back(text);
    this->text = text2;
}

MathNode::~MathNode(){
    if(this->getLeft())
        delete this->left;
    if(this->getRight())
        delete this->right;
}

NodeType MathNode::getNodeType(){
    return this->nodeType;
}

string MathNode::getText(){
    return this->text;
}

MathNode* MathNode::getParent(){
    return this->parent;
}

MathNode* MathNode::getLeft(){
    return this->left;
}

MathNode* MathNode::getRight(){
    return this->right;
}

void MathNode::setParent(MathNode* node){
    this->parent = node;
}

void MathNode::setLeft(MathNode* node){
    this->left = node;
}

void MathNode::setRight(MathNode* node){
    this->right = node;
}

void MathNode::setPlaceholder(bool isPlaceholder){
    this->isPlaceholder = isPlaceholder;
}

bool MathNode::getPlaceholder(){
    return this->isPlaceholder;
}
