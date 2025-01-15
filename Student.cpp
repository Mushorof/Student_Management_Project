#include <bits/stdc++.h>
#include<windows.h>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

class StudentManagement {
private:
    string name, phone, dept, IDNo;
    int age;
    double cgpa;

public:
    void setData() {
        cout << "\t\tEnter matrix ID: ";
        cin >> IDNo;
        cout << "\t\tEnter name: ";
        cin.ignore();
        getline(cin, name);
        cout << "\t\tEnter age: ";
        cin >> age;
        cout << "\t\tEnter CGPA: ";
        cin >> cgpa;
        cout << "\t\tEnter contact number: ";
        cin >> phone;
        cout << "\t\tEnter Department: ";
        cin >> dept;
    }

    void display() {
        cout << "ID NO\t\t: " << IDNo << endl;
        cout << "Name\t\t: " << name << endl;
        cout << "Age\t\t: " << age << " years" << endl;
        cout << "CGPA\t\t: " << fixed << setprecision(2) << cgpa << endl;
        cout << "Contact NO.\t: " << phone << endl;
        cout << "Department\t: " << dept << endl;
    }

    void writeOnFile() {
        ofstream outFile("Student_Record.txt", ios::app);
        if (!outFile) {
            cout << "\t\tError opening file for writing!\n";
            return;
        }

        char ch;
        do {
            cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
            cout << "------------------------------------- Add Student Details ---------------------------------------------" << endl;
            setData();
            outFile << IDNo << '|' << name << '|' << age << '|' << cgpa << '|' << phone << '|' << dept << '\n';
            cout << "\t\tDo you have next data?(y/n)";
            cin >> ch;
        } while (ch == 'y');

        cout << "\t\t\tStudent data has been successfully added...";
        outFile.close();
    }

    void readFromFile() {
        ifstream inFile("Student_Record.txt");
        if (!inFile || inFile.peek() == EOF) {
            cout << "\t\t\tNo data found...!\n";
            return;
        }

        cout << "\n\t\t================================\n";
        cout << "\t\t||| LIST OF STUDENTS |||";
        cout << "\n\t\t================================\n\n";

        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            getline(ss, IDNo, '|');
            getline(ss, name, '|');
            ss >> age;
            ss.ignore();
            ss >> cgpa;
            ss.ignore();
            getline(ss, phone, '|');
            getline(ss, dept, '\n');
            display();
            cout << "\n\t\t================================\n";
        }

        inFile.close();
    }

    void search() {
        ifstream inFile("Student_Record.txt");
        if (!inFile) {
            cout << "\t\t\tError opening file for reading!\n";
            return;
        }

        string ID;
        cout << "Enter matrix ID: ";
        cin >> ID;

        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            getline(ss, IDNo, '|');
            getline(ss, name, '|');
            ss >> age;
            ss.ignore();
            ss >> cgpa;
            ss.ignore();
            getline(ss, phone, '|');
            getline(ss, dept, '\n');

            if (ID == IDNo) {
                display();
                inFile.close();
                return;
            }
        }

        cout << "\n\n\t\t\tNo record found.";
        inFile.close();
    }

    void deleteFromFile() {
        ifstream inFile("Student_Record.txt");
        ofstream outFile("temp.txt");
        if (!inFile || !outFile) {
            cout << "\t\t\tError opening files!\n";
            return;
        }

        string num;
        bool flag = false;
        cout << "\t\t\tEnter matrix ID to delete: ";
        cin >> num;

        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            getline(ss, IDNo, '|');

            if (IDNo != num) {
                outFile << line << '\n';
            } else {
                flag = true;
            }
        }

        inFile.close();
        outFile.close();
        remove("Student_Record.txt");
        rename("temp.txt", "Student_Record.txt");

        if (flag) {
            cout << "\n\n\t\t\tStudent record has been successfully deleted...!";
        } else {
            cout << "\n\n\t\t\tStudent not found...!";
        }
    }

    void update() {
        ifstream inFile("Student_Record.txt");
        ofstream outFile("temp.txt");
        if (!inFile || !outFile) {
            cout << "\t\t\tError opening files!\n";
            return;
        }

        string IDinput;
        cout << "\n-------------------------------------------------------------------------------------------------------";
        cout << "------------------------------------- Update Student Details ---------------------------------------------\n" << endl;
        cout << "\t\tEnter matrix ID to be updated: ";
        cin >> IDinput;

        bool flag = false;
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            getline(ss, IDNo, '|');

            if (IDNo == IDinput) {
                cout << "Enter new record\n";
                setData();
                outFile << IDNo << '|' << name << '|' << age << '|' << cgpa << '|' << phone << '|' << dept << '\n';
                flag = true;
            } else {
                outFile << line << '\n';
            }
        }

        inFile.close();
        outFile.close();
        remove("Student_Record.txt");
        rename("temp.txt", "Student_Record.txt");

        if (flag) {
            cout << "\n\n\t\t\tStudent record has been successfully updated...!";
        } else {
            cout << "\n\n\t\t\tNo record found...!";
        }
    }
};

int main() {
    system("cls");
    while (1) {
        StudentManagement sm;
        int choice;

        system("cls");
        cout << "\n\t\t===================================";
        cout << "\n\t\t*| Student Management System |*";
        cout << "\n\t\t=======(By: Group[F])=======\n";
        cout << "\n\t\t===================================";
        cout << "\n\t\t----- WELCOME TO MAIN SYSTEM ------";
        cout << "\n\t\t===================================\n";
        cout << "\t\t[1] Add New Record\n";
        cout << "\t\t[2] Display Record\n";
        cout << "\t\t[3] Search Record\n";
        cout << "\t\t[4] Delete Record\n";
        cout << "\t\t[5] Update Record\n";
        cout << "\t\t[0] Exit\n";
        cout << "\n\t\tEnter your choice: ";
        cin >> choice;
        system("cls");

        switch (choice) {
        case 1:
            system("cls");
            sm.writeOnFile();
            break;

        case 2:
            system("cls");
            sm.readFromFile();
            break;

        case 3:
            system("cls");
            sm.search();
            break;

        case 4:
            system("cls");
            sm.deleteFromFile();
            break;

        case 5:
            system("cls");
            sm.update();
            break;

        case 0:
            system("cls");
            cout << "\n\n\n\t\t\tThank you for using our system." << endl << endl;
            exit(0);
            break;

        default:
            continue;
        }

        int opt;
        cout << "\n\n==>>Enter your choice:\n[1] System\t\t[0] Exit\n";
        cin >> opt;
        switch (opt) {
        case 0:
            system("cls");
            cout << "\n\n\n\t\t\tThank you for using our system." << endl << endl;
            exit(0);
            break;

        default:
            continue;
        }
    }

    return 0;
}
