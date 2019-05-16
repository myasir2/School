//
//  BST.hpp
//  Binary Search Tree
//
//  Created by Yasir Merchant on 2018-07-27.
//  Copyright © 2018 Yasir Merchant. All rights reserved.
//

#ifndef BST_hpp
#define BST_hpp

#include <stdio.h>
#include <iostream>

template <class T>
class BST
{
    struct Node
    {
        T data;
        Node *left;
        Node *right;
        Node(const T &data, Node *right = nullptr, Node *left = nullptr)
        {
            this->data = data;
            this->right = right;
            this->left = left;
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
        }
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
    BST()
    {
        root = nullptr;
    }
    
    void insert(const T &data)
    {
        if(root == nullptr)
        {
            root = new Node(data);
        }
        else
        {
//            Node *previous = nullptr;
//            Node *current = root;
//
//            while(current != nullptr)
//            {
//                previous = current;
//
//                if(data < current->data)
//                {
//                    current = current->left;
//                }
//                else
//                {
//                    current = current->right;
//                }
//
//                if(data > current->data)
//                {
//                    current = current->right;
//                }
//                else
//                {
//                    current = current->left;
//                }
//            }
//
//            if(data < previous->data)
//            {
//                previous->left = new Node(data);
//            }
//            else
//            {
//                previous->right = new Node(data);
//            }
            
            Node *current = root;
            
            while(current != nullptr)
            {
                if(data < current->data)
                {
                    if(current->left != nullptr)
                    {
                        current = current->left;
                    }
                    else
                    {
                        current->left = new Node(data);
                        current = nullptr;
                    }
                }
                else
                {
                    if(current->right != nullptr)
                    {
                        current = current->right;
                    }
                    else
                    {
                        current->right = new Node(data);
                        current = nullptr;
                    }
                }
            }
        }
    }
    
    void insertRecursive(const T &data)
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
    
    ~BST()
    {
        destroy(root);
    }
    
};

#endif /* BST_hpp */
