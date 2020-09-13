/**
 * @author Philip Zhang
 * @created on 08/11/2018
 */

//include all the c++ header source.
#include <bits/stdc++.h>

#include "FibonacciHeap.h"
 
using namespace std;

/**
 * Create and initialize a FibNode.
 * @param	string keyword		keyword in the inputfile.
 * @param	int val				the frequency of the keyword.
 */
FibNode::FibNode(string keyword, int val) {
	key    = keyword;
	freq   = val;
	degree = 0;
	marked = false;
	left   = this;
	right  = this;
	parent = nullptr;
	child  = nullptr;
}

/**
 * Create and initialize an empty Fibonacci Heap.
 */
FibHeap::FibHeap() {
	keyNum    = 0;
	maxDegree = 0;
	max       = nullptr;
	cons      = nullptr;
}

/**
 * Destructor for FibHeap.
 */
FibHeap::~FibHeap() {}

/**
 * Add the node before the max in the circular linked list.
 * ...root
 * ...node...root
 * @param	FibNode* node		node that will be added.
 * @param	FibNode* max		max node in Fibonacci Heap.
 * @return	void.
 */
void FibHeap::addNode(FibNode* node, FibNode* max) {
	node->left        = max->left;
	max->left->right  = node;
	node->right       = max;
	max->left         = node;
	return;
}

/**
 * Insert node to the Fibonacci Heap.
 * @param	FibNode* node	node that will be inserted.
 * @return	the address of the inserted node.
 */
FibNode* FibHeap::insertNode(FibNode* node) {
	if (!keyNum)
		max = node;
	else {
		addNode(node, max);
		if (node->freq > max->freq)
			max = node;
	}
	++keyNum;
	return node;
}

/**
 * Insert the FibNode to the Fibonacci Heap.
 * @param	string key		keyword int the inputfile.
 * @param	int freq		the frequency of the keyword.
 * @return	the address of the inserted node.
 */
FibNode* FibHeap::insert(string key, int freq) {
	FibNode *node = new FibNode(key, freq);
	if (node == nullptr)
		return nullptr;
	return insertNode(node);
}

/**
 * Remove the node from the circular linked list.
 * ...node...root
 * ...root
 * @param	FibNode* node	node that will be deleted.
 * @return	void.
 */
void FibHeap::removeNode(FibNode* node) {
	node->left->right = node->right;
	node->right->left = node->left;
	return;
}

/**
 * Update node by increasing the frequency of the node.
 * @param	FibNode* node		node that will be updated.
 * @param	int freq			the new frequency will add to the old frequency in the node.
 * @return	void.
 */
void FibHeap::updateNode(FibNode* node, int freq) {
	increase(node, freq);
	return;
}

/**
 * Remove the node from parent node and put the node in the root circular linked list.
 * @param	FibNode* node		node that will be cut.
 * @param	FibNode* parent		the parent of the node being cut.
 * @return	void.
 */
void FibHeap::cut(FibNode* node, FibNode* parent) {
	removeNode(node);
	--(parent->degree);
	
	if (node == node->right) 
		parent->child = nullptr;
	else 
		parent->child = node->right;
	
	node->parent = nullptr;
	node->left = node->right = node;
	node->marked = false;
	
	addNode(node, max);
	return;
}

/**
 * Cut the node.
 * @param	FibNode* node	node that will be cut.
 * @return	void.
 */
void FibHeap::cascadingCut(FibNode* node) {
	FibNode* parent = node->parent;
	if (parent != nullptr) {
		if (node->marked == false) 
			node->marked = true;
		else {
			cut(node, parent);
			cascadingCut(parent);
		}
	}
	return;
}

/**
 * Increase the frequency.
 * @param	FibNode* node		node that will be increased.
 * @param	int freq			frequency that will be updated.
 * @return	void.
 */
void FibHeap::increase(FibNode* node, int freq) {
	FibNode* parent;
	
	if (max == nullptr || node == nullptr)
		return;
	
	node->freq = node->freq + freq;
	
	parent = node->parent;
	if (parent != nullptr && node->freq > parent->freq) {
		cut(node, parent);
		cascadingCut(parent);
	}
	
	if (node->freq > max->freq)
		max = node;
	
	return;
}

/**
 * Update the frequency in the node.
 * @param	map<string, FibNode*> &table	hashtable used to find the address of the proper node.
 * @param	string key						keyword used to search for proper node.
 * @param	int newfreq						new frequency waiting to be updated.
 * @return	void.
 */
void FibHeap::update(map<string, FibNode*> &table, string key, int newfreq) {
	if (table[key] != nullptr)
		updateNode(table[key], newfreq);
	return;
}

/**
 * Extract the max node from the Fibonacci Heap.
 * @return	the address of the extracted node.
 */
FibNode* FibHeap::extractMax() {
	FibNode* p = max;
	if (p == p->right)
		max = nullptr;
	else {
		removeNode(p);
		max = p->right;
	}
	p->left = p->right = p;
	return p;
}
	
/** 
 * Link the node to the root.
 * @param	FibNode* node		node that will be linked.
 * @param	FibNode* root		the root for node to link.
 * @return	void.
 */
void FibHeap::link(FibNode* node, FibNode* root) {
	removeNode(node);
	if (root->child == nullptr)
		root->child = node;
	else
		addNode(node, root->child);
	
	node->parent = root;
	++root->degree;
	node->marked = false;
	
	return;
}

/** 
 * Create the area for consolidation.
 * @return	void.
 */
void FibHeap::makeCons() {
	int old = maxDegree;
	
	maxDegree = (log(keyNum) / log(2.0)) + 1;
	if (old >= maxDegree)
		return ;
	
	cons = new FibNode*[maxDegree + 1];
	
	return;
}

/**
 * Consolidate the Fabonacci Heap which has the same degree.
 * @return	void.
 */
void FibHeap::consolidate() {
	int i, d, D;
	FibNode *x, *y, *tmp;
	
	makeCons();
	D = maxDegree + 1;

	for (i = 0; i < D; i++)
		cons[i] = nullptr;
  
	while (max != nullptr) {
		
		x = extractMax();
		d = x->degree;
	
		while (cons[d] != nullptr) {
			y = cons[d];
			
			if (x->freq < y->freq)
				swap(x, y);
 
			link(y, x); 
			cons[d] = nullptr;
			++d;
		}
		cons[d] = x;
	}
	max = nullptr;
  
	// Put the node in the cons to the cycle linked list.
	for (i = 0; i < D; ++i) {
		if (cons[i] != nullptr) {
			if (max == nullptr)
				max = cons[i];
			else {
				addNode(cons[i], max);
				if ((cons[i])->freq > max->freq)
					 max = cons[i];
			}
		}
	}
	return;
}

/**
 * Remove the max value in Fibonacci Heap.
 * @return	the address of the removeMax node.
 */
FibNode* FibHeap::removeMax() {
	if (max == nullptr)
		return nullptr;
	
	FibNode* child = nullptr;
	FibNode* m     = max;
	FibNode* ret   = new FibNode(max->key, max->freq);
	
	while (m->child != nullptr) {
		child = m->child;
		removeNode(child);
		
		if (child->right == child)
			m->child = nullptr;
		else
			m->child = child->right;
		
		addNode(child, max);
		child->parent = nullptr;
	}
	
	removeNode(m);
	if (m->right == m)
		max = nullptr;
	else {
		max = m->right;
		consolidate();
	}
	--keyNum;
	delete m;
	
	return ret;
}
