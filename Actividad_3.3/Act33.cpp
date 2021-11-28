#include <bits/stdc++.h>

using namespace std;

struct Node {
	int data;
	Node *left, *right;

	Node(int data)
	{
		this->data = data;
		this->left = NULL;
		this->right = NULL;
	}
};

struct AVLTree 
{
	Node *root;

	/* CONSTRUCTORS */

	AVLTree() { this->root = NULL; }
	AVLTree(Node *root) { this->root = root; }

	/* METHODS */

	/* isEmpty() 
	* Util function to check if the root is empty (empty tree...) 
	* 
	* @return Whether the tree is empty or not
	*/
	bool isEmpty() {
		return this->root == NULL;
	}

	int size() 
	{
		return sizeUtil(this->root);
	}

	/* sizeUtil()
	* Util function to return the size of the tree using DFS.
	* 
	* Time Complexity: O(n) since it traverses all of the nodes.
	*/
	int sizeUtil(Node *root) {
		if (root == NULL) 
			return 0;
		
		return(sizeUtil(root->left) + sizeUtil(root->right) + 1);
	}

	/* height()
	* Gets overall height of the tree depending on the left
	* and right subtrees.
	*
	* Time Complexity: O(n) as it passsess through each node 
	*
	* @param node The node from which the height needs to be computed
	* @return The height of the tree starting at node
	*/
	int height(Node *node)
	{ 	
		if (node == NULL) return -1;

		int leftHeight = height(node->left);
		int rightHeight = height(node->right);

		if (leftHeight > rightHeight) {
			return leftHeight + 1;
		}

		return rightHeight + 1;
	} 

	/* getBalanceFactor
	* Calculates the balance factor of an specific node depending on the 
	* height of the left subtree and the right subtree.
	* 
	* Time Complexity: O(n)
	*
	* @param node The node from which the balance factor needs to be computed
	* @return The balance factor of the tree startingn at the node
	*/
	int getBalanceFactor(Node *node)
	{
		if (node == NULL) return -1;
		return height(node->left) - height(node->right);
	}


	/* rightRotate()
	* Performs right rotation at n1. This sets the left node as the root of 
	* the original node and the latter and its right node as childs
	* 
	* Time Complexity: O(1)
	*
	* @param n1 Node over rotation will be performed
	* @return The new root at n2
	*/
	Node* rightRotate(Node* n1) {

		Node *n2 = n1->left;
		Node *T2 = n2->right;

		n2->right = n1;
		n1->left = T2;

		return n2;
	}

	/* rightRotate()
	* Performs left rotation at n1. This sets the right node as the root of 
	* the original node and the latter and its left node as childs
	* 
	* Time Complexity: O(1)
	*
	* @param n1 Node over rotation will be performed
	* @return The new root at n2
	*/
	Node* leftRotate(Node* n1)
	{
		Node *n2 = n1->right;
		Node *T2 = n2->left;

		n2->left = n1;
		n1->right = T2;

		return n2;
	}

	/* insert()
	* Function that wraps the insertion process. It calls insertUtil on the specified data
	* 
	* Time Complexity: O(log(n)) since it calls insertUtil
	*
	* @param data An integer representing the value to be inserted
	* @return None
	*/
	void insert(int data)
	{
		if (this->root == NULL) {
			this->root = new Node(data);
			return;
		}

		this->root = insertUtil(this->root, data);
	}

	/* insertUtil()
	* To insert the node first it is inserted at its correct location, 
	* then we go backwards until the first node that is the root for an
	* unbalanced tree.
	* 
	* Time Complexity: O(h) -> O(log(n))
	*
	* @param r The root node 
	* @param data The data to be inserted
	* @return The new root node
	*/
	Node* insertUtil(Node *r, int data)
	{
		if (r == NULL) {
			r = new Node(data);
			return r;
		}

		if (data < r->data) { 
			r->left = insertUtil(r->left, data);
		} else if (data > r->data) {
			r->right = insertUtil(r->right, data);
		} else {
			return r;
		}

		int balanceFactor = getBalanceFactor(r);	

		if (balanceFactor > 1) {
			if (data > r->left->data) {
				r->left = leftRotate(r->left);
			} 
			return rightRotate(r);
		} else if (balanceFactor < -1) {
			if (data < r->right->data) {
				r->right = rightRotate(r->right);
			}
			return leftRotate(r);
		}
		return r;
	}

	/* delete()
	* Function that wraps the deletion process. It calls deleteUtil on the specified data
	* 
	* Time Complexity: O(log(n)) since it calls deleteUtil
	*
	* @param data An integer representing the value to be deleted
	* @return None
	*/
	void del(int data)
	{
		this->root = deleteUtil(this->root, data);
	}

	/* deleteUtil()
	* To delete a node first the it needs to be found and deleted as 
	* a normal BST. After that the tree needs to be rebalanced. 
	* 
	* Time Complexity: O(h) -> O(log(n))
	*
	* @param r The root node 
	* @param data The data to be deleted
	* @return The new root node
	*/
	Node* deleteUtil(Node *r, int data)
	{
		if (!r)
			return r;

		// Normal BST deletion
		if (data < r->data) { 
			r->left = deleteUtil(r->left, data);
		} else if (data > r->data) {
			r->right = deleteUtil(r->right, data);
		} else {
			Node *temp;
			if (!r->left) {
				temp = r->right;
				delete(r);
				return temp;
			} else if (!r->right) {
				temp = r->left;
				delete(r);
				return temp;
			} else {
				temp = r->right;
				while(temp->left)
					temp = temp->left;
				
				r = temp;
				r->right = deleteUtil(r->right, r->data);
			}
		}

		// Rebalance of tree 
		if (!r)
			return r;

		int balanceFactor = getBalanceFactor(r);	

		if (balanceFactor > 1) {
			if (getBalanceFactor(root->left) < 0)
				root->left = leftRotate(r->left);

			return rightRotate(r);
		} else if (balanceFactor < -1) {
			if (getBalanceFactor(root->right) > 0)
				r->right = rightRotate(r->right);
	
			return leftRotate(r);
		}
		return r;
	}

	/* find()
	* Performs a search in the AVL tree. This is similar to a Binary 
	* Search Tree, therefore the complexity is similar.
	* 
	* Time Complexity: O(log(n))
	*
	* @param data The data to be searched in the tree   
	* @return Whether the data is in the tree
	*/
	bool find(int data) 
	{
		Node *dummy = this->root;

		while(dummy) {
			if (dummy->data == data)
				return true;
			
			if (dummy->data < data)
				dummy = dummy->right;
			else
				dummy = dummy->left;
		}

		return false;
	}

	void printPreorder()
	{ 
		if(this->root) { 
			printPreorderUtil(this->root);
		}
	}

	/* printPreorderUtil()
	* Performs traversal and prints the nodes in the order: Root, Left Subtree, Right Subtree
	*
	* Time Complexity: O(n) since it visits all nodes 
	* 
	* @param root The root node to begin traversal
	* @return None
	*/
	void printPreorderUtil(Node *root)
	{
		if(root){
			cout << root->data << " ";
			printPreorderUtil(root->left);
			printPreorderUtil(root->right);
		}
	}
};

int main() 
{ 
	AVLTree myTree = AVLTree(); // new AVLTree object

	// Insertion of nodes	
	myTree.insert(8);
	myTree.insert(7);
	myTree.insert(6);
	myTree.insert(5);
	myTree.insert(4);
	myTree.insert(3);
	myTree.insert(2);
	myTree.insert(1);

	// Output of tree before deletion
	cout << "1. Tamaño de árbol antes de borrar: " << myTree.size() << "\n"; 
	cout << "2. Árbol antes de borrar:\n"; 
	myTree.printPreorder();
	cout << "\n";

	// Deletion of node with key 6
	myTree.del(6);
	cout << "3. Tamaño del árbol después de borrar: " << myTree.size() << "\n";
	cout << "4. Árbol después de borrar:\n";
	myTree.printPreorder();
	cout << "\n";

	// Find node with key 7
	cout << "5. Búsqueda (¿hay un nodo con valor 5?): " << myTree.find(5) << "\n";
}