#include <iostream>
#include "a1.h"
using namespace std;

bool isPalindrome(const char *s, int startIndex, int endIndex)
{
    if(startIndex >= endIndex)
    {
        return true;
    }
    
    if(s[startIndex] == s[endIndex] && isPalindrome(s, startIndex + 1, endIndex -1))
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    const char *palindrome = "racecar";
    
    bool correct = isPalindrome(palindrome, 0, strlen(palindrome)-1);
    
    cout << correct << endl;
    
    return 0;
    
    //    unsigned int counter = strlen(palindrome) - 1;
    //    for(unsigned int i = 0; i < strlen(palindrome); i++)
    //    {
    //        if(palindrome[i] == palindrome[counter])
    //        {
    //            isPalindrome = true;
    //        }
    //        else
    //        {
    //            isPalindrome = false;
    //        }
    //
    //        counter--;
    //    }
    //
    //    cout << isPalindrome << endl;
    //
    
}

