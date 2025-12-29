// This program reads a binary file,
// updates grades previously written to the file,
// adds new grades in the file,
// and deletes data previously stored in the file.

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
using namespace std;

struct StudentData
{
    char studentId[8];
    char lastName[12];
    char firstName[12];
    int grade;
};

enum class Choices { PRINT = 1, UPDATE, NEW, DELETE, END };

// enable user to input menu choice
Choices enterChoice();

// create text file for printing
void createTextFile(fstream& readFromFile);

// update grade in record
void updateRecord(fstream& updateFile);

// add a new grade in record
void newRecord(fstream& insertInFile);

// delete an existing record
void deleteRecord(fstream& deleteFromFile);

// obtain student ID from user
void getID(const char* const prompt, char studentId[]);

int main()
{
    // open file for reading and writing
    fstream inOutGrade("grades.dat", ios::in | ios::out | ios::binary);

    // exit program if fstream cannot open file
    if (!inOutGrade)
    {
        cerr << "File could not be opened." << endl;
        system("pause");
        exit(1);
    }

    Choices choice; // store user choice

    // enable user to specify action
    while ((choice = enterChoice()) != Choices::END)
    {
        switch (choice)
        {
        case Choices::PRINT:
            createTextFile(inOutGrade); // create text file from binary file
            break;
        case Choices::UPDATE:
            updateRecord(inOutGrade); // update grade
            break;
        case Choices::NEW:
            newRecord(inOutGrade); // add a new grade
            break;
        case Choices::DELETE:
            deleteRecord(inOutGrade); // delete existing record
            break;
        default:
            cerr << "Incorrect choice" << endl;
            break;
        }






        cout << endl;
    }

    inOutGrade.close();

    system("pause");
}

// enable user to input menu choice
Choices enterChoice()
{
    // display available options
    cout << "Enter your choice" << endl
        << "1 - store a text file of all students' information" << endl
        << "    called \"grades.txt\" for printing" << endl
        << "2 - update a student's grade" << endl
        << "3 - add a student's grade" << endl
        << "4 - delete a student's information" << endl
        << "5 - end program\n? ";

    int menuChoice;
    cin >> menuChoice;
    return static_cast<Choices>(menuChoice);
}

// create text file for printing
void createTextFile(fstream& readFromFile)
{
    StudentData stu;
    ofstream out("grade.txt");
    readFromFile.clear();
    readFromFile.seekg(0, ios::beg);

    cout << endl;
    cout << left << setw(9) << "ID";
    cout << left << setw(12) << "Last Name";
    cout << left << setw(13) << "First Name";
    cout << right << setw(5) << "Grade" << endl;

    out << left << setw(9) << "ID";
    out << left << setw(12) << "Last Name";
    out << left << setw(13) << "First Name";
    out << right << setw(5) << "Grade" << endl;

    while (readFromFile.read((char*)&stu, sizeof(StudentData))) {
        cout << left << setw(9) << stu.studentId;
        cout << left << setw(12) << stu.lastName;
        cout << left << setw(13) << stu.firstName;
        cout << right << setw(5) << stu.grade << endl;
        out << left << setw(9) << stu.studentId;
        out << left << setw(12) << stu.lastName;
        out << left << setw(13) << stu.firstName;
        out << right << setw(5) << stu.grade << endl;
    }
    out.close();

}

// update grade in record
void updateRecord(fstream& updateFile)
{
    char studentId[8];
    getID("\nEnter student ID to update", studentId);
    StudentData stu;
    bool found = false;
    updateFile.clear();
    updateFile.seekg(0, ios::beg);
    while (updateFile.read((char*)&stu, sizeof(StudentData))) {
        if (!strcmp(stu.studentId, studentId)) {
            found = true;
            if (stu.grade == -1) {
                cout << endl;
                cout << "Student ID ";
                cout << stu.studentId;
                cout << " has no grade." << endl;
            }
            else {
                cout << endl;
                cout << left << setw(9) << stu.studentId;
                cout << left << setw(12) << stu.lastName;
                cout << left << setw(13) << stu.firstName;
                cout << right << setw(5) << stu.grade << endl<<endl;
                cout << "Enter grade: ";
                int grade;
                cin >> grade;
                stu.grade = grade;
                updateFile.seekp(-static_cast<int>(sizeof(StudentData)), ios::cur);
                updateFile.write((char*)&stu, sizeof(StudentData));
                cout << endl;
                cout << left << setw(9) << stu.studentId;
                cout << left << setw(12) << stu.lastName;
                cout << left << setw(13) << stu.firstName;
                cout << right << setw(5) << stu.grade << endl;
            }
            break;
        }
    }
    if (!found) {
        cout << endl;
        cout << "Student ID ";
        cout << studentId;
        cout << " is empty." << endl;
    }
}

// add a new grade in record
void newRecord(fstream& insertInFile)
{
    char studentId[8];
    getID("\nEnter student ID to add", studentId);
    StudentData stu;
    bool found = false;
    insertInFile.clear();
    insertInFile.seekg(0, ios::beg);
    while (insertInFile.read((char*)&stu, sizeof(StudentData))) {
        if (!strcmp(stu.studentId, studentId)) {
            found = true;
            cout << "\nEnter grade: ";
            int grade;
            cin >> grade;
            stu.grade = grade;
            insertInFile.seekp(-static_cast<int>(sizeof(StudentData)), ios::cur);
            insertInFile.write((char*)&stu, sizeof(StudentData));
            cout << endl;
            cout << left << setw(9) << stu.studentId;
            cout << left << setw(12) << stu.lastName;
            cout << left << setw(13) << stu.firstName;
            cout << right << setw(5) << stu.grade << endl;
            break;
        }
    }
    if (!found) {
        cout << endl;
        cout << "Student ID ";
        cout << studentId;
        cout << " is empty." << endl;
    }
}

// delete an existing record
void deleteRecord(fstream& deleteFromFile)
{
    char studentId[8];
    getID("\nEnter student ID to delete", studentId);

    ofstream temp("temp.dat", ios::out | ios::binary);
    StudentData stu;
    bool found = false;
    deleteFromFile.clear();
    deleteFromFile.seekg(0, ios::beg);
    while (deleteFromFile.read((char*)&stu, sizeof(StudentData))) {
        if (strcmp(stu.studentId, studentId)) {
            temp.write((char*)&stu, sizeof(StudentData));
        }
        else {
            found = true;
            cout << endl;
            cout << "Student ID ";
            cout << studentId;
            cout << " deleted." << endl;
        }
    }
    deleteFromFile.close();
    temp.close();
    if (found) {
        if (remove("grades.dat") != 0) {
            cout << "刪除原檔失敗 (可能被佔用)" << endl;
        }
        else if (rename("temp.dat", "grades.dat") != 0) {
            cout << "改名失敗" << endl;
        }
    }
    else {
        cout << endl;
        cout << "Student ID ";
        cout << studentId;
        cout << " is empty." << endl;
        remove("temp.dat");
    }
    deleteFromFile.open("grades.dat", ios::in | ios::out | ios::binary);
}

// obtain student ID from user
void getID(const char* const prompt, char studentId[])
{
    do
    {
        cout << prompt << " ( 1141401 - 1141450 ): ";
        /*cin.getline(studentId, 20);*/
        cin >> studentId;
    } while (strcmp(studentId, "1141401") == -1 || strcmp(studentId, "1141450") == 1);
}
