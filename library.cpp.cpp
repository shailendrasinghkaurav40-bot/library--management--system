#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class Library {
private:
    int id;
    string name, author, student;
    int price, pages;
    string status;
    string issue_date;
    string return_date;

public:
    void addBook() {
        ofstream file("books.txt", ios::app);

        cout << "Enter Book ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Book Name: ";
        getline(cin, name);

        cout << "Enter Author Name: ";
        getline(cin, author);

        cout << "Enter Book Price: ";
        cin >> price;

        cout << "Enter Book Pages: ";
        cin >> pages;

        status = "Available";
        student = "-";
        issue_date = "-";
        return_date = "-";

        file << id << "," << name << "," << author << ","
             << price << "," << pages << ","
             << status << "," << student << ","
             << issue_date << "," << return_date << endl;

        file.close();

        cout << "Book Added Successfully!\n";
    }

    void displayBooks() {
        ifstream file("books.txt");
        string line;

        cout << "\n===== Book Details =====\n";
        while (getline(file, line)) {
            stringstream ss(line);
            string data[9];

            for (int i = 0; i < 9; i++) {
                getline(ss, data[i], ',');
            }

            cout << "\nID: " << data[0];
            cout << "\nName: " << data[1];
            cout << "\nAuthor: " << data[2];
            cout << "\nPrice: " << data[3];
            cout << "\nPages: " << data[4];
            cout << "\nStatus: " << data[5];
            cout << "\nStudent: " << data[6];
            cout << "\nIssue Date: " << data[7];
            cout << "\nReturn Date: " << data[8];
            cout << "\n--------------------------\n";
        }
        file.close();
    }

    void issueBook() {
        ifstream file("books.txt");
        ofstream temp("temp.txt");

        int searchId;
        cout << "Enter Book ID to Issue: ";
        cin >> searchId;
        cin.ignore();

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string data[9];

            for (int i = 0; i < 9; i++) {
                getline(ss, data[i], ',');
            }

            if (stoi(data[0]) == searchId && data[5] == "Available") {
                cout << "Enter Student Name: ";
                getline(cin, data[6]);

                cout << "Enter Issue Date: ";
                getline(cin, data[7]);

                data[5] = "Issued";
                cout << "Book Issued Successfully!\n";
            }

            for (int i = 0; i < 9; i++) {
                temp << data[i];
                if (i < 8) temp << ",";
            }
            temp << endl;
        }

        file.close();
        temp.close();

        remove("books.txt");
        rename("temp.txt", "books.txt");
    }

    void returnBook() {
        ifstream file("books.txt");
        ofstream temp("temp.txt");

        int searchId;
        cout << "Enter Book ID to Return: ";
        cin >> searchId;
        cin.ignore();

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string data[9];

            for (int i = 0; i < 9; i++) {
                getline(ss, data[i], ',');
            }

            if (stoi(data[0]) == searchId && data[5] == "Issued") {
                cout << "Enter Return Date: ";
                getline(cin, data[8]);

                data[5] = "Available";
                data[6] = "-";
                data[7] = "-";

                cout << "Book Returned Successfully!\n";
            }

            for (int i = 0; i < 9; i++) {
                temp << data[i];
                if (i < 8) temp << ",";
            }
            temp << endl;
        }

        file.close();
        temp.close();

        remove("books.txt");
        rename("temp.txt", "books.txt");
    }
};

int main() {
    Library lib;
    int choice;

    while (true) {
        cout << "\n===== Library Menu =====\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Issue Book\n";
        cout << "4. Return Book\n";
        cout << "5. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            lib.addBook();
            break;
        case 2:
            lib.displayBooks();
            break;
        case 3:
            lib.issueBook();
            break;
        case 4:
            lib.returnBook();
            break;
        case 5:
            cout << "Exiting...";
            return 0;
        default:
            cout << "Invalid Choice!\n";
        }
    }
}
