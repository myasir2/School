template <typename T>
class Stack
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
    
    // default constructor Stack that will initialize first and back Node pointers and set them to point to each other. It will also initialize the
    // number of nodes to 0
    // this function has a constant runtime
    Stack()
    {
        front = new Node();
        back = new Node;
        front->next = back;
        back->prev = front;
        
        numberOfNodes = 0;
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
            currentNode->next->prev = front;
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
    
    T& top()const
    {
        return front->next->data;
    }
    
    // the destructor of the class that removes all nodes in the list
    // this function has a constant runtime
    ~Stack()
    {
        Node *current = front;
        
        while(current)
        {
            Node *nodeToRemove = current;
            current = current->next;
            delete nodeToRemove;
        }
    }
};
