//hashtable firaol Berehanu 
//inputs a list of number using a key
//using changing to stor multiple values at one idnex
//also has rehash if the function becomes to crowed by having a index
//source - youtbe and stakoverfolow


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

// Main function
int main() {
    srand(time(0));
    bool exitProgram = false;
    Student** roster = new Student*[100];
    char userInput[7];
    int currentID = 0;
    int capacity = 100;
    resetRoster(roster, capacity);
    while (!exitProgram) {
        cout << "Please enter a valid command (ADD, MADD, PRINT, ALL(PRINT ALL), DELETE, QUIT):" << endl;
        cin >> userInput;
        if (strcmp(userInput, "MADD") == 0) {
            roster = manAdd(roster, currentID, capacity);
        }
        if (strcmp(userInput, "ADD") == 0) {
            roster = addPupils(roster, currentID, capacity);
        }
        else if (strcmp(userInput, "ALL") == 0) {
            displayAll(roster, capacity);
        }
        else if (strcmp(userInput, "PRINT") == 0) {
            display(roster, capacity);
        }
        else if (strcmp(userInput, "DELETE") == 0) {
            eliminate(roster, capacity);
        }
        else if (strcmp(userInput, "QUIT") == 0) {
            exitProgram = true;
        }
    }
    return 0;
}

// Function to add pupils
Student** addPupils(Student** roster, int &currentID, int &capacity) {
    int students;
    cout << "How many students would you like to add?" << endl;
    cin >> students;
    for (int i = 0; i < students; i++) {
        char input[100];
        char givenName[100];
        char surname[100];
        fstream givenFile("givenName.txt");
        fstream surnameFile("surname.txt");
        int count;
        int num = (rand() % 20) + 1;
        int num2 = (rand() % 20) + 1;
        Student* newStudent = new Student();
        count = 1;
        while (givenFile.getline(input, 100, '\n')) {
            if (count == num) {
                strcpy(givenName, input);
                count++;
            }
            count++;
        }
        givenFile.close();
        count = 1;
        while (surnameFile.getline(input, 100, '\n')) {
            if (count == num2) {
                strcpy(surname, input);
                count++;
            }
            count++;
        }
        surnameFile.close();
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        r *= 23;
        while (r > 4) {
            r -= 4;
            while (r < 2) {
                r += 1;
            }
        }
        strcpy(newStudent->givenName, givenName);
        strcpy(newStudent->surname, surname);
        newStudent->studentID = currentID;
        newStudent->grade = r;
        if (roster[(currentID) % capacity] == NULL) {
            roster[(currentID % capacity)] = newStudent;
        }
        else {
            if (roster[(currentID) % capacity]->next == NULL) {
                roster[currentID % capacity]->next = newStudent;
            }
            else {
                if (roster[(currentID) % capacity]->next->next == NULL) {
                    roster[currentID % capacity]->next->next = newStudent;
                }
                else {
                    Student** newRoster = new Student*[capacity * 2];
                    resetRoster(newRoster, capacity * 2);
                    roster = rehashRoster(roster, newRoster, capacity, currentID);
                    roster[currentID % capacity]->next = newStudent;
                }
            }
        }
        currentID++;
    }
    return roster;
}

// Function to manually add a student
Student** manAdd(Student** roster, int &currentID, int &capacity) {
    char input[100];
    char givenName[100];
    char surname[100];
    float grade;
    Student* newStudent = new Student();
    cout << "Enter the first name:" << endl;
    cin >> givenName;
    cin.clear();
    cout << "Enter the last name:" << endl;
    cin >> surname;
    cin.clear();
    cout << "Enter the grade:" << endl;
    cin >> grade;
    cin.clear();
    strcpy(newStudent->givenName, givenName);
    strcpy(newStudent->surname, surname);
    newStudent->studentID = currentID;
    newStudent->grade = grade;
    if (roster[(currentID) % capacity] == NULL) {
        roster[(currentID % capacity)] = newStudent;
    }
    else {
        if (roster[(currentID) % capacity]->next == NULL) {
            roster[currentID % capacity]->next = newStudent;
        }
        else {
            if (roster[(currentID) % capacity]->next->next == NULL) {
                roster[currentID % capacity]->next->next = newStudent;
            }
            else {
                Student** newRoster = new Student*[capacity * 2];
                resetRoster(newRoster, capacity * 2);
                roster = rehashRoster(roster, newRoster, capacity, currentID);
                roster[currentID % capacity]->next = newStudent;
            }
        }
    }
    currentID++;
    return roster;
}

// Function to display all students
void displayAll(Student** roster, int capacity) {
    for (int i = 0; i < capacity; i++) {
        printChain(roster[i]);
    }
    return;
}

// Function to display details of a student
void display(Student** roster, int capacity) {
    int i;
    Student* current;
    cout << "Please enter the student ID# you wish to print:" << endl;
    cin >> i;
    cin.clear();
    if (roster[i % capacity] != NULL && roster[i % capacity]->studentID == i) {
        current = roster[i % capacity];
    }
    else if (roster[i % capacity] != NULL && roster[i % capacity]->next != NULL && roster[i % capacity]->next->studentID == i) {
        current = roster[i % capacity]->next;
    }
    else if (roster[i % capacity] != NULL && roster[i % capacity]->next != NULL && roster[i % capacity]->next->next != NULL && roster[i % capacity]->next->next->studentID == i) {
        current = roster[i % capacity]->next->next;
    }
    else {
        cout << "Invalid ID" << endl;
        return;
    }
    cout << "Here are the details:" << endl;
    cout << current->givenName << " " << current->surname << " Grade: " <<  fixed << setprecision(2) << current->grade << " ID: " << current->studentID << endl;
}

// Function to print a chain of students
void printChain(Student* current) {
    if (current != NULL) {
        cout << current->givenName << " " << current->surname << " Grade: " <<  fixed << setprecision(2) << current->grade << " ID: " << current->studentID << endl;
        printChain(current->next);
    }
    return;
}

// Function to eliminate a student
void eliminate(Student** roster, int capacity) {
    int i;
    cout << "Please enter the ID# of the student you wish to remove:" << endl;
    cin >> i;
    cin.clear();
    if (roster[i % capacity]->studentID == i) {
        roster[i % capacity] = roster[i % capacity]->next;
    }
    else if (roster[i % capacity]->next->studentID == i) {
        roster[i % capacity]->next = roster[i % capacity]->next->next;
    }
    else if (roster[i % capacity]->next->next->studentID == i) {
        roster[i % capacity]->next->next = NULL;
    }
    return;
}

// Function to reset the roster
void resetRoster(Student** roster, int capacity) {
    for (int i = 0; i < capacity; i++) {
        roster[i] = NULL;
    }
}

// Function to rehash the roster
Student** rehashRoster(Student** roster, Student** newRoster, int &capacity, int currentID) {
    int oldCapacity = capacity;
    capacity = capacity * 2;
    for (int i = 0; i < currentID; i++) {
        if (i < oldCapacity) {
            newRoster[(i % capacity)] = roster[(i) % oldCapacity];
        }
        else if (i < oldCapacity * 2) {
            newRoster[(i % capacity)] = roster[(i) % oldCapacity]->next;
        }
        else {
            newRoster[i % capacity]->next = roster[(i) % oldCapacity]->next->next;
        }
    }
    for (int i = capacity / 2; i < capacity; i++) {
        newRoster[(i % capacity)]->next = NULL;
    }
    return newRoster;
}

































