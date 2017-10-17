#include <iostream>
#include <iomanip>
#include "List.h"

ifstream fin ("LinkedInput.txt");
ofstream fout("LinkedOutput.txt");

List::List()    // default constructor initializes members
{
    head = NULL;                // points to first node
	last = NULL;				// points to the last node
	curr = NULL;				// points to the current node
	temp = NULL;				// a temporary pointer
	count = 0;  				// keeps count of # nodes in the list
}

List::~List()
{
    deleteList();
}

List::List(const List & source)  // copy constructor
{
    head = NULL;        // Sets head to null and copies list
    copyList(source);
}

void List::copyList(const List & rhs)
{
    node * newNode;         // pointer to create a node
    if(head != NULL)        // list is empty
        deleteList();
    if(rhs.head == NULL)    // if list is not empty, make it empty
    {
        head = NULL;
        last = NULL;
        count = 0;
    }
    else
    {
        curr = rhs.head;    // copy the gpa infohead;    // current points to the
        count = rhs.count;  // list to be copied

        // copy the first node
        head = new node;            // create the node
        head->myGPA = curr->myGPA;  // copy the gpa info
        head->myName = curr->myName;// copy the name info
        head->next = NULL;          // set the next field to null

        last = head;        // make last point to first
        curr = curr->next;  // make curr point to next node

        // copy the remaining list
        while(curr != NULL)
        {
            newNode = new node;             // create a node
            newNode->myGPA = curr->myGPA;   // copy the gpa info
            newNode->myName = curr->myName; // copy the name info
            newNode->next = NULL;           // assign null to next

            last->next = newNode;           // attach newNode after last
            last = newNode;                 // make last point to actual last node
            curr = curr->next;              // make curr point to the next node
        }// end while
    }// end if
}// end copyList

int List::size() const
{
    return count;   // Count access function
}

void List::deleteList()
{
    node * temp;    //Pointer to deallocate memory

    while (head != NULL)
    {
        temp = head;        //assign head to the temp pointer
        head = head->next;  //advance to the next node
        delete temp;
    }
    last = NULL;
    count = 0;
    cout << "         Record destroyed" << endl << endl;
}

string List::deleteNode(string name)
{
    string result = "";          //the deleted name thats returned
    node * current;         //pointer for current to search
    node * trailCurrent;    //node just before current
    bool found;             //flag for found or not

    if (head == NULL) // List is empty
        cout << "Can't delete from an empty list" << endl;
    else
    {
        if (head->myName == name)   // if head equals the name
        {
            current = head;     // Sets head to second node and deletes first
            head = head->next;
            count--;

            if (head == NULL) // the list only has one node
                last = NULL;
            delete current;
        }
        else                  //searches the list
        {
            found = false;
            trailCurrent = head;    //set trail to head, 1st node
            current = head->next;   //sets current to point to next node

            while(current != NULL && !found) //run out of list or not found
            {
                if (current->myName != name)
                {
                    trailCurrent = current; //advance both pointers
                    current = current->next;
                }
                else
                    found = true;
            }//end else

            if (found)  // if the name is found
            {
                result = current->myName;  //this is name
                trailCurrent->next = current->next;
                count--;

                if (last == current)
                    last = trailCurrent;    //if current is last node
                delete current;
            }
            else
                cout << "The item to be deleted is not in the list" << endl;
        }//end else
    }//end else
    return result;
}//end of delete node

string List::addNode(string name, double gpa)
{
    string result;      // String variable to display addition
    node * n = new node;
    n->myGPA = gpa;     // Creates new node and sets name and GPA
    n->myName = name;
    n->next = NULL;

    if (head != NULL) //Searches if there is a list
    {
        curr = head;
        while(curr->next != NULL) // Goes through the list to last node
            curr = curr->next;

        curr->next = n;     // Sets last node to new addition
    }
    else
        head = n;
    count++;
    result = name + " was added"; // Sets string name
    return result;
}

void List::sortLinkedList(string key)
{
    node *prev;
    bool swapped = true;// Variable to tell if swapped or not

    if (head == NULL)   // Checks if there is a list
        return;

    if (key == "GPA")   // Sorts list by GPA
    {
        for(int i = 0; i <count && swapped; i++)
        {
            curr = head->next; // Sets current to next node and previous to current node
            prev = head;
            swapped = false;
            for(int j = 0; j < count - 1; j++)
            {
                if (prev->myGPA < curr->myGPA) // Tests to see if the previous node is larger than the next
                    swapped = swapData(curr, prev); // Swaps node data
                prev = curr;    // Goes to the next pair of nodes
                curr = curr->next;
            }

        }
    }

    if (key == "NAME")  // Sorts the list by GPA
    {
        for(int i = 0; i <count && swapped; i++)
        {
            curr = head->next;
            prev = head;
            swapped = false;
            for(int j = 0; j < count - 1; j++)
            {
                if (prev->myName > curr->myName)
                    swapped = swapData(curr, prev);
                prev = curr;
                curr = curr->next;
            }

        }
    }
}

istream& operator >> (istream & isObject, List & cObject)
{
    double addGPA;					// local data variable
	string lname, fname, name;

    // read 1st item in the list to "prime the pump"
    fin >> addGPA;    				// read the first GPA
    while(fin)
    {
    	node * n = new node;		// create space for the node
    	n-> next = NULL;			// next element points to nothing
	    fin >> lname >> fname;		// read in last & first names
		name = lname + " " + fname;	// concatenate the names
		n-> myName = name;
		n-> myGPA = addGPA;			// assign data to the node (GPA)

    	if(cObject.head != NULL)	 		// if head points to an object (list exists)
    	{
    		cObject.curr = cObject.head;				// make a copy of current head pointer
    		while(cObject.curr-> next != NULL)	// not yet at the end of the list
    			cObject.curr = cObject.curr->next;		// advance the current pointer
    		cObject.curr->next = n;				// connect the node to the list
    	}
    	else
    		cObject.head = n;				// head now points to 1st and only node
        cObject.count++;                    // adds 1 to the private count member
        fin >> addGPA;              // read the next double
    }// copy the gpa info
    fin.close();                   	// close the input file.  Done reading
}

bool List::swapData(node * &curr, node * &prev)
{
    double dTemp = curr->myGPA;     // Creates temporary variables to store name and GPA
    string sTemp = curr->myName;
    curr->myGPA = prev->myGPA;      // Switches name and GPA
    curr->myName = prev->myName;
    prev->myGPA = dTemp;
    prev->myName = sTemp;
    return true;
}
ostream& operator << (ostream & osObject, List & cObject)
{
    cout << fixed  << showpoint  << setprecision(2);
    fout << fixed  << showpoint  << setprecision(2);

    cObject.curr = cObject.head;
	// write the list
	while (cObject.curr != NULL)			// while there is data
	{
        cout << "         " << setw(9)
             << left << setw(18)
			 << cObject.curr->myName
			 << right
			 << setw(7)
			 << cObject.curr->myGPA << endl;
        fout <<  "         " << setw(9)
             << left << setw(18)
			 << cObject.curr->myName
			 << right
			 << setw(7)
			 << cObject.curr->myGPA << endl;
        cObject.curr = cObject.curr->next;			// now, point to the next node
	}
	cout << "         -------------------------" << endl
         << "         " << cObject.size() << " student records." << endl << endl;
    fout << "         -------------------------" << endl
         << "         " << cObject.size() << " student records." << endl << endl;
}

const List& List::operator= (const List & other)
{
    head = NULL;        // Sets one list equal to the other
    copyList(other);
}
