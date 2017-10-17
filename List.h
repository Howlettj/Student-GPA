#ifndef List_H
#define List_H

#include <fstream>
#include <string>

using namespace std;

struct node
{
	string myName;				// holds name of student
    double myGPA;				// holds GPA of student
	node*  next;				// link points to the next node
};

class List
{
    // operator overloading for insertion & extraction streams
    friend ostream& operator << (ostream &, List & );
    friend istream& operator >> (istream &, List & );

private:
	node *head;					// points to the head of list
	node *last;					// points to the last node
	node *curr;					// points to the current node
	node *temp;					// a temporary pointer
	int count;  				// keeps count of # nodes in the list
    void copyList(const List & rhs); 	// a private copy function

public:
	List();					    // constructor for linked list
	~List();					// destructor for linked list
    List(const List & source);  // copy constructor
	const List& operator= (const List &); // * overload assignment op *

    void deleteList();			    // deletes the entire list
	int  size() const;			    // returns number of nodes in the list
	string addNode(string, double);	// adds one node with record data
	string deleteNode(string name);	// deletes node matching name
    void sortLinkedList(string key);	// bubble sorts list
    bool swapData(node * &curr, node * &prev);

};

#endif
