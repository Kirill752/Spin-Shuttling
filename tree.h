#ifndef TREE_H
#define TREE_H

#include <iostream>
#include "point.h"

struct treeNode
{
    double val;
    treeNode *root;
    treeNode *left;
    treeNode *right;
    treeNode(double val, treeNode *root = nullptr,
             treeNode *left = nullptr,
             treeNode *right = nullptr) : val(val),
                                          root(root),
                                          left(left),
                                          right(right)
    {
    }
    ~treeNode() {
        if (root != nullptr)
        {
            delete root;
        }
        if (left != nullptr){
            delete left;
        }
        if (right != nullptr)
        {
            delete right;
        }   
    }
};

class tree
{
public:
    treeNode *root;
    treeNode *leftEnd;
    treeNode *rightEnd;
    tree(treeNode *root) : root(root) {}
    tree(double val)
    {
        this->root = new treeNode(val);
    }
    tree(treeNode *L, treeNode *R);
    tree(double L, double R);
    ~tree();
    void addPoint(double val);
    treeNode *findPoint(double val);
    void deletePoint(double val);
};
void printTree(treeNode *root, const std::string &prefix, bool isLeft);
#endif
