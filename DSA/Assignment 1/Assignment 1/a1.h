template <typename T>
class DList
{
    private:
	struct Node
    {
        T data;
        Node *next;
        Node *prev;
        
		Node(const T& data=T{}, Node* next=nullptr, Node* prev=nullptr)
        {
            this->data = data;
            this->next = next;
            this->prev = prev;
        }
	};
    
    Node *front;
    Node *back;
    
    int numberOfNodes;
    
    public:
    
    // the const_iterator stores a read-only iterator
    class const_iterator
    {
        // setting const_iterator's friend class to DList so access to private variables outside the iterator classes is possible
        friend class DList;
        
        protected:
        Node *currentNode;

        public:
        
        // default constructor to initialize currentNode to nullptr
        // this function has a constant runtime
        const_iterator()
        {
            currentNode = nullptr;
        }
    
        // overloaded constructor to set the currentNode to point to node from parameter
        // this function has a constant runtime
        const_iterator(Node *newNode)
        {
            currentNode = newNode;
        }
    
        // overloaded == operator that will return true if the currentNode and rhs's current node are equal
        // this function has a constant runtime
        bool operator==(const_iterator rhs)
        {
            return (this->currentNode == rhs.currentNode);
        }
    
        // overloaded != operator that will return true if the currentNode and rhs's current node are not equal
        // this function has a constant runtime
        bool operator!=(const_iterator rhs)
        {
            return (this->currentNode != rhs.currentNode);
        }

        // overloaded prefix increment operator that will set the currentNode to point to next and return the currentNode
        // this function has a constant runtime
        const_iterator operator++()
        {
            currentNode = currentNode->next;
            return currentNode;
        }
    
        // overloaded postfix increment operator that will set the currentNode to point to next and return the old
        // this function has a constant runtime
        const_iterator operator++(int)
        {
            const_iterator old = *this;
            currentNode = currentNode->next;
            return old;
        }
    
        // overloaded prefix decrement operator that will set the currentNode to point to prev and return the currentNode
        // this function has a constant runtime
        const_iterator operator--()
        {
            currentNode = currentNode->prev;
            return currentNode;
        }
    
        // overloaded postfix decrement operator that will set the currentNode to point to prev and return the old
        // this function has a constant runtime
        const_iterator operator--(int)
        {
            const_iterator old = *this;
            currentNode = currentNode->prev;
            return old;
        }
        
        // overloaded * operator to return the data stored in currentNode
        // this function has a constant runtime
        const T& operator*() const
        {
            return currentNode->data;
        }
    };

    class iterator : public const_iterator
    {
        public:
        
        // default constructor that will call the base constructor and initialize the currentNode to nullptr
        // this function has a constant runtime
        iterator() : const_iterator()
        {
            const_iterator::currentNode = nullptr;
        }
    
        // overloaded constructor that will call the base overloaded constructor and set the currentNode to point to node from parameter
        // this function has a constant runtime
        iterator(Node *newNode) : const_iterator(newNode)
        {
            const_iterator::currentNode = newNode;
        }
    
        // overloaded * operator to return the data stored in currentNode
        // this function has a constant runtime
        T& operator*()
        {
            return const_iterator::currentNode->data;
        }
    
        // overloaded prefix increment operator that will set the currentNode to point to next and return the currentNode
        // this function has a constant runtime
        iterator operator++()
        {
            const_iterator::currentNode = const_iterator::currentNode->next;
            return const_iterator::currentNode;
        }

        // overloaded postfix increment operator that will set the currentNode to point to next and return the old
        // this function has a constant runtime
        iterator operator++(int)
        {
            iterator old = *this;
            const_iterator::currentNode = const_iterator::currentNode->next;
            return old;
        }
    
        // overloaded prefix decrement operator that will set the currentNode to point to prev and return the currentNode
        // this function has a constant runtime
        iterator operator--()
        {
            const_iterator::currentNode = const_iterator::currentNode->prev;
            return const_iterator::currentNode;
        }

        // overloaded postfix decrement operator that will set the currentNode to point to prev and return the old
        // this function has a constant runtime
        iterator operator--(int)
        {
            iterator old = *this;
            const_iterator::currentNode = const_iterator::currentNode->prev;
            return old;
        }
    };

    // default constructor DList that will initialize first and back Node pointers and set them to point to each other. It will also initialize the
    // number of nodes to 0
    // this function has a constant runtime
    DList()
    {
        front = new Node();
        back = new Node;
        front->next = back;
        back->prev = front;
        
        numberOfNodes = 0;
    }

    // this function will initialize an iterator class that points to front->next node and return it
    // this function has a constant runtime
    iterator begin()
    {
        return iterator(front->next);
    }

    // this function will initialize an iterator class that points to back node and return it
    // this function has a constant runtime
    iterator end()
    {
        return iterator(back);
    }

    // this function will initialize a const_iterator class that points to front->next node and return it
    // this function has a constant runtime
    const_iterator begin() const
    {
        return const_iterator(front->next);
    }

    // this function will initialize a const_iterator class that points to back node and return it
    // this function has a constant runtime
    const_iterator end() const
    {
        return const_iterator(back);
    }

    // this function creates a new Node with the data recieved, and pushes it to the front of the list. It also increments numberOfNodes by 1
    // this function has a constant runtime
    void push_front(const T& data)
    {
        Node *node = new Node(data);
        
        node->next = front->next;
        node->prev = front;
        
        front->next->prev = node;
        front->next = node;
        
        numberOfNodes++;
    }

    // this function creates a new Node with the data recieved, and pushes it to the back of the list. It also increments numberOfNodes by 1
    // this function has a constant runtime
    void push_back(const T& data)
    {
        std::cout << "pushing" << endl;
        Node *node = new Node(data);
        
        node->prev = back->prev;
        node->next = back;
        
        back->prev->next = node;
        back->prev = node;
        
        numberOfNodes++;
    }

    // this function deletes a node from the front of the list and decrements the numberOfNodes by 1
    // this function has a constant runtime
    void pop_front()
    {
        Node *currentNode = front->next;
        
        if(currentNode != back)
        {
            currentNode->next->prev_ = front;
            front->next = currentNode->next;
            
            numberOfNodes--;
        }
        
        delete currentNode;
    }

    // this function deletes a node from the back of the list and decrements the numberOfNodes by 1
    // this function has a constant runtime
    void pop_back()
    {
        Node *currentNode = back->prev;
        
        if(currentNode != front)
        {
            currentNode->prev->next = back;
            back->prev = currentNode->prev;
            
            numberOfNodes--;
        }
        
        delete currentNode;
    }

    // this function creates a new Node with the data recieved, pushes it before the node referred by the recieved iterator param,
    // and increments the numberOfNodes by 1
    // this function has a constant runtime
    iterator insert(iterator loc, const T& data)
    {
        Node *newNode = new Node(data);
        Node *oldNode = loc.currentNode;
        
        newNode->next = oldNode;
        oldNode->prev->next = newNode;
        
        newNode->prev = oldNode->prev;
        oldNode->prev = newNode;
        
        numberOfNodes++;
        
        return newNode;
    }

    // this function deletes the node referred by recieved iterator param and decrements the numberOfNodes by 1.
    // this function has a constant runtime
    void erase(iterator it)
    {
        Node *nodeToDelete = it.currentNode;
        
        nodeToDelete->prev->next = nodeToDelete->next;
        nodeToDelete->next->prev = nodeToDelete->prev;
        
        delete it.currentNode;
        
        numberOfNodes--;
    }
    
    // this function recieves a starting iterator and ending iterator, deletes all nodes in between with the starting one being inclusive.
    // it also decrements the numberOfNodes by 1. t
    // this function has a linear runtime
    void erase(iterator start, iterator end)
    {
        Node *newFirstNode = start.currentNode->prev;
        Node *newLastNode = end.currentNode;
        
        newFirstNode->next = newLastNode;
        newLastNode->prev = newFirstNode;
        
        iterator it;
        
        for(it = start; it != end; it++)
        {
            delete it.currentNode;
            
            numberOfNodes--;
        }
    }
    
    // this function finds the first node in the list that has the same data as the recieved parameter and returns the iterator to that node
    // this funtion has a linear runtime
    iterator search(const T& data)
    {
        iterator it = begin();
        
        while(it.currentNode != back)
        {
            if(it.currentNode->data == data)
            {
                break;
            }
            
            it++;
        }
        
        return it;
    }
    
    // this function finds the first node in the list that has the same data as the recieved parameter and returns the const iterator to that node
    // this function has a linear runtime
    const_iterator search(const T& data) const
    {
        const_iterator it = begin();
        
        while(it.currentNode != back)
        {
            if(it.currentNode->data == data)
            {
                break;
            }
            
            it++;
        }
        
        return it;
    }
    
    // this function returns true if the list is empty by checking if the front sentinel is pointing to the back sentinel
    // this function has a constant runtime
    bool empty() const
    {
        if(front->next == back)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    // this function returns the number of nodes in the list
    // this function has a constant runtime
    int size() const
    {
        return numberOfNodes;
    }

    // the destructor of the class that removes all nodes in the list
    // this function has a constant runtime
    ~DList()
    {
        std::cout << "destructor called" << endl;
        
        Node *current = front;
        
        while(current)
        {
            Node *nodeToRemove = current;
            current = current->next;
            delete nodeToRemove;
        }
    }

    // the copy constructor of the list that will copy all the data recieved from the param DList and copy it to the current object
    // this function has a linear runtime
    DList(const DList &rhs)
    {
        front = new Node();
        back = new Node();
        front->next = back;
        back->prev = front;
        
        const_iterator oldListIterator;
        iterator newListIterator;
        
        for(newListIterator = begin(), oldListIterator = rhs.begin(); oldListIterator != rhs.end(); oldListIterator++)
        {
            insert(newListIterator, oldListIterator.currentNode->data);
        }
    }
    
    // the assignment operator for the copy constructor will remove all the data for the current object and copy over the data from the
    // recieved list param to the current object
    // this function has a linear runtime
    DList& operator=(const DList &rhs)
    {
        if(this != &rhs)
        {
            const_iterator oldListIterator;
            iterator newListIterator;
            
            erase(begin(), end());
    
            for(newListIterator = begin(), oldListIterator = rhs.begin(); oldListIterator != rhs.end(); oldListIterator++)
            {
                insert(newListIterator, oldListIterator.currentNode->data);
            }
        }
        
        return *this;
    }
    
    // move constructor of the list will make front and back pointers of the current object to point to recieved list's front and back nodes
    // this function has a constant runtime
    DList(DList &&rhs)
    {
        front = new Node();
        back = new Node();
        front = rhs.front;
        back = rhs.back;
        numberOfNodes = rhs.size();
        
        rhs.front = new Node();
        rhs.back = new Node();
        rhs.front->next = rhs.back;
        rhs.back->prev = rhs.front;
        rhs.numberOfNodes = 0;
    }
    
    // move assignment operator of the list that will swap the front and back pointers of the current list and the recieved list param
    // this function has a constant runtime
    DList& operator=(DList &&rhs)
    {
        if(this != &rhs)
        {
            Node *tempFront = front;
            Node *tempBack = back;
            
            front = rhs.front;
            back = rhs.back;
            numberOfNodes = rhs.numberOfNodes;
            
            rhs.front = tempFront;
            rhs.back = tempBack;
        }
        
        return *this;
    }
};
