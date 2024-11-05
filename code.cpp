#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

const int TOTAL_CLASSES = 50;  // Total classes held (fixed)
const int NUM_SUBJECTS = 5;    // Number of subjects

class Student {
private:
    string name;                // Student's name
    string parentage;          // Parent's name
    string reg_no;             // Registration number
    int age;                   // Age of the student
    int semester;              // Current semester
    int roll_number;           // Roll number
    int classes_attended;      // Number of classes attended out of TOTAL_CLASSES
    float marks[NUM_SUBJECTS]; // Marks in subjects

public:
    void getDetails() {
        cout << "Enter student's name: ";
        getline(cin, name);

        cout << "Enter parent's name: ";
        getline(cin, parentage);

        cout << "Enter registration number: ";
        getline(cin, reg_no);

        cout << "Enter student's age: ";
        cin >> age;

        cout << "Enter semester: ";
        cin >> semester;

        cout << "Enter roll number: ";
        cin >> roll_number;

        cout << "Enter number of classes attended (out of " << TOTAL_CLASSES << "): ";
        cin >> classes_attended;

        cout << "Enter marks for " << NUM_SUBJECTS << " subjects:\n";
        for (int i = 0; i < NUM_SUBJECTS; ++i) {
            cout << "Subject " << i + 1 << ": ";
            cin >> marks[i];
        }
        cin.ignore();  // Ignore the newline character
    }

    void showDetails() const {
        cout << "\nDetails for Roll No: " << roll_number << endl;
        cout << "Name: " << name << endl;
        cout << "Parentage: " << parentage << endl;
        cout << "Registration Number: " << reg_no << endl;
        cout << "Age: " << age << endl;
        cout << "Semester: " << semester << endl;
        cout << "Classes Attended: " << classes_attended << "/" << TOTAL_CLASSES << endl;
        cout << "Marks: ";
        for (int i = 0; i < NUM_SUBJECTS; ++i) {
            cout << marks[i] << " ";
        }
        cout << endl;
    }

    float getAttendancePercentage() const {
        return (float)classes_attended / TOTAL_CLASSES * 100;
    }

    void printAttendance() const {
        cout << "Roll No: " << roll_number << ", Name: " << name << ", Attendance: " << getAttendancePercentage() << "%\n";
    }

    bool hasAttendanceShortage() const {
        return getAttendancePercentage() < 75;
    }

    float getAverageMarks() const {
        float totalMarks = 0;
        for (int i = 0; i < NUM_SUBJECTS; ++i) {
            totalMarks += marks[i];
        }
        return totalMarks / NUM_SUBJECTS;
    }

    bool hasHighAverageMarks() const {
        return getAverageMarks() >= 90;
    }

    int getRollNumber() const { return roll_number; }
    string getName() const { return name; }
};

// Function to display top 5 students based on average marks
void showTop5(Student students[], int n) {
    sort(students, students + n, [](const Student &a, const Student &b) {
        return a.getAverageMarks() > b.getAverageMarks();
    });

    cout << "\nTop 5 Students (by average marks):\n";
    for (int i = 0; i < 5 && i < n; ++i) {
        cout << "Roll No: " << students[i].getRollNumber() << ", Name: " << students[i].getName()
             << ", Average Marks: " << students[i].getAverageMarks() << endl;
    }
}

int main() {
    int n;

    cout << "Enter number of students: ";
    cin >> n;
    cin.ignore();  // Ignore the newline character

    Student students[100];  // Array to store student data

    for (int i = 0; i < n; ++i) {
        cout << "\nEnter details for student " << i + 1 << ":\n";
        students[i].getDetails();
    }

    cout << "\nDetails of all students:\n";
    for (int i = 0; i < n; ++i) {
        students[i].showDetails();
    }

    cout << "\nAttendance of all students:\n";
    for (int i = 0; i < n; ++i) {
        students[i].printAttendance();
    }

    cout << "\nStudents with attendance shortage (< 75%):\n";
    bool shortage = false;
    for (int i = 0; i < n; ++i) {
        if (students[i].hasAttendanceShortage()) {
            cout << "Roll No: " << students[i].getRollNumber() << ", Name: " << students[i].getName() << endl;
            shortage = true;
        }
    }
    if (!shortage) {
        cout << "No students with attendance shortage.\n";
    }

    showTop5(students, n);

    cout << "\nStudents with 90% or more average marks:\n";
    bool highAverage = false;
    for (int i = 0; i < n; ++i) {
        if (students[i].hasHighAverageMarks()) {
            cout << "Roll No: " << students[i].getRollNumber() << ", Name: " << students[i].getName()
                 << ", Average Marks: " << students[i].getAverageMarks() << endl;
            highAverage = true;
        }
    }
    if (!highAverage) {
        cout << "No students with 90% or more average marks.\n";
    }

    return 0;
}