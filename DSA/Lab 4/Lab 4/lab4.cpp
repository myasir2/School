#include "stack.h"
#include <string>
using namespace std;gl

bool bracketCheck(const string &stringToCheck)
{
    Stack<char> stack;
    
    for(int i = 0; i < stringToCheck.length(); i++)
    {
        if(stringToCheck[i] == '(' || stringToCheck[i] == '{' || stringToCheck[i] == '[')
        {
            stack.push_front(stringToCheck[i]);
        }
        else if(stringToCheck[i] == ')' || stringToCheck[i] == '}' || stringToCheck[i] == ']')
        {
            if(stack.empty())
            {
                return false;
            }
            
            if(stringToCheck[i] == ')')
            {
                if(stack.top() == '(')
                {
                    stack.pop_front();
                }
            }
            else if(stringToCheck[i] == '}')
            {
                if(stack.top() == '{')
                {
                    stack.pop_front();
                }
            }
            else if(stringToCheck[i] == ']')
            {
                if(stack.top() == '[')
                {
                    stack.pop_front();
                }
            }
        }
    }
    
    return stack.size() == 0;
}
