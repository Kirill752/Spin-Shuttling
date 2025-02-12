#include <iostream>
#include <vector>
#include "tree.h"
#include "point.h"

int main() {
    tree t(5.0);
    t.addPoint(0.0);
    t.addPoint(10.0);
    t.addPoint(2.5);
    t.addPoint(7.5);
    t.addPoint(1.25);
    t.addPoint(3.25);
    t.addPoint(8.25);
    t.addPoint(6.25);
    printTree(t.root);
}