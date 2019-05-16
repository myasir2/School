#include "lab5.h"
#include <iostream>

/************************************************************/
/*  Lab 5 tester                                            */
/*  To compile:                                             */
/*     g++ lab5tester.cpp -std=c++0x                        */
/*  To run:                                                 */
/*     ./a.out                                              */
/************************************************************/
int main(void){
	const int numTrees = 11;
	const int numNodes = 19;
	BST<int> testTree[numTrees];
	BST<int> correctTree[numTrees];
	int dataset[numNodes]={9,4,14,2,5,10,17,1,3,7,12,16,18,6,8,11,13,15,19};
	int resultset[numTrees][numNodes]={
		{},
		{4},
		{14},
		{9,4,14,2,5,10,17,3,7,12,16,18,6,8,11,13,15,19},  //remove 1: a leaf 
		{9,4,14,2,5,10,17,1,3,7,12,18,6,8,11,13,15,19},   //remove 16: node with only left child
		{9,4,14,2,5,10,17,1,3,7,12,16,6,8,11,13,15,19},   //remove 18: node with only right child
		{9,4,14,2,10,17,1,3,7,12,16,18,6,8,11,13,15,19},  //remove 5: node with right child, right child has subtree
		{9,4,15,2,5,10,17,1,3,7,12,16,18,6,8,11,13,19},   //remove 14: node with 2 children, inorder successor has no children
		{9,4,14,3,5,10,17,1,7,12,16,18,6,8,11,13,15,19},  //remove 2: node with 2 children, inorder successor is right child
		{9,5,14,2,10,17,1,3,7,12,16,18,6,8,11,13,15,19},  //remove 4: node with 2 children, inorder successor is right child who has children
		{10,4,14,2,5,17,1,3,7,12,16,18,6,8,11,13,15,19}   //remove 9: remove the root


	};
	int removeValues[numTrees]={9,9,9,1,16,18,5,14,2,4,9};
	testTree[0].insert(9);  //tree with just root

	testTree[1].insert(9);  //tree with root + left child
	testTree[1].insert(4);

	testTree[2].insert(9);  //tree with root + right child
	testTree[2].insert(14);
	//create the 8 identical trees
	for(int i=3;i<numTrees;i++){
		for(int j=0;j<numNodes;j++){
			testTree[i].insert(dataset[j]);
		}
	}

	//create the trees with the correct results
	correctTree[1].insert(resultset[1][0]);
	correctTree[2].insert(resultset[2][0]);

	for(int i=3;i<numTrees;i++){
		for(int j=0;j<numNodes-1;j++){
			correctTree[i].insert(resultset[i][j]);
		}
	}
	//remove one node from each tree
	for(int i=0;i<numTrees;i++){
		testTree[i].remove(removeValues[i]);
	}
	bool passtest=true;
	for(int i=0;passtest && i<numTrees;i++){
		std::cout << "Test " << i+1 << " : ";
		if(testTree[i]==correctTree[i]){
			std::cout << "remove(" << removeValues[i] << ") was correctly done." << std::endl;
			std::cout << "preOrder() :";
			testTree[i].printPreOrder();
			std::cout << "inOrder() :";
			testTree[i].printInOrder();
		}
		else{
			std::cout << "remove(" << removeValues[i] << ") was not correct" << std::endl;
			std::cout << "Your Tree:" << std::endl;
			testTree[i].print();
			std::cout << std::endl << std::endl;
			std::cout << "Correct Tree:" << std::endl;
			correctTree[i].print();
			passtest=false;
		}
	}
	if(passtest){
		std::cout << "Lab 5 tests successfully completed" << std::endl;
	}
	else{
		std::cout << "Lab 5 tests were not completed" << std::endl;
	}


	return 0;
}