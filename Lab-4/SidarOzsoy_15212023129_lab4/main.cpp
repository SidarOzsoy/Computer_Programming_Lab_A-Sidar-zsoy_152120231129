#include <iostream>
#include <string>
using namespace std;

#define SIZE 5

struct Package {
    string packageID;
    string destinationCity;
    int dimensions[3];
    Package* next;
};

struct Courier {
    string courierName;
    string vehicleType;
};

void pushPackage(Package*& top, string id, string city, int l, int w, int h) {
    Package* newPacage = new Package;
    newPacage->packageID = id;
    newPacage->destinationCity = city;
    newPacage->dimensions[0] = l;
    newPacage->dimensions[1] = w;
    newPacage->dimensions[2] = h;
    newPacage->next = top;
    top = newPacage;
}

void enqueueCourier(Courier q[], int& rear, int& count, string name, string vehicle) {
    if (count == SIZE) {
        cout << "Queue is full" << endl;
        return;
    }

    rear = (rear + 1) % SIZE;
    q[rear].courierName = name;
    q[rear].vehicleType = vehicle;
    count++;
}

void dispatch(Package*& top, Courier q[], int& front, int& count) {
    if (top == NULL) {
        cout << "No package available" << endl;
        return;
    }

    if (count == 0) {
        cout << "No courier available" << endl;
        return;
    }

    Package* temp = top;
    Courier c = q[front];

    cout << c.courierName << " takes package " << temp->packageID
         << " to " << temp->destinationCity << endl;

    top = top->next;
    delete temp;

    front = (front + 1) % SIZE;
    count--;
}

void displayPackages(Package* top) {
    cout << "\nPackages in stack:" << endl;

    if (top == NULL) {
        cout << "Empty" << endl;
        return;
    }

    while (top != NULL) {
        cout << top->packageID << " " << top->destinationCity << " ["
             << top->dimensions[0] << " "
             << top->dimensions[1] << " "
             << top->dimensions[2] << "]" << endl;
        top = top->next;
    }
}

void displayCouriers(Courier q[], int front, int count) {
    cout << "\nCouriers in queue:" << endl;

    if (count == 0) {
        cout << "Empty" << endl;
        return;
    }

    for (int i = 0; i < count; i++) {
        int index = (front + i) % SIZE;
        cout << q[index].courierName << " " << q[index].vehicleType << endl;
    }
}

int main() {
    Package* top = NULL;
    Courier q[SIZE];

    int front = 0;
    int rear = -1;
    int count = 0;

    int choice;
    string id, city, name, vehicle;
    int l, w, h;

    do {
        cout << "\n1- Add Package" << endl;
        cout << "2- Add Courier" << endl;
        cout << "3- Dispatch" << endl;
        cout << "4- Display" << endl;
        cout << "5- Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter package id: ";
            cin >> id;
            cout << "Enter city: ";
            cin >> city;
            cout << "Enter length width height: ";
            cin >> l >> w >> h;
            pushPackage(top, id, city, l, w, h);
        }
        else if (choice == 2) {
            cout << "Enter courier name: ";
            cin >> name;
            cout << "Enter vehicle type: ";
            cin >> vehicle;
            enqueueCourier(q, rear, count, name, vehicle);
        }
        else if (choice == 3) {
            dispatch(top, q, front, count);
        }
        else if (choice == 4) {
            displayPackages(top);
            displayCouriers(q, front, count);
        }
        else if (choice == 5) {
            cout << "Program finished" << endl;
        }
        else {
            cout << "Wrong choice" << endl;
        }

    } while (choice != 5);

    return 0;
}
