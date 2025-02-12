#include <iostream>
#include <iomanip>
#include <string>
#include "tree.h"

#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"


std::ostream& operator<<(std::ostream& stream, const Point2D& p){
    stream << '{'<< p.x << ',' << p.y << '}';
    return stream;
};

void freemem(treeNode *tN)
{
    if (tN != nullptr)
    {
        freemem(tN->left);
        freemem(tN->right);
        delete tN;
    }
}

tree::~tree()
{
    freemem(this->root);
}

void tree::addPoint(double val)
{
    if (this->root == nullptr)
    {
        this->root = new treeNode(val);
    }
    else
    {
        treeNode *curruntNode = this->root;
        while (curruntNode != NULL)
        {
            if (curruntNode->val == val)
            {
                std::cerr << "Point has already exist!";
                return;
            }
            if (curruntNode->val < val)
            {
                if (curruntNode->left == NULL)
                {
                    curruntNode->left = new treeNode(val, curruntNode);
                    return;
                }
                curruntNode = curruntNode->left;
                continue;
            }
            if (curruntNode->val > val)
            {
                if (curruntNode->right == NULL)
                {
                    curruntNode->right = new treeNode(val, curruntNode);
                    return;
                }
                curruntNode = curruntNode->right;
                continue;
            }
        }
    }
}
treeNode *tree::findPoint(double val)
{
    treeNode *curruntNode = this->root;

    while (curruntNode != nullptr)
    {
        if (curruntNode->val == val)
        {
            return curruntNode;
        }
        if (curruntNode->val < val)
        {
            curruntNode = curruntNode->left;
        }
        if (curruntNode->val > val)
        {
            curruntNode = curruntNode->right;
        }
    }
    return curruntNode;
}

void printTree(treeNode* root, const std::string& prefix, bool isLeft)
{
    if (root == nullptr) return;
    // Выводим текущий узел
    std::cout << prefix;
    std::cout << (isLeft ? "┌──" : "└──");
    std::cout << COLOR_GREEN << root->val << COLOR_RESET << '\n';

    // Рекурсивно выводим левое и правое поддеревья
    printTree(root->left, prefix + (isLeft ? "│   " : "    "), true);
    printTree(root->right, prefix + (isLeft ? "│   " : "    "), false);
}