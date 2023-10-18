#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int MAX_STUDENTS = 100;
const int MAX_ASSIGNMENTS = 50;

struct Assignment {
    string name;
    int score;
};

struct Student {
    string name;
    Assignment assignments[MAX_ASSIGNMENTS];
};

struct Teacher {
    string name;
};

void displayMainMenu() {
    cout << "1. Student Login\n";
    cout << "2. Teacher Login\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
}

void studentMenu(Student& student) {
    int choice;
    do {
        cout << "\nStudent Menu\n";
        cout << "1. View Assignments\n";
        cout << "2. Submit Assignment\n";
        cout << "3. Change Information\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Assignments:\n";
                for (const Assignment& assignment : student.assignments) {
                    if (!assignment.name.empty()) {
                        cout << assignment.name << ": " << assignment.score << "\n";
                    }
                }
                break;
            case 2:
                cout << "Enter assignment name: ";
                cin >> ws; // To consume the newline character left in the buffer
                getline(cin, student.assignments[0].name);
                cout << "Enter assignment score: ";
                cin >> student.assignments[0].score;
                cout << "Assignment submitted successfully!\n";
                break;
            case 3:
                cout << "Enter new student name: ";
                cin >> ws;
                getline(cin, student.name);
                cout << "Information updated successfully!\n";
                break;
            case 4:
                cout << "Exiting student menu.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);
}

void teacherMenu(Student students[], int studentCount) {
    string assignmentName;  // Move declaration outside the switch
    string studentName;     // Move declaration outside the switch
    int choice;

    do {
        cout << "\nTeacher Menu\n";
        cout << "1. Assign Tasks\n";
        cout << "2. Grade Students\n";
        cout << "3. Add/Edit Student Information\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter assignment name: ";
                cin >> ws;
                getline(cin, assignmentName);

                for (int i = 0; i < studentCount; ++i) {
                    students[i].assignments[0].name = assignmentName;
                    students[i].assignments[0].score = -1; // Set an initial score, indicating not graded yet
                }

                cout << "Assignment assigned successfully!\n";
                break;
            case 2:
                cout << "Enter assignment name to grade: ";
                cin >> ws;
                getline(cin, assignmentName);

                for (int i = 0; i < studentCount; ++i) {
                    if (students[i].assignments[0].name == assignmentName) {
                        cout << "Enter grade for " << students[i].name << ": ";
                        cin >> students[i].assignments[0].score;
                    }
                }

                cout << "Grades updated successfully!\n";
                break;
            case 3:
                cout << "Enter student name to add/edit information: ";
                cin >> ws;
                getline(cin, studentName);

                for (int i = 0; i < studentCount; ++i) {
                    if (students[i].name == studentName) {
                        cout << "Enter new student name: ";
                        getline(cin, students[i].name);
                        cout << "Student information updated successfully!\n";
                        break;
                    }
                }

                cout << "Student not found.\n";
                break;
            case 4:
                cout << "Exiting teacher menu.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);
}

int main() {
    Student students[MAX_STUDENTS];
    Teacher teacher;

    // Initialize sample data
    students[0].name = "Student1";
    students[1].name = "Student2";
    teacher.name = "Teacher";

    int studentCount = 2; // Number of students

    int mainChoice;
    do {
        displayMainMenu();
        cin >> mainChoice;

        switch (mainChoice) {
            case 1:
                int studentIndex;
                cout << "Enter student index (0-" << studentCount - 1 << "): ";
                cin >> studentIndex;

                if (studentIndex >= 0 && studentIndex < studentCount) {
                    studentMenu(students[studentIndex]);
                } else {
                    cout << "Invalid student index.\n";
                }
                break;
            case 2:
                teacherMenu(students, studentCount);
                break;
            case 3:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (mainChoice != 3);

    return 0;
}
