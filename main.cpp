#include <iostream>
#include <cstring>
#include <vector>
#include <iomanip> 
#include <fstream>

using namespace std;
// Struct definition
struct Student {
    char givenName[100];
    char surname[100];
    float grade;
    int studentID;
    Student* next = NULL;
};

// Function declarations
Student** addPupils(Student** roster, int &currentID, int &capacity);
Student** manAdd(Student** roster, int &currentID, int &capacity);
void displayAll(Student** roster, int capacity);
void display(Student** roster, int capacity);
void eliminate(Student** roster, int capacity);
void resetRoster(Student* roster[], int capacity);
void printChain(Student* current);
Student** rehashRoster(Student** roster, Student** newRoster, int &capacity, int currentID);


