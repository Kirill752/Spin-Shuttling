#include <iostream>
#include <iomanip>
#include <string>
#include "tree.h"

#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"

std::ostream &operator<<(std::ostream &stream, const Point2D &p)
{
    stream << '{' << p.x << ',' << p.y << '}';
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

tree::tree(treeNode *L, treeNode *R)
{
    this->root = new treeNode((L->val + R->val) / 2);
    this->leftEnd = L;
    this->rightEnd = R;
    this->root->left = this->leftEnd;
    this->root->right = this->rightEnd;
}

tree::tree(double L, double R)
{
    this->root = new treeNode((L + R) / 2);
    this->leftEnd = new treeNode(L);
    this->rightEnd = new treeNode(R);
    this->root->left = this->leftEnd;
    this->root->right = this->rightEnd;
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
                if (curruntNode->left == this->leftEnd)
                {
                    treeNode *buf = this->leftEnd;
                    curruntNode->left = new treeNode(val, curruntNode);
                    curruntNode->left->left = buf;
                    return;
                }

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
                if (curruntNode->right == this->rightEnd)
                {
                    treeNode *buf = this->rightEnd;
                    curruntNode->right = new treeNode(val, curruntNode);
                    curruntNode->right->right = buf;
                    return;
                }
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

void tree::deletePoint(double val) {
    treeNode *curentNode = this->findPoint(val);
    // Если у узда нет потомков, то просто удаляем его
    if (curentNode->left == nullptr && curentNode->right == nullptr)
    {
        if (curentNode->root->left == curentNode){
            curentNode->root->left = nullptr;
        }
        else {
            curentNode->root->right = nullptr;
        }   
        curentNode->~treeNode();
        return;
    }
    // Если у узла один потомок, то на место текущего узла ставим его потомка
    if (curentNode->left != nullptr)
    {
        if (curentNode->root->left == curentNode){
            curentNode->root->left = curentNode->left;
        }
        else {
            curentNode->root->right = curentNode->left;
        }
        curentNode->~treeNode();
        return;
    }
    if (curentNode->right != nullptr)
    {
        if (curentNode->root->left == curentNode){
            curentNode->root->left = curentNode->right;
        }
        else {
            curentNode->root->right = curentNode->right;
        }
        curentNode->~treeNode();
        return;
    }
    // Если у узла два потомка, то ищем узел с минимальным значением в правом поддереве этого узла
    treeNode *toReplace = curentNode->right;
    for (; toReplace->left != nullptr; toReplace = toReplace->left) {
    }
}

void printTree(treeNode *root, const std::string &prefix = "", bool isLeft = true)
{
    if (root == nullptr)
        return;
    // Выводим текущий узел
    std::cout << prefix;
    std::cout << (isLeft ? "┌──" : "└──");
    std::cout << COLOR_GREEN << root->val << COLOR_RESET << '\n';

    // Рекурсивно выводим левое и правое поддеревья
    printTree(root->left, prefix + (isLeft ? "│   " : "    "), true);
    printTree(root->right, prefix + (isLeft ? "│   " : "    "), false);
}