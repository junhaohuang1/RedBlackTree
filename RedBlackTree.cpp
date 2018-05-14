#include "RedBlackTree.h"
#include <iostream>

template<typename T>
inline RedBlackTree<T>::RedBlackTree() : root(nullptr)
{
}

template<typename T>
RedBlackTree<T>& RedBlackTree<T>::operator=(const RedBlackTree<T> rhs)
{
	// TODO: insert return statement here
}

template<typename T>
RedBlackTree<T>::~RedBlackTree()
{
	clear();
}

template<typename T>
RedBlackTree<T>::RedBlackTree(const RedBlackTree<T>& rhs)
{
}

template<typename T>
bool RedBlackTree<T>::isInTree(const T & toFind) const
{
	return find(toFind) == nullptr;
}

template<typename T>
bool RedBlackTree<T>::isEmpty() const
{
	return this->root == nullptr;
}

template<typename T>
int RedBlackTree<T>::size() const
{
	return nodeCount;
}

template<typename T>
void RedBlackTree<T>::insert(const T & item)
{
	insert(item, this->root, this->root);
}

template<typename T>
typename RedBlackTree<T>::Node*& RedBlackTree<T>::find(const T & toFind) const
{
	return find(toFind, this->root);
}

template<typename T>
void RedBlackTree<T>::clear()
{
	clear(this->root);
}

template<typename T>
void RedBlackTree<T>::printInOrder() const
{
	print(this->root);
}

template<typename T>
inline typename RedBlackTree<T>::Node* RedBlackTree<T>::recursiveCopy(Node* toCopy)
{
	return T();
}

template<typename T>
inline void RedBlackTree<T>::singleCCR(Node*& point)
{
	Node* grandparent = point;
	Node* parent = point->right;
	parent->parent = grandparent->parent;
	grandparent->parent = parent;
	grandparent->right = parent->left;
	parent->left = grandparent;
	if (grandparent->right != nullptr) //if we now have a right child, update its parent pointer
		grandparent->right->parent = grandparent;
	if (parent->parent == nullptr)//if we were the root, update the root!
		root = parent;
	else if (parent->parent->right == grandparent)
		parent->parent->right = parent;
	else
		parent->parent->left = parent;
}

template<typename T>
inline void RedBlackTree<T>::doubleCR(Node*& point)
{
	singleCCR(point->left);
	singleCR(point);
}

template<typename T>
inline void RedBlackTree<T>::singleCR(Node*& point)
{
	Node* grandparent = point;
	Node* parent = point->left;
	parent->parent = grandparent->parent;
	grandparent->parent = parent;
	grandparent->left = parent->right;
	parent->right = grandparent;
	if (grandparent->left != nullptr) //if we now have a left child, update its parent pointer
		grandparent->left->parent = grandparent;
	if (parent->parent == nullptr)//if we were the root, update the root!
		root = parent;
	else if (parent->parent->left == grandparent)
		parent->parent->left = parent;
	else
		parent->parent->right = parent;
}

template<typename T>
inline void RedBlackTree<T>::doubleCCR(Node*& point)
{
	singleCR(point->right);
	singleCCR(point);
}



template<typename T>
inline void RedBlackTree<T>::recolor(Node *& node)
{
	if ((*node).isBlack)
		(*node).isBlack = false;
	else
		(*node).isBlack = true;
}

template<typename T>
void RedBlackTree<T>::print(Node *& root)
{
	if (root->left != nullptr)
		print(root->left);
	std::cout << root->val;
	if (root->right != nullptr)
		print(root->right);
}

template<typename T>
typename RedBlackTree<T>::Node*& RedBlackTree<T>::find(const T & toFind, Node * root) const
{
	if (root == nullptr || root->val == toFind)
		return root;
	else if (root->val < toFind)
		return find(toFind, root->right);
	else
		return find(toFind, root->left);
}

template<typename T>
inline RedBlackTree<T>::Node::Node() : data(T()), parent(nullptr), left(nullptr), right(nullptr), isBlack(false)
{
}

template<typename T>
RedBlackTree<T>::Node::Node(const T & data) : data(data), parent(nullptr), left(nullptr), right(nullptr), isBlack(false)
{
}

template<typename T>
RedBlackTree<T>::Node::Node(const T & data, Node * parent, Node * left, Node * right): data(data), parent(parent), left(left), right(left), isBlack(false)
{
}

template<typename T>
void RedBlackTree<T>::insert(const T & item, Node * root, Node* parent)
{
	if (isEmpty) {
		root = new Node(item);
		(*root).isBlack = true;
		this->nodeCount++;
	}

	if (root == nullptr) {
		this->nodeCount++;
		if (parent->val < item) {
			parent->right = new Node(item, parent, nullptr, nullptr);
		}
		else if(parent->val > item) {
			parent->left = new Node(item, parent, nullptr, nullptr);
		}
	}
	else if (root->val < item)
		insert(item, root->right, root);
	else if(root->val > item)
		insert(item, root->left, root);
}

template<typename T>
void RedBlackTree<T>::doRotation(Node * point)
{	
	if (point == nullptr)
		return;
	//check for black parent with two red children as inserting
	if (point->left != nullptr && point->right != nullptr) {
		if ((*point).isBlack && !(*point->left).isBlack && !(*point->left).isBlack) {
			recolor(point);
			recolor(point->left);
			recolor(point->right);
			if (point->parent != nullptr) {
				if (point == point->parent->left)
					singleCR(point->parent);
				else if (point == point->parent->right)
					singleCCR(point->parent);
			}
		}
	}
	//check for when parent is red and uncle is black after inserting
	else if (point->parent->parent != nullptr) {
		Node* grandparent = point->parent->parent;
		if (!(*point->parent).isBlack) {
			Node* uncle = (grandparent->left == point->parent) ? grandparent->right : grandparent->left;
			//if uncle is black
			if (uncle == nullptr || (*uncle).isBlack) {
				//if the node is outside, single rotate grandparent
				if (point == parent->left && parent == grandparent->left)
					singleCR(grandparent);
				else if (point == parent->right && parent == grandparent->right)
					singleCCR(grandparent);
				//if node is inside, double rotate grandparent
				else if (point == parent->left && parent == grandparent->right)
					doubleCCR(grandparent);
				else if (point == parent->right && parent == grandparent->left)
					doubleCR(grandparent);
			}
		}
	}
}


template<typename T>
void RedBlackTree<T>::clear(Node * root)
{
	if (root != nullptr) {
		clear(root->left);
		clear(root->right);
		delete root;
	}
}
