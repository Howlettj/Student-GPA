// Justin Howlett
// November 17, 2016
// Bubble Sorting in a Linked list
// Purpose of program is to demonstrate bubble sorting in a linked list
// Execution of the program will call various functions to sort the list by GPA and
// by name. It will also demonstrate how to add and delete a node with separate functions

#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>

#include "List.cpp"

using namespace std;

void title(string);                 // prototypes for functions called
void process(List);

int main()
{
    title("title"); // Calls title to display main title

    List list1;     // Creates list one and list two
    List list2;

    fin >> list1;   // Reads file to create list
    fin.close();    // Closes input file

    list2 = list1;  // Uses overloaded = operator to set them equal

    process(list2); // Send list2 to function as instance of list1

    title("Original List"); // Calls title to display original list
    fout << endl;
    cout << list1;          // Displays list to file and output
    fout.close();

	return 0;
}

void title(string st)
{
    string month[] = {"January", "February", "March", "April", "June",  // Holds the months by number
                    "July", "August", "September", "October", "November", "December"};

    time_t now = time(0);           // Gets the time for now
    tm *ltm = localtime(&now);

    int monthNum = ltm->tm_mon - 1; // Sets the month, year and day to today
    int day = ltm->tm_mday;
    int year = 1900 + ltm->tm_year;

    if (st == "title")
    {       // Displays title
        cout << "L I N K E D   L I S T   G P A   R E P O R T" << endl << endl
             << "      Current Date: " << month[monthNum] << " " << day << ", " << year << endl << endl
             << "                     by" << endl << endl
             << "               Justin Howlett" << endl << endl
             << "         LastName, First       GPA" << endl
             << "         ---------------       ---" << endl;

        fout << "L I N K E D   L I S T   G P A   R E P O R T" << endl << endl
             << "      Current Date: " << month[monthNum] << " " << day << ", " << year << endl << endl
             << "                     by" << endl << endl
             << "               Justin Howlett" << endl << endl
             << "         LastName, First       GPA" << endl
             << "         ---------------       ---" << endl;
    }

    if (st != "title")  // Displays title by sort type
    {
        cout << "         " << "(" << st  << ")" << endl << "         -------------------------" << endl;
        fout << "         " << "(" << st  << ")" << endl << "         -------------------------" << endl;
    }
}

void process(List listy)
{
    string name;

    title("unsorted");  // Calls title for unsorted
    cout << listy;
    cout << endl;      // Displays list with number of members
    fout << endl;

    listy.sortLinkedList("GPA"); // Sorts list by GPA
    title("GPA sorted");         // Calls title for GPA
    cout << listy;

    name = listy.deleteNode("Asp, Baad"); // Deletes Asp, Baad node
    cout << "         " << name << " was deleted" << endl << endl;
    fout << "         " << name << " was deleted" << endl << endl;
    title("GPA sorted"); // Sorts list by GPA
    cout << listy;

    name = listy.addNode("Study, Alot", 4.00); // Adds node Study, Alot, 4.00
    cout << "         " << name << endl << endl;
    fout << "         " << name << endl << endl;

    listy.sortLinkedList("NAME"); // Sorts list by NAME
    title("Alphabetically sorted"); // Displays title for alphabetical
    cout << listy;
    fout << endl;
}
