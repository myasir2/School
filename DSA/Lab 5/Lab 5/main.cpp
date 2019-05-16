//
//  main.cpp
//  Lab 5
//
//  Created by Yasir Merchant on 2018-08-08.
//  Copyright © 2018 Yasir Merchant. All rights reserved.
//

#include <iostream>
#include "lab5.h"
using namespace std;

int main(int argc, const char * argv[])
{
    BST<int> tree;
    tree.insert(42);
    tree.insert(62);
    tree.insert(75);
    tree.insert(99);
    tree.insert(57);
    tree.insert(10);
    tree.insert(16);
    tree.insert(55);
    tree.insert(38);
    tree.insert(20);
    tree.insert(34);
    tree.insert(14);
    tree.insert(15);
    tree.insert(30);
    tree.insert(77);

    int min = tree.min(62);
    
    cout << "The min of the tree is: " << min << endl;
    
    return 0;
}
