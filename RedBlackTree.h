#pragma once

template<typename T>

class RedBlackTree {

private:
	struct Node {
		T data;
		bool isBlack;
		Node* parent, *left, *right;
		Node();
		Node(const T& data);
		Node(const T& data, Node* parent, Node* left, Node* right);
	};

	Node* root;
	int nodeCount;
	Node* recursiveCopy(Node* toCopy);
	void singleCCR(Node*& point);
	void doubleCR(Node*& point);
	void singleCR(Node*& point);
	void doubleCCR(Node*& point);
	//fix violations after insertions
	void fixRedParentBlackUncleViolation(Node* point);
	//fix violations as looking for point of insertion
	void fixBlackParentTwoRedChildrenViolation(Node* point);
	void recolor(Node*& node);
	void print(Node* root) const;
	Node*& find(const T& toFind, Node* root) const;
	void insert(const T& item, Node* root, Node* parent);
	void clear(Node* root);

public:
	RedBlackTree();
	//big 3
	RedBlackTree& operator=(const RedBlackTree<T> rhs);
	virtual ~RedBlackTree();
	RedBlackTree<T>(const RedBlackTree<T>& rhs);

	bool isInTree(const T& toFind) const;
	bool isEmpty() const;
	int size()const;
	void insert(const T& item);
	Node*& find(const T& toFind) const;
	void clear();
	void printInOrder()const;
};

