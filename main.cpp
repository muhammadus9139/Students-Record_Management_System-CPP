#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdexcept>
using namespace std;


struct Student {
    int rollNo;
    string name;
    string gender;
    int age;
    float cgpa;
    char grade;
    string city;
    string mobile;
    float marks1, marks2, marks3;
    float totalMarks;
};


Student students[100]; 
int studentCount = 0;

// Function prototypes
void displayMenu();
void addStudent();
void displayAllStudents();
void saveToFile();
void loadFromFile();
void searchByName();
void deleteByRollNo();
void updateByMobile();
char calculateGrade(float totalMarks);

int main() {
    cout << "Welcome to student management system" << endl;
    int choice;
    do {
        displayMenu();
        cout << "Enter your choice: ";

        try {
            cin >> choice;
            if (choice<0&&choice>8)
            {
                throw choice;
            }
            switch(choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayAllStudents();
                break;
            case 3:
                saveToFile();
                break;
            case 4:
                loadFromFile();
                break;
            case 5:
                searchByName();
                break;
            case 6:
                deleteByRollNo();
                break;
            case 7:
                updateByMobile();
                break;
            case 0:
                cout << "Exiting... Thank you!" << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
            }

            if(choice != 0) {
                cout << "---------------------------------------------------" << endl;
            }

        } catch (int exp) {
            cout <<"Invalid input"<< endl;
            cin.clear();
        }

    } while(choice != 0);

    return 0;
}

void displayMenu() {
    cout << "\n1. Add New Student Record" << endl;
    cout << "2. Display All Student Records" << endl;
    cout << "3. Save Records to File" << endl;
    cout << "4. Load Records from File" << endl;
    cout << "5. Search Student by Name" << endl;
    cout << "6. Delete Record by Roll No" << endl;
    cout << "7. Update Record by Mobile No" << endl;
    cout << "0. Exit" << endl;
    cout << "---------------------------------------------------" << endl;
}

void addStudent() {
    try {
        if(studentCount >= 100) {
            throw runtime_error("Cannot add more students. Maximum limit reached!");
        }

        cout << "Enter Roll No: ";
        if (!(cin >> students[studentCount].rollNo)) {
            throw runtime_error("Invalid input for Roll No. Please enter a number.");
        }

      
        for(int i = 0; i < studentCount; i++) {
            if(students[i].rollNo == students[studentCount].rollNo) {
                throw runtime_error("Roll number already exists!");
            }
        }

        cin.ignore(); 

        cout << "Name: ";
        getline(cin, students[studentCount].name);
        if (students[studentCount].name.empty()) {
            throw runtime_error("Name cannot be empty.");
        }

        cout << "Gender: ";
        getline(cin, students[studentCount].gender);
        if (students[studentCount].gender.empty()) {
            throw runtime_error("Gender cannot be empty.");
        }

        cout << "Age: ";
        if (!(cin >> students[studentCount].age)) {
            throw runtime_error("Invalid input for Age. Please enter a number.");
        }

        if(students[studentCount].age < 0) {
            throw runtime_error("Negative values are not allowed for Age.");
        }

        cout << "CGPA: ";
        if (!(cin >> students[studentCount].cgpa)) {
            throw runtime_error("Invalid input for CGPA. Please enter a number.");
        }

        if(students[studentCount].cgpa < 0 || students[studentCount].cgpa > 4.0) {
            throw runtime_error("CGPA must be between 0 and 4.0.");
        }

        cin.ignore(); 

        cout << "City: ";
        getline(cin, students[studentCount].city);
        if (students[studentCount].city.empty()) {
            throw runtime_error("City cannot be empty.");
        }

        cout << "Mobile: ";
        getline(cin, students[studentCount].mobile);
        if (students[studentCount].mobile.empty()) {
            throw runtime_error("Mobile number cannot be empty.");
        }

        cout << "Marks in Subject 1: ";
        if (!(cin >> students[studentCount].marks1)) {
            throw runtime_error("Invalid input for Marks 1. Please enter a number.");
        }

        if(students[studentCount].marks1 < 0 || students[studentCount].marks1 > 100) {
            throw runtime_error("Marks must be between 0 and 100.");
        }

        cout << "Marks in Subject 2: ";
        if (!(cin >> students[studentCount].marks2)) {
            throw runtime_error("Invalid input for Marks 2. Please enter a number.");
        }

        if(students[studentCount].marks2 < 0 || students[studentCount].marks2 > 100) {
            throw runtime_error("Marks must be between 0 and 100.");
        }

        cout << "Marks in Subject 3: ";
        if (!(cin >> students[studentCount].marks3)) {
            throw runtime_error("Invalid input for Marks 3. Please enter a number.");
        }

        if(students[studentCount].marks3 < 0 || students[studentCount].marks3 > 100) {
            throw runtime_error("Marks must be between 0 and 100.");
        }

       
        students[studentCount].totalMarks = students[studentCount].marks1 +
                                            students[studentCount].marks2 +
                                            students[studentCount].marks3;
        students[studentCount].grade = calculateGrade(students[studentCount].totalMarks);

        studentCount++;
        cout << "Student added successfully." << endl;

    } catch (const exception& e) {
        cout << "Error adding student: " << e.what() << endl;
        cin.clear();

    }
}

void displayAllStudents() {
    try {
        if(studentCount == 0) {
            throw studentCount;
        }

        cout << "\n--- Student Records ---" << endl;
        for(int i = 0; i < studentCount; i++) {
            cout << "\nRoll No: " << students[i].rollNo << endl;
            cout << "Name: " << students[i].name << endl;
            cout << "Gender: " << students[i].gender << endl;
            cout << "Age: " << students[i].age << endl;
            cout << "CGPA: " << fixed << setprecision(2) << students[i].cgpa << endl;
            cout << "Total Marks: " << students[i].totalMarks << endl;
            cout << "Grade: " << students[i].grade << endl;
            cout << "City: " << students[i].city << endl;
            cout << "Mobile: " << students[i].mobile << endl;
        }
    } catch (int exp) {
        cout << "Error no record available " << endl;
    }
}

void saveToFile() {
    try {
        ofstream file("students.txt");
        if(!file.is_open()) {
            throw runtime_error("Unable to open file for writing.");
        }

        for(int i = 0; i < studentCount; i++) {
            file <<"Roll no: "<< students[i].rollNo <<endl
                 <<"Name: "<< students[i].name <<endl
                 <<"Gender: "<< students[i].gender <<endl
                 <<"Age:"<< students[i].age <<endl
                 <<"Cgpa:" <<students[i].cgpa <<endl
                 <<"Grade: "<< students[i].grade <<endl
                 <<"City: "<< students[i].city <<endl
                 <<"Mobile: "<< students[i].mobile <<endl
                 <<"Marks 1: "<< students[i].marks1 <<endl
                 <<"Marks 2: "<< students[i].marks2 <<endl
                 <<"Marks 3: "<< students[i].marks3 <<endl
                 <<"Total marks: "<< students[i].totalMarks<<endl<<endl;
        }

        file.close();
        cout << "Records saved to file successfully." << endl;
    } catch (const exception& e) {
        cout << "Error saving to file: " << e.what() << endl;
    }
}

void loadFromFile() {
    try {
        ifstream file("students.txt");
        if(!file.is_open()) {
            throw runtime_error("Unable to open file for reading.");
        }

        studentCount = 0; 
        cout<<endl<<"File content"<<endl;
        string line;
        while(getline(file,line))
        {
            cout<<line<<endl;

            studentCount++;

            if(studentCount >= 100)
                break; 
        }
        file.close();
     cout << "Records loaded from file successfully"<< endl;
    } catch (const exception& e) {
        cout << "Error loading from file: " << e.what() << endl;
    }
}

void searchByName() {
    try {
        if(studentCount == 0) {
            throw runtime_error("No student records available.");
        }

        cin.ignore();
        string searchName;
        cout << "Enter name to search: ";
        getline(cin, searchName);

        if (searchName.empty()) {
            throw runtime_error("Search name cannot be empty.");
        }

        bool found = false;
        for(int i = 0; i < studentCount; i++) {
            if(students[i].name == searchName) {
                cout << "\nRecord Found:" << endl;
                cout << "Roll No: " << students[i].rollNo << endl;
                cout << "Name: " << students[i].name << endl;
                cout << "Gender: " << students[i].gender << endl;
                cout << "Age: " << students[i].age << endl;
                cout << "CGPA: " << fixed << setprecision(2) << students[i].cgpa << endl;
                cout << "Total Marks: " << students[i].totalMarks << endl;
                cout << "Grade: " << students[i].grade << endl;
                cout << "City: " << students[i].city << endl;
                cout << "Mobile: " << students[i].mobile << endl;
                found = true;
                break;
            }
        }

        if(!found) {
            throw runtime_error("Student not found.");
        }
    } catch (const exception& e) {
        cout << "Error searching by name: " << e.what() << endl;
    }
}

void deleteByRollNo() {
    try {
        if(studentCount == 0) {
            throw runtime_error("No student records available.");
        }

        int rollNo;
        cout << "Enter Roll No to delete: ";
        if (!(cin >> rollNo)) {
            throw runtime_error("Invalid input for Roll No. Please enter a number.");
        }

        bool found=false;
        int index = -1;
        for(int i = 0; i < studentCount; i++) {
            if(students[i].rollNo == rollNo) {
                index = i;
                found=true;
                break;
            }
        }

        if(index != -1) {
            
            for(int i = index; i < studentCount - 1; i++) {
                students[i] = students[i + 1];
            }
            studentCount--;
            cout << "Record deleted successfully." << endl;
        }

        if(!found)
        {
            throw runtime_error("Roll no not found");
        }

    } catch (const exception& e) {
        cout << "Error deleting by roll number: " << e.what() << endl;
        cin.clear();

    }
}

void updateByMobile() {
    try {
        if(studentCount == 0) {
            throw runtime_error("No student records available.");
        }

        cin.ignore(); 
        string mobile;
        cout << "Enter mobile number to update: ";
        getline(cin, mobile);

        if (mobile.empty()) {
            throw runtime_error("Mobile number cannot be empty.");
        }

        bool found = false;
        for(int i = 0; i < studentCount; i++) {
            if(students[i].mobile == mobile) {
                cout << "Enter new city: ";
                getline(cin, students[i].city);
                if (students[i].city.empty()) {
                    throw runtime_error("City cannot be empty.");
                }
                cout << "Record updated successfully." << endl;
                found = true;
                break;
            }
        }

        if(!found) {
            throw runtime_error("Student with specified mobile number not found.");
        }
    } catch (const exception& e) {
        cout << "Error updating by mobile: " << e.what() << endl;
    }
}

char calculateGrade(float totalMarks) {
    try {
        if (totalMarks < 0 || totalMarks > 300) {
            throw totalMarks;
        }

        if(totalMarks >= 270) return 'A';      
        else if(totalMarks >= 240) return 'B'; 
        else if(totalMarks >= 210) return 'C'; 
        else if(totalMarks >= 180) return 'D'; 
        else return 'F';                       
    } catch (int exp) {
        cout << "Invalid total marks";
    }
}

