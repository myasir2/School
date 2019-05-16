//
//  AVL.hpp
//  Binary Search Tree
//
//  Created by Yasir Merchant on 2018-08-01.
//  Copyright © 2018 Yasir Merchant. All rights reserved.
//

#ifndef AVL_hpp
#define AVL_hpp
#endif /* AVL_hpp */

#include <stdio.h>
#include <iostream>

template <class T>
class AVL
{
    struct Node
    {
        T data;
        Node *left;
        Node *right;
        int height;
        
        Node(const T &data, Node *right = nullptr, Node *left = nullptr)
        {
            this->data = data;
            this->right = right;
            this->left = left;
            this->height = 1;
        }
        
        int leftHeight() const
        {
            return left ? left->height : 0;
        }
        
        int rightHeight() const
        {
            return right ? right->height : 0;
        }
        
        int nodeBalance() const
        {
            return rightHeight() - leftHeight();
        }
        
        void updateHeight()
        {
            if(rightHeight() > leftHeight())
            {
                height = rightHeight() + 1;
            }
            else
            {
                height = leftHeight() + 1;
            }
        }
    };
    
    Node *root;
    
    void insert(const T &data, Node*& subRoot)
    {
        if(subRoot == nullptr)
        {
            subRoot = new Node(data);
        }
        else
        {
            if(data < subRoot->data)
            {
                insert(data, subRoot->left);
            }
            else
            {
                insert(data, subRoot->right);
            }
            
            if(subRoot->nodeBalance() > 1)
            {
                if(subRoot->right->nodeBalance() == 1)
                {
                    leftRotate(subRoot);
                    
                    subRoot->left->updateHeight();
                }
                else
                {
                    rightRotate(subRoot->right);
                    leftRotate(subRoot);
                    
                    subRoot->left->updateHeight();
                    subRoot->right->updateHeight();
                }
            }
            else if(subRoot->nodeBalance() < -1)
            {
                if(subRoot->left->nodeBalance() == -1)
                {
                    rightRotate(subRoot);
                    
                    subRoot->right->updateHeight();
                }
                else
                {
                    leftRotate(subRoot->left);
                    rightRotate(subRoot);
                    
                    subRoot->left->updateHeight();
                    subRoot->right->updateHeight();
                }
            }
            
            subRoot->updateHeight();
        }
    }
    
    void leftRotate(Node *&A)
    {
        Node *B = A->right;
        Node *Y = B->left;
        
        A->right = Y;
        B->left = A;
        
        A=B;
    }
    
    void rightRotate(Node *&A)
    {
        Node *B = A->left;
        Node *Y = B->right;
        
        A->left = Y;
        B->right = A;
        
        A=B;
    }
    
    void printPreOrder(Node *subroot) const
    {
        if(subroot != nullptr)
        {
            std::cout << subroot->data << " ";
            printPreOrder(subroot->left);
            printPreOrder(subroot->right);
        }
    }
    
    void printInOrder(Node *subroot) const
    {
        if(subroot != nullptr)
        {
            printInOrder(subroot->left);
            std::cout << subroot->data << " ";
            printInOrder(subroot->right);
        }
    }
    
    void destroy(Node *subroot)
    {
        if(subroot)
        {
            destroy(subroot->left);
            destroy(subroot->right);
            delete subroot;
        }
    }
    
public:
    AVL()
    {
        root = nullptr;
    }
    
    void insert(const T &data)
    {
        insert(data, root);
    }
    
    void remove(const T &data);
    
    bool exists(const T &data) const
    {
        Node *current = root;
        
        while(current && current->data != data)
        {
            if(data < current->data)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
        
        return current;
    }
    
    void print() const
    {
        //        Queue<Node*> theNodes;
        //
        //        if(root)
        //        {
        //           theNodes.enqueue = root;
        //
        //            while(!theNodes.isEmpty())
        //            {
        //                Node *current = theNodes.front();
        //                theNodes.dequeue();
        //
        //                std::cout << current->data << " ";
        //
        //                if(current->left)
        //                    theNodes.enqueue(current->left);
        //
        //                if(current->right)
        //                    theNodes.enqueue(current->right);
        //            }
        //        }
    }
    
    void printPreOrder() const
    {
        printPreOrder(root);
        
        std::cout << std::endl;
    }
    
    void printInOrder() const
    {
        printInOrder(root);
        
        std::cout << std::endl;
    }
    
    ~AVL()
    {
        destroy(root);
    }
    
};
