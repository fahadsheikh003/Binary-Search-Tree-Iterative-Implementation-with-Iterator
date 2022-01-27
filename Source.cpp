#include<iostream>
#include"BinarySearchTree.h"

using namespace std;

int main()
{
	BST<double, string> bst;

	bst.Insert(5, "D");
	
	bst.Insert(3, "B");
	bst.Insert(7, "F");
	
	bst.Insert(2, "A");
	bst.Insert(4, "C");
	
	bst.Insert(6, "E");
	bst.Insert(8, "G");

	bst.Insert(5.5, "O");

	bst.Remove(7);

	BST<double, string>::InorderIterator it;

	cout << "In Order:\n";
	for (it = bst.begin(); it != bst.end(); it++)
	{
		cout << (*it).first << "  " << (*it).second << endl;
	}

	BST<double, string> bst2 = bst;
	
	cout << endl << endl;

	bst2.Remove(5);
	cout << "5 Removed!\n";

	BST<double, string>::PreorderIterator itr;

	cout << "Pre Order: \n";
	for (itr = bst2.begin(); itr != bst2.end(); itr++)
	{
		cout << (*itr).first << "  " << (*itr).second << endl;
	}

	cout << endl << endl;
	
	bst2.Remove(2);
	cout << "2 Removed!\n";
	bst2.Remove(6);
	cout << "6 Removed!\n";

	bst2.Insert(9, "X");
	cout << "9 added!\n";

	BST<double, string>::PostorderIterator iptr;

	cout << "Post Order: \n";
	for (iptr = bst2.begin(); iptr != bst2.end(); iptr++)
	{
		cout << (*iptr).first << "  " << (*iptr).second << endl;
	}
	
}