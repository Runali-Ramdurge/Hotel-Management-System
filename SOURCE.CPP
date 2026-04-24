/*
    Title       : Hotel Management System (Modern Version)
    Language    : C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

class Hotel {
private:
    int room_no;
    string name, address, phone;
    int days;
    float fare;

public:
    void main_menu();
    void add();
    void display();
    void rooms();
    void edit();
    int check(int);
    void modify(int);
    void delete_rec(int);
};

// ---------------- MAIN MENU ----------------
void Hotel::main_menu() {
    int choice;

    while (true) {
        cout << "\n\n===== HOTEL MANAGEMENT SYSTEM =====\n";
        cout << "1. Book a Room\n";
        cout << "2. Customer Record\n";
        cout << "3. Rooms Allotted\n";
        cout << "4. Edit Record\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: add(); break;
            case 2: display(); break;
            case 3: rooms(); break;
            case 4: edit(); break;
            case 5: return;
            default: cout << "Invalid choice!\n";
        }
    }
}

// ---------------- ADD CUSTOMER ----------------
void Hotel::add() {
    ofstream fout("Record.dat", ios::app | ios::binary);

    cout << "\nEnter Room No: ";
    cin >> room_no;

    if (check(room_no)) {
        cout << "Room already booked!\n";
        return;
    }

    cin.ignore();
    cout << "Name: ";
    getline(cin, name);

    cout << "Address: ";
    getline(cin, address);

    cout << "Phone: ";
    getline(cin, phone);

    cout << "Days: ";
    cin >> days;

    fare = days * 900;

    fout.write((char*)this, sizeof(*this));
    fout.close();

    cout << "Room booked successfully!\n";
}

// ---------------- DISPLAY CUSTOMER ----------------
void Hotel::display() {
    ifstream fin("Record.dat", ios::binary);

    int r, found = 0;
    cout << "Enter room no: ";
    cin >> r;

    while (fin.read((char*)this, sizeof(*this))) {
        if (room_no == r) {
            cout << "\nRoom No: " << room_no;
            cout << "\nName: " << name;
            cout << "\nAddress: " << address;
            cout << "\nPhone: " << phone;
            cout << "\nDays: " << days;
            cout << "\nFare: " << fare << endl;
            found = 1;
        }
    }

    if (!found)
        cout << "Record not found!\n";

    fin.close();
}

// ---------------- LIST ALL ROOMS ----------------
void Hotel::rooms() {
    ifstream fin("Record.dat", ios::binary);

    cout << "\n--- All Booked Rooms ---\n";

    while (fin.read((char*)this, sizeof(*this))) {
        cout << "\nRoom No: " << room_no;
        cout << "\nName: " << name;
        cout << "\nPhone: " << phone;
        cout << "\nDays: " << days;
        cout << "\nFare: " << fare;
        cout << "\n----------------------";
    }

    fin.close();
}

// ---------------- CHECK ROOM ----------------
int Hotel::check(int r) {
    ifstream fin("Record.dat", ios::binary);

    while (fin.read((char*)this, sizeof(*this))) {
        if (room_no == r) {
            fin.close();
            return 1;
        }
    }

    fin.close();
    return 0;
}

// ---------------- EDIT MENU ----------------
void Hotel::edit() {
    int choice, r;

    cout << "\n1. Modify Record\n2. Delete Record\nEnter choice: ";
    cin >> choice;

    cout << "Enter room no: ";
    cin >> r;

    if (choice == 1)
        modify(r);
    else if (choice == 2)
        delete_rec(r);
    else
        cout << "Invalid choice!\n";
}

// ---------------- MODIFY ----------------
void Hotel::modify(int r) {
    fstream file("Record.dat", ios::in | ios::out | ios::binary);
    bool found = false;

    while (file.read((char*)this, sizeof(*this))) {
        if (room_no == r) {
            cin.ignore();
            cout << "New Name: ";
            getline(cin, name);

            cout << "New Address: ";
            getline(cin, address);

            cout << "New Phone: ";
            getline(cin, phone);

            cout << "Days: ";
            cin >> days;

            fare = days * 900;

            file.seekp(file.tellg() - (streampos)sizeof(*this));
            file.write((char*)this, sizeof(*this));

            cout << "Record updated!\n";
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Record not found!\n";

    file.close();
}

// ---------------- DELETE ----------------
void Hotel::delete_rec(int r) {
    ifstream fin("Record.dat", ios::binary);
    ofstream fout("temp.dat", ios::binary);

    bool found = false;

    while (fin.read((char*)this, sizeof(*this))) {
        if (room_no == r) {
            found = true;
            continue;
        }
        fout.write((char*)this, sizeof(*this));
    }

    fin.close();
    fout.close();

    remove("Record.dat");
    rename("temp.dat", "Record.dat");

    if (found)
        cout << "Record deleted!\n";
    else
        cout << "Record not found!\n";
}

// ---------------- MAIN ----------------
int main() {
    string user, pass;

    cout << "Username: ";
    cin >> user;

    cout << "Password: ";
    cin >> pass;

    if (user == "admin" && pass == "1234") {
        cout << "\nLogin successful!\n";
        Hotel h;
        h.main_menu();
    } else {
        cout << "Invalid credentials!\n";
    }

    return 0;
}
