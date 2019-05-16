bool candidate(int array[],int& candidate, int sz);
bool majorityElement(const int arr[], int& majority, int sz);

// this function attempt to find the majority element in a given array by copying the array into a temp storage, finding a candidate, and searching
// the array if the array containts n/2+1 candidates which will return true as the candidate is the majority element
// this function has a constant runtime
bool majorityElement(const int arr[], int& majority, int sz)
{
    int *copyArray = new int[sz];
    int candidateNumber = 0;
    int copySize = sz;
    bool majorityElementFound = false;
    
    for(int i = 0; i < sz; i++)
    {
        copyArray[i] = arr[i];
    }
    
    candidate(copyArray, candidateNumber, copySize);
    
    int majorityCounter = 0;
    for(int i = 0; i < sz; i++)
    {
        if(arr[i] == candidateNumber)
        {
            majorityCounter++;
        }
        
        if(majorityCounter >= (sz/2)+1)
        {
            majority = candidateNumber;
            majorityElementFound = true;
            break;
        }
    }

    delete [] copyArray;
    
    return majorityElementFound;
}

// this function is a recursive function that will take an array, and look at the elements in pairs if they're equal. If the pairs are equal, one of
// them is a possible candidate which gets added to a temparray and passed to the function itself for further filtering of the candidate
// this function has a linear runtime
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
    
    for(int i = 0; i < sz; i = i+2)
    {
        if(array[i] == array[i+1])
        {
            tempArraySize++;
        }
    }
    
    if(sz % 2 != 0)
    {
        candidateNumber = array[sz-1];
    }
    
    int tempArray[tempArraySize];
    int tempCounter = 0;
    for(int i = 0; i < sz; i = i+2)
    {
        if(array[i] == array[i+1])
        {
            tempArray[tempCounter] = array[i];
            tempCounter++;
        }
    }
    
    return candidate(tempArray, candidateNumber, tempArraySize);
}
