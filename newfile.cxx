#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

// Structure to hold student details
struct Student {
    string rollNo;
    string name;
    string course;
    string age;
};

// Function declarations
void addStudent();
void displayAllStudents();
void updateStudent();
void deleteStudent();
void searchStudent();
void displayHeader();

int main() {
    int choice;

    while (true) {
        displayHeader();
        cout << "=========================================\n";
        cout << "        STUDENT MANAGEMENT SYSTEM        \n";
        cout << "=========================================\n";
        cout << "1. Add New Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student by Roll No\n";
        cout << "4. Update Student Record\n";
        cout << "5. Delete Student Record\n";
        cout << "6. Exit\n";
        cout << "-----------------------------------------\n";
        cout << "Enter your choice (1-6): ";
        
        if (!(cin >> choice)) {
            cout << "Invalid input! Please enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        cin.ignore(); // Clear newline character from buffer

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayAllStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6:
                cout << "\nThank you for using Student Management System. Goodbye!\n";
                return 0;
            default:
                cout << "\nInvalid choice! Please try again.\n";
        }
        
        cout << "\nPress Enter to continue...";
        cin.get();
    }
    return 0;
}

// Function to add a student to the file
void addStudent() {
    ofstream outFile("students.txt", ios::app); // Open in append mode
    if (!outFile) {
        cout << "Error opening file for writing!\n";
        return;
    }

    Student s;
    cout << "\n--- Add New Student ---\n";
    cout << "Enter Roll Number: ";
    getline(cin, s.rollNo);
    cout << "Enter Full Name: ";
    getline(cin, s.name);
    cout << "Enter Course/Branch: ";
    getline(cin, s.course);
    cout << "Enter Age: ";
    getline(cin, s.age);

    // Save comma-separated values to file
    outFile << s.rollNo << "," << s.name << "," << s.course << "," << s.age << "\n";
    outFile.close();

    cout << "\nRecord added successfully!\n";
}

// Function to display all students
void displayAllStudents() {
    ifstream inFile("students.txt");
    if (!inFile) {
        cout << "\nNo records found! (File does not exist yet)\n";
        return;
    }

    string line;
    cout << "\n----------------------------------------------------------------------\n";
    cout << left << setw(12) << "Roll No" 
         << setw(25) << "Name" 
         << setw(20) << "Course" 
         << setw(8) << "Age" << endl;
    cout << "----------------------------------------------------------------------\n";

    bool hasRecords = false;
    while (getline(inFile, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        Student s;
        getline(ss, s.rollNo, ',');
        getline(ss, s.name, ',');
        getline(ss, s.course, ',');
        getline(ss, s.age, ',');

        cout << left << setw(12) << s.rollNo 
             << setw(25) << s.name 
             << setw(20) << s.course 
             << setw(8) << s.age << endl;
        hasRecords = true;
    }

    if (!hasRecords) {
        cout << "No records available.\n";
    }
    cout << "----------------------------------------------------------------------\n";
    inFile.close();
}

// Function to search for a specific student
void searchStudent() {
    ifstream inFile("students.txt");
    if (!inFile) {
        cout << "\nNo records found!\n";
        return;
    }

    string searchRoll;
    cout << "\nEnter Roll Number to search: ";
    getline(cin, searchRoll);

    string line;
    bool found = false;

    while (getline(inFile, line)) {
        stringstream ss(line);
        Student s;
        getline(ss, s.rollNo, ',');
        getline(ss, s.name, ',');
        getline(ss, s.course, ',');
        getline(ss, s.age, ',');

        if (s.rollNo == searchRoll) {
            cout << "\n--- Student Found ---\n";
            cout << "Roll No : " << s.rollNo << endl;
            cout << "Name    : " << s.name << endl;
            cout << "Course  : " << s.course << endl;
            cout << "Age     : " << s.age << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nStudent with Roll Number " << searchRoll << " not found.\n";
    }
    inFile.close();
}

// Function to update a student's information
void updateStudent() {
    ifstream inFile("students.txt");
    if (!inFile) {
        cout << "\nNo records found!\n";
        return;
    }

    string updateRoll;
    cout << "\nEnter Roll Number to update: ";
    getline(cin, updateRoll);

    ofstream tempFile("temp.txt"); // Temporary file to write updated data
    string line;
    bool found = false;

    while (getline(inFile, line)) {
        stringstream ss(line);
        Student s;
        getline(ss, s.rollNo, ',');
        getline(ss, s.name, ',');
        getline(ss, s.course, ',');
        getline(ss, s.age, ',');

        if (s.rollNo == updateRoll) {
            found = true;
            cout << "\n--- Current Details ---\n";
            cout << "Name: " << s.name << " | Course: " << s.course << " | Age: " << s.age << endl;
            cout << "-------------------------\n";
            
            cout << "Enter New Name (or press Enter to keep current): ";
            string newName;
            getline(cin, newName);
            if (!newName.empty()) s.name = newName;

            cout << "Enter New Course (or press Enter to keep current): ";
            string newCourse;
            getline(cin, newCourse);
            if (!newCourse.empty()) s.course = newCourse;

            cout << "Enter New Age (or press Enter to keep current): ";
            string newAge;
            getline(cin, newAge);
            if (!newAge.empty()) s.age = newAge;
        }
        
        // Write (either original or updated) record to temp file
        tempFile << s.rollNo << "," << s.name << "," << s.course << "," << s.age << "\n";
    }

    inFile.close();
    tempFile.close();

    // Replace original file with temporary file
    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found) {
        cout << "\nRecord updated successfully!\n";
    } else {
        cout << "\nStudent with Roll Number " << updateRoll << " not found.\n";
    }
}

// Function to delete a student record
void deleteStudent() {
    ifstream inFile("students.txt");
    if (!inFile) {
        cout << "\nNo records found!\n";
        return;
    }

    string deleteRoll;
    cout << "\nEnter Roll Number to delete: ";
    getline(cin, deleteRoll);

    ofstream tempFile("temp.txt");
    string line;
    bool found = false;

    while (getline(inFile, line)) {
        stringstream ss(line);
        Student s;
        getline(ss, s.rollNo, ',');
        getline(ss, s.name, ',');
        getline(ss, s.course, ',');
        getline(ss, s.age, ',');

        // If it matches, skip writing it to the temporary file
        if (s.rollNo == deleteRoll) {
            found = true;
            continue; 
        }

        tempFile << s.rollNo << "," << s.name << "," << s.course << "," << s.age << "\n";
    }

    inFile.close();
    tempFile.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found) {
        cout << "\nRecord deleted successfully!\n";
    } else {
        cout << "\nStudent with Roll Number " << deleteRoll << " not found.\n";
    }
}

// Utility function to clear screen space between menus
void displayHeader() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}