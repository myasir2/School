//
//  main.cpp
//  Binary Search Tree
//
//  Created by Yasir Merchant on 2018-07-27.
//  Copyright © 2018 Yasir Merchant. All rights reserved.
//

#include <iostream>
#include "AVL.hpp"
using namespace std;

int main(int argc, const char * argv[])
{
    AVL<int> tree1;
    AVL<int> tree2;
    
    int dataset[20] = {10, 30, 20};
    
    for(int i = 0; i < 3; i++)
    {
        tree1.insert(dataset[i]);
        //tree2.insert(dataset[6-i]);
    }
    
    tree1.printInOrder();
    tree1.printPreOrder();
    
//    cout << "tree 2" << endl;
//    
//    tree2.printInOrder();
//    tree2.printPreOrder();
//    
//    bool found = tree1.exists(43342);
//    
//    cout << found << endl;
//    
    return 0;
}
