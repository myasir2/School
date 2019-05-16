#pragma once
#include <iostream>
#include <string>
#include <utility>
#include "dlist.h"
using namespace std;

template <class TYPE>
class Table
{
    public:
	Table(){}
	virtual bool update(const string& key, const TYPE& value)=0;
	virtual bool remove(const string& key)=0;
	virtual bool find(const string& key, TYPE& value)=0;
	virtual ~Table(){}
};

template <class TYPE>
class SimpleTable:public Table<TYPE>
{
	struct Record
    {
		TYPE data;
		string key;
        
		Record(const string& key, const TYPE& data)
        {
			this->key=key;
			this->data=data;
		}
	};

	Record** records;   //the table
	int recordsCapacity;           //capacity of the array
	int recordsSize;          //current number of records held
	int search(const string& key);
	void sort();

    public:
    SimpleTable(int maxExpected);
    SimpleTable(const SimpleTable& other);
    SimpleTable(SimpleTable&& other);
    virtual bool update(const string& key, const TYPE& value);
    virtual bool remove(const string& key);
    virtual bool find(const string& key, TYPE& value);
    virtual const SimpleTable& operator=(const SimpleTable& other);
    virtual const SimpleTable& operator=(SimpleTable&& other);
    virtual ~SimpleTable();
};

//returns index of where key is found.
template <class TYPE>
int SimpleTable<TYPE>::search(const string& key){
	int rc=-1;
	for(int i=0;i<recordsSize;i++){
		if(records[i]->key_==key){
			rc=i;
		}
	}
	return rc;
}
//sort the according to key in table
template <class TYPE>
void SimpleTable<TYPE>::sort(){
   int minIdx=0;
   for(int i=0;i<recordsSize;i++){
   		minIdx=i;
     	for(int j=i+1;j<recordsSize;j++){
     		if(records[j]->key_ < records[minIdx]->key_){
     			minIdx=j;
     		}
    	}
    	Record* tmp=records[i];
    	records[i]=records[minIdx];
    	records[minIdx]=tmp;
   }
}

/* none of the code in the function definitions below are correct.  You can replace what you need
*/
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(int maxExpected): Table<TYPE>(){
	records=new Record*[maxExpected];
	recordsCapacity=maxExpected;
	recordsSize=0;
}

template <class TYPE>
SimpleTable<TYPE>::SimpleTable(const SimpleTable<TYPE>& other){
	records=new Record*[other.recordsCapacity];
	recordsCapacity=other.recordsCapacity;
	recordsSize=0;
	for(int i=0;i<other.recordsSize;i++){
		update(other.records[i]->key_,other.records[i]->data_);
	}
}
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(SimpleTable<TYPE>&& other){
	recordsSize=other.recordsSize;
	recordsCapacity=other.recordsCapacity;
	records=other.records;
	other.records=nullptr;
	other.recordsSize=0;
	other.recordsCapacity=0;
}

template <class TYPE>
bool SimpleTable<TYPE>::update(const string& key, const TYPE& value){
	int idx=search(key);
	bool rc=false;
	if(idx==-1){
		if(recordsSize < recordsCapacity){
			records[recordsSize++]=new Record(key,value);
			sort();
			rc=true;
		}
	}
	else{
		rc=true;
		records[idx]->data_=value;
	}
	return rc;
}

template <class TYPE>
bool SimpleTable<TYPE>::remove(const string& key){
	int idx=search(key);
	if(idx!=-1){
		delete records[idx];
		for(int i=idx;i<recordsSize-1;i++){
			records[i]=records[i+1];
		}
		recordsSize--;
		return true;
	}
	else{
		return false;
	}
}

template <class TYPE>
bool SimpleTable<TYPE>::find(const string& key, TYPE& value){
	int idx=search(key);
	if(idx==-1)
		return false;
	else{
		value=records[idx]->data_;
		return true;
	}
}

template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(const SimpleTable<TYPE>& other){
	if(this!=&other){
		if(records){
			int sz=recordsSize;
			for(int i=0;i<sz;i++){
				remove(records[0]->key_);
			}
			delete [] records;
		}
		records=new Record*[other.recordsCapacity];
		recordsCapacity=other.recordsCapacity;
		recordsSize=0;
		for(int i=0;i<other.recordsSize;i++){
			update(other.records[i]->key_,other.records[i]->data_);
		}

	}
	return *this;
}
template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(SimpleTable<TYPE>&& other){
	swap(records,other.records);
	swap(recordsSize,other.recordsSize);
	swap(recordsCapacity,other.recordsCapacity);
	return *this;
}
template <class TYPE>
SimpleTable<TYPE>::~SimpleTable(){
	if(records){
		int sz=recordsSize;
		for(int i=0;i<sz;i++){
			remove(records[0]->key_);
		}
		delete [] records;
	}
}

template <class T>
class ChainingTable : public Table<T>
{
    // Each key-value pair in the HashTable is represented by a struct
    struct Record
    {
        string key;
        T value;
        
        Record(const string &key = "", const T &value = T{})
        {
            this->key = key;
            this->value = value;
        }
        
        bool operator==(const Record &rhs)
        {
            return key == rhs.key;
        }
        
        bool operator!=(const Record &rhs)
        {
            return key != rhs.key;
        }
    };
    
    DList<Record> *records;
    
    int capacity;
    int size;
    
    hash<string> hashedFunction;
    
    // This function takes in a key, computes the hashed index and returns it
    // This function has a constant runtime
    size_t getHashedIndex(const string& key)
    {
        return (hashedFunction(key) % capacity);
    }
    
    // This function will take in a key, value, hashedIndex and insert it into the HashTable, if possible, in the spot specified by the hashedIndex
    // This function has a constant runtime
    bool insert(const string &key, const T& value, size_t hashedIndex)
    {
        if(size + 1 <= capacity)
        {
            Record record(key, value);
            
            records[hashedIndex].push_back(record);
            
            size++;
            
            return true;
        }
        else
        {
            return false;
        }
    }
    
    public:
    ChainingTable(int maxExpected);
    ChainingTable(const ChainingTable& other);
    ChainingTable(ChainingTable&& other);
    
    // This function will return the number of Records in the HashTable
    // This function has a constant runtime
    int numRecords() const
    {
        return size;
    }
    
    // This function will return true if the HashTable is empty else false
    // This function has a constant runtime
    bool isEmpty() const
    {
        return size == 0;
    }
    
    virtual bool update(const string& key, const T& value);
    virtual bool remove(const string& key);
    virtual bool find(const string& key, T& value);
    virtual const ChainingTable& operator=(const ChainingTable& other);
    virtual const ChainingTable& operator=(ChainingTable&& other);
    virtual ~ChainingTable();
    
    // A print function which is not part of the assignment but useful for debugging
    void print() const
    {
        for(int i = 0; i < capacity; i++)
        {
            if(!records[i].empty())
            {
                DList<Record> list = records[i];

                for(auto it = list.begin(); it != list.end(); it++)
                {
                    Record r = *it;

                    cout << r.key << " => " << r.value << endl;
                }
            }
        }
    }
};

// The constructor for the HashTable which will allocate number of elements represented by maxExpected in the HashTable array
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(int maxExpected): Table<TYPE>()
{
    records = new DList<Record>[maxExpected];
    capacity = maxExpected;
    size = 0;
}

// The copy constructor for the HashTable will create a deep copy of the passed in object for the current object
// This function has a linear runtime
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(const ChainingTable<TYPE>& rhs)
{
    records = new DList<Record>[rhs.capacity];
    capacity = rhs.capacity;
    size = rhs.size;

    for(int i = 0; i < capacity; i++)
    {
        if(!rhs.records[i].empty())
        {
            records[i] = rhs.records[i];
        }
    }
}

// The move constructor for the HashTable will make the records array pointer point to the passed in objects records and have the passed in objects records point to nullptr. It also sets the capacy and size of the current object to be the same as the passed in object's
// This function has a constant runtime
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(ChainingTable<TYPE>&& rhs)
{
    records = rhs.records;
    capacity = rhs.capacity;
    size = rhs.size;

    rhs.records = nullptr;
    rhs.capacity = 0;
    rhs.size = 0;
}

// The destructor for the HashTable which will deallocate the records array
template <class TYPE>
ChainingTable<TYPE>::~ChainingTable()
{
    delete [] records;
}

// The = operator overload which will mimic the behaviour of the copy constructor
// This function has a linear runtime
template <class TYPE>
const ChainingTable<TYPE>& ChainingTable<TYPE>::operator=(const ChainingTable<TYPE>& rhs)
{
    if(this != &rhs)
    {
        delete [] records;
        records = new DList<Record>[rhs.capacity];
        capacity = rhs.capacity;
        size = rhs.size;
        
        for(int i = 0; i < capacity; i++)
        {
            if(!rhs.records[i].empty())
            {
                records[i] = rhs.records[i];
            }
        }
    }
    
    return *this;
}

// The = operator overload which will mimic the behaviour of the move constructor
// This function has a constant runtime
template <class TYPE>
const ChainingTable<TYPE>& ChainingTable<TYPE>::operator=(ChainingTable<TYPE>&& rhs)
{
    if(this != &rhs)
    {
        records = rhs.records;
        capacity = rhs.capacity;
        size = rhs.size;

        rhs.records = nullptr;
        rhs.capacity = 0;
        rhs.size = 0;
    }

    return *this;
}

// This function will take in a key, value and attempt to add it in the HashTable should it be possible and if a record doesn't already exist with the same key. If a record is found with the same key, it will update the record's value with the passed in value. It will return true if the record was added/updated else false
// This function has a constant runtime
template <class TYPE>
bool ChainingTable<TYPE>::update(const string& key, const TYPE& value)
{
    size_t hashedIndex = getHashedIndex(key);
    
    if(records[hashedIndex].empty())
    {
        return insert(key, value, hashedIndex);
    }
    else
    {
        DList<Record> *existingList = &records[hashedIndex];
        Record newRecord(key, value);
        Record *existingRecord = &*existingList->search(newRecord);
        
        if(*existingRecord == newRecord)
        {
            existingRecord->value = value;
            return true;
        }
        else
        {
            return insert(key, value, hashedIndex);
        }
    }
}

// This function will take in a key and attempt to remove the record with the specified key if found. It will return true if the record was successfully deleted else false.
// This function has a constant runtime
template <class TYPE>
bool ChainingTable<TYPE>::remove(const string& key)
{
    size_t hashedIndex = getHashedIndex(key);

    if(!records[hashedIndex].empty())
    {
        bool recordDeleted = false;

        DList<Record> *removalList = &records[hashedIndex];

        for(auto it = removalList->begin(); it != removalList->end() && !recordDeleted; it++)
        {
            Record *record = &*it;

            if(record->key == key)
            {
                removalList->erase(it);
                size--;
                recordDeleted = true;
            }
        }

        return recordDeleted;
    }
    else
    {
        return false;
    }
}

// This function will take in a key, a reference to a value and will attempt to find the record with the key. If a key is found, then the reference value variable is assigned to have the same value as the found record and true is returned; else false is returned
// This function has a constant runtime
template <class TYPE>
bool ChainingTable<TYPE>::find(const string& key, TYPE& value)
{
    size_t hashedIndex = getHashedIndex(key);

    if(!records[hashedIndex].empty())
    {
        bool keyFound = false;
        
        Record tempRecord(key, value);
        DList<Record> *existingList = &records[hashedIndex];
        Record *existingRecord = &*existingList->search(tempRecord);
        
        if(*existingRecord == tempRecord)
        {
            keyFound = true;
            value = existingRecord->value;
        }

        return keyFound;
    }
    else
    {
        return false;
    }
}

