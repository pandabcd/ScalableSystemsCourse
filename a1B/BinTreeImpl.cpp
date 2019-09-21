#include "IBinTree.h"
#include <iostream>
#include <float.h>
#include<limits.h> //Just to include INT_MIN

using namespace std;

/**
 * Array Implementation of Binary Tree
 */
class ArrayBinTree: public IBinTree
{  
	private: 
		struct node{
			int k;
			float v;

			node(int key, float value){
				k = key;
				v = value;
			}
			// Nodes with key = FLT_MAX are equivalent of null nodes in this implementation
			node(){
				k = FLT_MAX;
				v = FLT_MAX;
			}
		};
		// tree_size = array size
		// tree_ind = index of last inserted element
		int tree_size, tree_ind;
	
	public:
		struct node* tree ;
	
	ArrayBinTree()
	{ 
		tree_size = 0;
		tree_ind = -1; // Has the index of last inserted element
		tree = NULL;
	}
 
 
    void insert (int key, float value)
	{ 
	  
	    node* n = new node(key, value);
	    
	    // If this is the first element, allocate array of size 10 nodes
	    if(tree_ind == -1){
	    	tree_size = 10;
	    	tree = (node*)malloc(tree_size*sizeof(struct node));
	    	// All the nodes(except root) have to be null(key value FLT_MAX in the implementation)
	    	for(int i=0;i<tree_size;i++){
	    		tree[i] = node();
	    	}
	    	tree[0] = *n;
	    	tree_ind++;
	    	return ;
	    }

	    tree_ind++;
	    // If the tree is full, get more size dynamically
	    if(tree_ind==tree_size){
	    	increase_tree_size();
	    	tree[tree_ind] = *n;
	    }
	    else{
	    	tree[tree_ind] = *n;
	    }
	}

	
	float find(int key)
	{ 
	   	// Linear search algorithm
	    for(int i=0;i<=tree_ind;i++){
	    	if(tree[i].k==key){
	    		return tree[i].v;
	    	}
	    }
	    return FLT_MAX;
	}

	
	int count()
	{
		return tree_ind+1;
	}

	// Doubles the size of array everytime size limit is reached
	void increase_tree_size(){
		int old_size = tree_size;
		tree_size*=2;
		tree = (node *)realloc(tree,tree_size*sizeof(struct node));
	}
};

class LinkedBinTree: public IBinTree
{  

	private: 
		struct node {
			int k;
			float v;
			node *left, *right;

			node(int key, int val){
				k = key;
				v = val;
				left = NULL;
				right = NULL;
			}
		};
		node *root;
		// Number of nodes
		int num_nodes;
   
   
	public:
	LinkedBinTree()
	{ 
		root = NULL;
		num_nodes = 0;
	}
 
 // Makes a skewed tree to the right with new element being the root.
	// This is most efficient as it inserts in O(1) and searches in O(n) which is the best assuming random distribution
	void insert (int key, float value)
	{ 
	    num_nodes++;
	    node *n = new node(key, value);
	    n->right = root;
	    root = n;

	}

	
	float find(int key)
	{ 
	    node *curr = root;

	    // Searching in a right skewed tree
	    while(curr){
	    	if(curr->k==key){
	    		return curr->v;
	    	}
	    	curr = curr->right;
	    }
	    return FLT_MAX;
	}

	
	int count()
	{
		return num_nodes;
	}

};

/**
 * Array Implementation of Binary Search Tree
 */
class ArrayBinSearchTree: public IBinTree
{  

	private: 
		struct node{
			int k;
			float v;

			node(int key, float value){
				k = key;
				v = value;
			}

			node(){
				k = INT_MIN;
				v = INT_MIN;
			}
		};
		struct node* tree ;
		// Tree size = array size
		int num_nodes, tree_size;
	
	public:
	
  	ArrayBinSearchTree()
	{ 
		tree_size = 0;
		num_nodes = 0;
		tree = NULL;
	}

    void insert (int key, float value)
	{ 
		num_nodes++;
		node* n = new node(key, value);
	
	    // Inititalising tree size with 10
	    if(tree_size==0){
	    	tree_size = 10;
	    	tree = (node*)malloc(tree_size*sizeof(struct node));
	    	for(int i=0;i<tree_size;i++){
	    		// Test if new should come
	    		node *x = new node();
	    		tree[i] = *x;
	    	}
	    	tree[0] = *n;
	    	return ;
	    }

	    int tree_ind = 0;

	    while(1){
	    	if(key <= tree[tree_ind].k ){
	    		// If left is empty
	    		int left_ind = left(tree_ind);
	    		// If index out of bounds, increase bounds
	    		if(left_ind>= tree_size){
	    			increase_tree_size();
	    		}

	    		// Equivalent to checking a logical NULL
	    		if(tree[left_ind].k == INT_MIN){
	    			 tree[left_ind] = *n;
	    			 return;
	    		}
	    		else{
	    			tree_ind = left(tree_ind);
	    		}
	    	}

	    	else{
	    		int right_ind = right(tree_ind);

	    		if(right_ind >= tree_size){
	    			increase_tree_size();
	    		}
	    		// If right is empty
	    		if(tree[right_ind].k == INT_MIN){
	    			tree[right_ind] = *n;
	    			return;
	    		}
	    		else{
	    			tree_ind = right(tree_ind);
	    		}
	    	}
	    }


	    

	}

	float find(int key)
	{ 
	    int curr = 0;
	    if(tree[curr].k == FLT_MAX){
	    	cout<<"empty tree";
	    	return FLT_MAX;
	    }

	    // while current is not null(logical) and in bounds
	    while(curr < tree_size && tree[curr].k != FLT_MAX){
	    	if(tree[curr].k == key){
	    		return tree[curr].v;
	    	}
	    	if(key<tree[curr].k){
	    		curr = left(curr);
	    	}
	    	else{
	    		curr = right(curr);
	    	}
	    }

	    return FLT_MAX;

	}

	
	int count()
	{
		return num_nodes;
	}

	 // #######################################################
// Doubles the size of array and puts empty nodes(logical) in place
	void increase_tree_size(){
		int old_size = tree_size;
		tree_size*=2;

		tree = (node *)realloc(tree,tree_size*sizeof(struct node));

		// Initializing new empty nodes
		for(int i=old_size;i<tree_size;i++){
			node *x = new node();
	    	tree[i] = *x;
		}
	}

	int parent(int i){
		return i/2;
	}

	int left(int i){
		return i*2+1;
	}

	int right(int i){
		return i*2+2;
	}
};

/**
 * Linked Implementation of Binary Search Tree
 */
class LinkedBinSearchTree: public IBinTree
{  

	private: 
		// TODO
		struct node {
			int key;
			float val;
			node *left, *right;

			node(int k, int v){
				key = k;
				val = v;
				left = NULL;
				right = NULL;
			}
		};
		node *root;
		int num_nodes;
   
   
	public:
	LinkedBinSearchTree()
	{ 
		root = NULL;
		num_nodes = 0;
	}
 
    void insert (int key, float value)
	{ 
	    num_nodes++;
	    node* n = new node(key, value);
	   
	    if(root==NULL){
	    	root = n;
	    	return;
	    }
	    node* curr = root;

	    while(1){
	    	// Can break in key1=k=key2
	    	if(n->key<=curr->key){
	    		if(!curr->left){
	    			curr->left = n;
	    		    break;
	    		}
	    		else
	    			curr=curr->left;
	    	}
	    	else{
	    		if(!curr->right){
	    			curr->right = n;
	    			break;
	    		}
	    		else
	    			curr = curr->right;
	    	}
	    }
	}

	float find(int key)
	{ 
	    node* curr = root;
	    if(root==NULL){
	    	cout<<"Empty tree!";
	    	return FLT_MAX;
	    }

	    while(curr!=NULL){
	    	if(curr->key==key){
	    		return (float)curr->val;
	    	}
	    	if(key<curr->key){
	    		curr=curr->left;
	    	}
	    	else{
	    		curr=curr->right;
	    	}
	    }

	    return (float)FLT_MAX;
	}

	
	int count()
	{
		return num_nodes;
	}

};