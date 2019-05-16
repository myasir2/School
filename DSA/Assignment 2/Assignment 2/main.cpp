//
//  main.cpp
//  Assignment 2
//
//  Created by Yasir Merchant on 2018-08-01.
//  Copyright © 2018 Yasir Merchant. All rights reserved.
//

#include <iostream>
#include <utility>
#include "table.h"
using namespace std;

int main(int argc, const char * argv[])
{
    hash<string> hashFunction;
    
    cout << "A hashed: " << hashFunction("a") % 10 << endl;

    return 0;
}
