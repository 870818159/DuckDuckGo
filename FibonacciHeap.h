/**
 * @author Philip Zhang
 * @created on 08/11/2018
 */

//include all the c++ header source.
#include <bits/stdc++.h>
 
using namespace std;

class FibNode {
public:
	string   key;		/**< Keywords */
	int      freq;		/**< Frequency of the keywords. */
	int      degree;	/**< Degree of one node */
	
	FibNode* left;		/**< The left sibling of the node */
	FibNode* right;		/**< The right sibling of the node */
	FibNode* child;		/**< The first child of the node */
	FibNode* parent;	/**< The parent of the node */
	
	bool     marked;	/**< Whether has been deleted the first child */
	
	// Create and initialize a FibNode.
	FibNode(string keyword, int val);
};

class FibHeap {
private:
	int keyNum;			/**< Total number of the key nodes */
	int maxDegree;		/**< Max degree of the heap */
	
	FibNode *max;		/**< The max root value of the heap */
	FibNode **cons;		/**< When deleting the node, cons can store the node temporarily */

public:

	// Create and initialize an empty Fibonacci Heap.
	FibHeap();
	
	~FibHeap();
	
	// Insert the FibNode to the Fibonacci Heap.
	FibNode* insert(string key, int freq);
	
	// Update the frequency in the node.
	void update(map<string, FibNode*> &table, string key, int newfreq);
	
	// Remove the max value in Fibonacci Heap.
	FibNode* removeMax();
	
private:

	// Add the node before the max in the circular linked list.
	void addNode(FibNode* node, FibNode* root);
	
	// Remove the node from the circular linked list.
	void removeNode(FibNode* node);
	
	// Insert node to the Fibonacci Heap.
	FibNode* insertNode(FibNode* node);
	
	// Update node by increasing the frequency of the node.
	void updateNode(FibNode* node, int freq);
	
	// Remove the node from parent node and put the node in the root circular linked list.
	void cut(FibNode* node, FibNode* parent);
	
	// Cut the node.
	void cascadingCut(FibNode* node);
	
	// Increase the frequency.
	void increase(FibNode* node, int freq);
	
	// Consolidate the Fibonacci Heap which has the same degree.
	void consolidate();
	
	// Create the area for consolidation.
	void makeCons();
	
	// Extract the max node from the Fibonacci Heap.
	FibNode* extractMax();
	
	// Link the node to the root.
	void link(FibNode* node, FibNode* root);
};