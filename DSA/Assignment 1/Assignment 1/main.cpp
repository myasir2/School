//
//  main.cpp
//  Assignment 1
//
//  Created by Yasir Merchant on 2018-07-15.
//  Copyright © 2018 Yasir Merchant. All rights reserved.
//

#include <iostream>
#include <math.h>
using namespace std;

bool candidate(int array[],int& candidate, int sz);
bool majorityElement(const int arr[], int& majority, int sz);

int main()
{
    int array[21] = {5,5, 5,5, 5,5, 5,5, 4,4, 4,4, 4,4, 4,4, 4,4, 5,5, 3};
    int majority = 0;
    
    majorityElement(array, majority, 21);
    
    return 0;
}

bool majorityElement(const int arr[], int& majority, int sz)
{
    int *copyArray = new int[sz];
    int candidateNumber = 0;
    int copySize = sz;
    
    for(int i = 0; i < sz; i++)
    {
        copyArray[i] = arr[i];
    }
    
    candidate(copyArray, candidateNumber, copySize);
    
    cout << "Min size is: " << sz/2+1 << endl;
    
    int majorityCounter = 0;
    for(int i = 0; i < sz; i++)
    {
        if(arr[i] == candidateNumber)
        {
            majorityCounter++;
        }
        
        if(majorityCounter >= sz/2+1)
        {
            cout << "Majority is: " << candidateNumber << " returning true " << endl;
            
            majority = candidateNumber;
            return true;
        }
    }

    cout << "Majority is: " << candidateNumber << ". Majority counter is: " << majorityCounter << " returning false " << endl;
    return false;
}

bool candidate(int array[],int& candidateNumber, int sz)
{
    if(sz == 1)
    {
        candidateNumber = array[0];
        
        return true;
    }
    else if(sz == 0)
    {
        return true;
    }
    
    int tempArraySize = 0;
    
    for(int i = 0; i < sz; i++)
    {
        if(array[i] == array[i+1])
        {
            tempArraySize++;
            i++;
        }
    }
    
    if(sz % 2 != 0)
    {
        candidateNumber = array[sz-1];
    }
    
    int tempArray[tempArraySize];
    int tempCounter = 0;
    for(int i = 0; i < sz; i++)
    {
        if(array[i] == array[i+1])
        {
            tempArray[tempCounter] = array[i];
            
            cout << tempArray[tempCounter] << ", ";
            tempCounter++;
            i++;
        }
    }
    
    cout << endl;

    return candidate(tempArray, candidateNumber, tempArraySize);
}
