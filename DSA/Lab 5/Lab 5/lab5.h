#include <iostream>
#include <iomanip>
using namespace std;

template <class T>
class Queue{
	T* theQueue_;
	int capacity_;
	int used_;
	int front_;
	int back_;
	void grow(){
		T* tmp=new T[capacity_*2];
		int j;
		for(int i=0,j=front_;i<used_;i++,j=(j+1)%capacity_){
			tmp[i]=theQueue_[j];
		}
		delete [] theQueue_;
		theQueue_=tmp;
		capacity_=capacity_*2;
		front_=0;
		back_=used_;
	}
public:
	Queue(){
		theQueue_=new T[50];
		capacity_=50;
		used_=0;
		front_=0;
		back_=0;
	}
	void enqueue(const T& data){
		if(used_==capacity_){
			grow();
		}
		theQueue_[back_]=data;
		back_=(back_+1)%capacity_;
		used_++;
	}
	void dequeue(){
		if(!isEmpty()){
			used_--;
			front_=(front_+1)%capacity_;
		}
	}
	T front() const{
		if(!isEmpty()){
			return theQueue_[front_];
		}
		return T{};

	}
	bool isEmpty() const{
		return used_==0;
	}
	~Queue(){
		delete [] theQueue_;
	}	
};

template <class T>
class BST{
	struct Node{
		T data_;
		Node* left_;
		Node* right_;
		Node(const T& data,Node* lt=nullptr,Node* rt=nullptr){
			data_=data;
			left_=lt;
			right_=rt;
		}
	};
	Node* root_;



	//insert data into subtree with root subroot
	void insert(const T& data, Node*& subroot){
		if(subroot == nullptr){
			subroot=new Node(data);
		}
		else{
			if(data < subroot->data_){
				insert(data,subroot->left_);
			}
			else{
				insert(data,subroot->right_);
			}
		}
	}
	void printPreOrder(Node* subroot)const{
		if(subroot){
			std::cout << subroot->data_ << " ";		
			printPreOrder(subroot->left_);
			printPreOrder(subroot->right_);
		}
	}
	void printInOrder(Node* subroot)const{
		if(subroot)
        {
			printInOrder(subroot->left_);
			std::cout << subroot->data_ << " ";
			printInOrder(subroot->right_);
		}
	}
    
    void printBetween(const int min, const int max, Node *subroot) const
    {
        if(subroot)
        {
            printBetween(min, max, subroot->left_);
            
            if(subroot->data_ >= min && subroot->data_ <= max)
            {
                std::cout << subroot->data_ << " " ;
            }
            
            printBetween(min, max, subroot->right_);
        }
    }
    
    int height(Node *subroot) const
    {
        if(!subroot)
        {
            return -1;
        }
        
        int leftHeight = height(subroot->left_);
        int rightHeight = height(subroot->right_);
        
        if(leftHeight > rightHeight)
        {
            return leftHeight + 1;
        }
        else
        {
            return rightHeight + 1;
        }
    }
    
	void destroy(Node* subroot){
		if(subroot){
			destroy(subroot->left_);
			destroy(subroot->right_);
			delete subroot;
		}
	}
	bool isSame(const Node* left, const Node* right) const{
		bool rc;
		if(!left && !right){
			rc=true;
		}
		else if(left && right){
			if(left->data_ == right->data_){
				rc=isSame(left->left_,right->left_) && isSame(left->right_,right->right_);
			}
			else{
				rc=false;
			}
		}
		else{
			rc=false;
		}
		return rc;
	}
	/*used by print() to print all nodes at same level*/
	void printLine(Node* data[],int numNodes,int width) const{
		int half=width/2;
		int firsthalf=width%2?half+1:half;

		if(numNodes > 1){
			for(int i=0;i<numNodes;i++){
				if(i%2==0){
					if(data[i]){
						std::cout << std::right <<std::setfill(' ') << std::setw(firsthalf)<< "-";
						std::cout << std::left << std::setfill('-') << std::setw(half) << "-";
					}
					else{
						std::cout << std::right <<std::setfill(' ') << std::setw(firsthalf)<< " ";
						std::cout << std::left << std::setfill(' ') << std::setw(half) << " ";
					}
				}
				else{
					if(data[i]){
						std::cout << std::right << std::setfill('-') << std::setw(firsthalf) << "-";
						std::cout << std::left <<std::setfill(' ') << std::setw(half)<<"-";
					}
					else{
						std::cout << std::right << std::setfill(' ') << std::setw(firsthalf) << " ";
						std::cout << std::left <<std::setfill(' ') << std::setw(half)<<" ";
					}
				}
			}
			std::cout << std::endl;
		}
		for(int i=0;i<numNodes;i++){
			if(data[i]){
				if(i%2==0){
					std::cout << std::right << std::setw(firsthalf) << "|";
					std::cout << std::left <<std::setfill(' ') << std::setw(half)<<" ";
				}
				else{
					std::cout << std::right << std::setfill(' ') << std::setw(firsthalf) << " ";
					std::cout << std::left <<std::setfill(' ') << std::setw(half)<< "|";				
				}
			}
			else{
				std::cout << std::left <<std::setfill(' ') << std::setw(width)<<" ";			
			}
		}
		std::cout << std::endl;		
		for(int i=0;i<numNodes;i++){
			if(data[i]){
				if(i%2==0){
					std::cout << std::right << std::setw(firsthalf) << data[i]->data_;
					std::cout << std::left <<std::setfill(' ') << std::setw(half)<<" ";
				}
				else{
					std::cout << std::right << std::setfill(' ') << std::setw(firsthalf) << " ";
					std::cout << std::left <<std::setfill(' ') << std::setw(half)<< data[i]->data_;				
				}
			}
			else{
				std::cout << std::left <<std::setfill(' ') << std::setw(width)<<" ";			
			}
		}
		std::cout << std::endl;

	}
    
    void remove(const T &data, Node *&subroot)
    {
        if(data == subroot->data_)
        {
            Node *rm = subroot;
            
            if(subroot->right_ != nullptr && subroot->left_ != nullptr)
            {
                Node *successor = detachSmallest(subroot->right_);
                successor->left_ = rm->left_;
                successor->right_ = rm->right_;
                
                subroot = successor;
                
                delete rm;
            }
            else if(subroot->right_ != nullptr)
            {
                subroot = rm->right_;
                
                delete rm;
            }
            else if(subroot->left_ != nullptr)
            {
                subroot = rm->left_;
            }
            else
            {
                subroot = nullptr;
                
                delete rm;
            }
        }
        else if(data < subroot->data_)
        {
            remove(data, subroot->left_);
        }
        else if(data > subroot->data_)
        {
            remove(data, subroot->right_);
        }
    }
    
    Node* detachSmallest(Node *&subroot)
    {
        if(subroot->left_ == nullptr)
        {
            Node *successor = subroot;
            subroot = successor->right_;
            
            return successor;
        }
        else
        {
            return detachSmallest(subroot->left_);
        }
    }
    
    int min(const int subrootValue, Node *subroot)
    {
        if(subrootValue == subroot->data_)
        {
            return minOfSubtree(subroot);
        }
        else if(subrootValue > subroot->data_)
        {
            return min(subrootValue, subroot->right_);
        }
        else if(subrootValue < subroot->data_)
        {
            return min(subrootValue, subroot->left_);
        }
        else
        {
            return 0;
        }
    }
    
    int minOfSubtree(Node *subtreeRoot)
    {
        if(!subtreeRoot->left_)
        {
            return subtreeRoot->data_;
        }
        else
        {
            return minOfSubtree(subtreeRoot->left_);
        }
    }
    
    int pathLen(const int subrootValue, Node *subroot)
    {
        int pathLen = 1;
        
        Node *current = subroot;
        
        std::cout << "Current left is: " << current->left_->data_ << endl;

        
        while(current->data_ != subrootValue)
        {
            if(subrootValue > current->data_)
            {
                current = current->right_;
            }
            else if(subrootValue < current->data_)
            {
                current = current->left_;
            }
            
            pathLen++;
        }
        
        return pathLen;
    }
    
public:
	BST(){
		root_=nullptr;
	}
	void printPreOrder() const{
		printPreOrder(root_);
		std::cout << std::endl;
	}
	void printInOrder() const{
		printInOrder(root_);
		std::cout << std::endl;
	}
    
    void printBetween(const int min, const int max)
    {
        printBetween(min, max, root_);
        std::cout << std::endl;
    }
    
    int height() const
    {
        return height(root_);
    }
    
    int min(const int v)
    {
        return min(v, root_);
    }
    
    int pathLen(const int v)
    {
        return pathLen(v, root_);
    }
    
	void insertRecursive(const T& data){
		insert(data,root_);
	}

	void insert(const T& data){
		if(root_==nullptr){
			root_=new Node(data);
		}
		else{

			Node* curr=root_;
			while(curr != nullptr){
				if(data < curr->data_){
					//go left
					if(curr->left_){
						curr=curr->left_;
					}
					else{
						curr->left_=new Node(data);
						curr=nullptr;
					}
				}	
				else{
					//go right
					if(curr->right_){
						curr=curr->right_;
					}
					else{
						curr->right_=new Node(data);
						curr=nullptr;
					}
				}
			}

		}

	}
    
	void remove(const T& data)
    {
        remove(data, root_);
	}
    
	bool exists(const T& data) const{
		bool rc=false;
		Node* curr=root_;
		while(curr && curr->data_ != data){
			if(data < curr->data_){
				curr=curr->left_;
			}
			else{
				curr=curr->right_;
			}
		}

		return (bool)curr;
	}
	bool operator==(const BST& rhs) const{
		return isSame(root_,rhs.root_);
	}
	void print() const{
		struct Output{
			Node* node_;
			int lvl_;
			int position_;
			Output(Node* n=nullptr,int l=0, int p=0){
				node_=n;
				lvl_=l;
				position_=p;
			}
			void set(Node* n=nullptr,int l=0, int p=0){
				node_=n;
				lvl_=l;
				position_=p;
			}
		};
		Queue<Output> theNodes;
		Node* line[16];
		if(root_){
			for(int i=0;i<16;i++){
				line[i]=nullptr;
			}
			theNodes.enqueue(Output(root_,0,0));
			int currline=0;
			int width=80;
			int numInLine=1;
			while(theNodes.isEmpty()==false){
				Output curr=theNodes.front();
				if(curr.node_->left_)
					theNodes.enqueue(Output(curr.node_->left_,curr.lvl_+1,curr.position_*2));
				if(curr.node_->right_)
					theNodes.enqueue(Output(curr.node_->right_,curr.lvl_+1,curr.position_*2+1));
				theNodes.dequeue();


				if(curr.lvl_>currline){
					printLine(line,numInLine,width);
					width=width/2;
					numInLine=numInLine*2;
					for(int i=0;i<16;i++){
						line[i]=nullptr;
					}
					currline++;

				}
				line[curr.position_]=curr.node_;
			}
			printLine(line,numInLine,width);
			std::cout << std::endl;

		}
		else{
			std::cout << "tree is empty" << std::endl;
		}
	}
	~BST(){
		destroy(root_);
	}
};

