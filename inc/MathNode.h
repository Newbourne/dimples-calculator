#ifndef MATHNODE_H
#define MATHNODE_H

#include <string>

using namespace std;

enum NodeType { Operator, Operand };

class MathNode{
private:
    MathNode* parent = NULL;
    MathNode* left = NULL;
    MathNode* right = NULL;
    NodeType nodeType;
    string text = "";
    bool isPlaceholder = false;
public:
    MathNode(MathNode* parent, NodeType nodeType, string text);
    MathNode(MathNode* parent, NodeType nodeType, char text);
    MathNode(NodeType nodeType, string text);
    MathNode(NodeType nodeType, char text);
    ~MathNode();
    NodeType getNodeType();
    string getText();
    MathNode* getParent();
    MathNode* getLeft();
    MathNode* getRight();
    void setParent(MathNode* node);
    void setRight(MathNode* node);
    void setLeft(MathNode* node);
    void setPlaceholder(bool);
    bool getPlaceholder();
};

#endif
