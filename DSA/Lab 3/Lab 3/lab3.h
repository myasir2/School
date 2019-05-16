#include <iostream>

template <typename T>
class DList{
	struct Node{
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& data=T{},Node* next=nullptr, Node* prev=nullptr){
			data_=data;
			next_=next;
			prev_=prev;
		}
	};
	Node* front_;
	Node* back_;
public:
	DList(){
		front_=nullptr;
		back_=nullptr;
	}
	void push_front(const T& data);
	void push_back(const T& data);
	void pop_front();
	void pop_back();
	void print() const;
	void reversePrint() const;
	~DList();
};


template <typename T>
void DList<T>::push_front(const T& data)
{
	Node *node = new Node(data);

	if(front_ == nullptr)
	{
		back_ = node;
	}
	else
	{
		node->next_ = front_;
		front_->prev_ = node;
	}
	
	front_ = node;
}

template <typename T>
void DList<T>::push_back(const T& data)
{
	Node *node = new Node(data);
	
	if(front_ == nullptr)
	{
		front_ = node;
	}
	else
	{
		node->prev_ = back_;
		back_->next_ = node;
	}
	
	back_ = node;
}

template <typename T>
void DList<T>::pop_front()
{
	if(front_ != nullptr)
	{
		Node *temp = front_;
		
		if(front_ != back_)
		{
			temp->next_->prev_ = nullptr;
		}
		else
		{
			back_ = nullptr;
		}

		front_ = temp->next_;

		delete temp;
	}
}

template <typename T>
void DList<T>::pop_back()
{
	if(front_ != nullptr)
	{
		Node *temp = back_;

		if(back_ != front_)
		{
			temp->prev_->next_ = nullptr;
		}
		else
		{
			front_ = nullptr;
		}

		back_ = temp->prev_;

		delete temp;
	}
}

template <typename T>
void DList<T>::print() const{
	Node* curr=front_;
	while(curr!=nullptr){
		std::cout << curr->data_ << " ";
		curr=curr->next_;
	}
	std::cout << std::endl;
}
template <typename T>
void DList<T>::reversePrint() const{
	Node* curr=back_;
	while(curr!=nullptr){
		std::cout << curr->data_ << " ";
		curr=curr->prev_;
	}
	std::cout << std::endl;
}
template <typename T>
DList<T>::~DList(){
	Node* curr=front_;
	while(curr){
		Node* rm=curr;
		curr=curr->next_;
		delete rm;
	}
}
template <typename T>
class Sentinel{
	struct Node{
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& data=T{},Node* next=nullptr, Node* prev=nullptr){
			data_=data;
			next_=next;
			prev_=prev;
		}
	};
	Node* front_;
	Node* back_;
public:
	Sentinel(){
		front_=new Node();
		back_=new Node();
		front_->next_=back_;
		back_->prev_=front_;
	}
	void push_front(const T& data);
	void push_back(const T& data);
	void pop_front();
	void pop_back();
	void print() const;
	void reversePrint() const;
	~Sentinel();
};


template <typename T>
void Sentinel<T>::push_front(const T& data)
{
    Node *node = new Node(data);
    
    node->next_ = front_->next_;
    node->prev_ = front_;
    
    front_->next_->prev_ = node;
    front_->next_ = node;
}

template <typename T>
void Sentinel<T>::push_back(const T& data)
{
    Node *node = new Node(data);
    
    node->prev_ = back_->prev_;
    node->next_ = back_;
    
    back_->prev_->next_ = node;
    back_->prev_ = node;
}

template <typename T>
void Sentinel<T>::pop_front()
{
    Node *currentNode = front_->next_;
    
    if(currentNode != back_)
    {
        currentNode->next_->prev_ = front_;
        front_->next_ = currentNode->next_;
    }
}

template <typename T>
void Sentinel<T>::pop_back()
{
    
}

template <typename T>
void Sentinel<T>::print() const{
	Node* curr=front_->next_;
	while(curr!=back_){
		std::cout << curr->data_ << " ";
		curr=curr->next_;
	}
	std::cout << std::endl;
}
template <typename T>
void Sentinel<T>::reversePrint() const{
	Node* curr=back_->prev_;
	while(curr!=front_){
		std::cout << curr->data_ << " ";
		curr=curr->prev_;
	}
	std::cout << std::endl;
}
template <typename T>
Sentinel<T>::~Sentinel(){
	Node* curr=front_;
	while(curr){
		Node* rm=curr;
		curr=curr->next_;
		delete rm;
	}
}
