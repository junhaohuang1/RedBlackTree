#include <iostream>
#include <ctime>
#include "RedBlackTree.h"
#include "RedBlackTree.cpp"
using namespace std;


int main(){
	
	RedBlackTree<int> b;
	srand(time(NULL));
	for (int i = 0; i < 9; i++) {
		cout << "inserting\n";
		b.insert(i);
	}
	b.printInOrder();
	cout << "Got here!" << endl;
	cout << "Got here #2" << endl;
	return 0;
}