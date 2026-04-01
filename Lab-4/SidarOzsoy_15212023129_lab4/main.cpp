#include <iostream>
#include <string>
using namespace std;
#define SIZE 5

struct Package                                                              {
    string packageID;
    string destinationCity;
    int dimensions[3];
    Package* next;
                                                                            };

struct Courier                                                              {
    string courierName;
    string vehicleType;
                                                                            };

void pushPackage(Package*& top, string id, string city, int l, int w, int h) {
    Package* newPackage = new Package;
    newPackage->packageID = id;
    newPackage->destinationCity = city;
    newPackage->dimensions[0] = l;
    newPackage->dimensions[1] = w;
    newPackage->dimensions[2] = h;
    newPackage->next = top;
    top = newPackage;
                                                                            }

void enqueueCourier(Courier q[], int& rear, int& count, string name, string vehicle) {
    if (count == SIZE)                                                      {
        cout << "Queue is full.\n";
        return;
                                                                            }

    rear = (rear + 1) % SIZE;
    q[rear].courierName = name;
    q[rear].vehicleType = vehicle;
    count++;
                                                                            }

void dispatch(Package*& top, Courier q[], int& front, int& count)           {
    if (top == nullptr) {
        cout << "No package available.\n";
        return;
                                                                            }

    if (count == 0)                                                         {
        cout << "No courier available.\n";
        return;
                                                                            }

    Package* temp = top;
    Courier c = q[front];

    cout << c.courierName << " (" << c.vehicleType << ") takes package "
         << temp->packageID << " to " << temp->destinationCity << endl;

    top = top->next;
    delete temp;

    front = (front + 1) % SIZE;
    count--;
                                                                            }

void displayPackages(Package* top)                                          {
    cout << "\nPackages:\n";
    if (top == nullptr)                                                     {
        cout << "Empty\n";
        return;
                                                                            }

    while (top != nullptr)                                                  {
        cout << top->packageID << " - " << top->destinationCity << " - ["
             << top->dimensions[0] << ", "
             << top->dimensions[1] << ", "
             << top->dimensions[2] << "]\n";
        top = top->next;
                                                                            }
                                                                            }

void displayCouriers(Courier q[], int front, int count)                     {
    cout << "\nCouriers:\n";
    if (count == 0)                                                         {
        cout << "Empty\n";
        return;
    }

    for (int i = 0; i < count; i++)                                         {
        int index = (front + i) % SIZE;
        cout << q[index].courierName << " - " << q[index].vehicleType << endl;
                                                                            }
                                                                            }

int main()                                                                  {
    Package* top = nullptr;

    Courier q[SIZE];
    int front = 0, rear = -1, count = 0;

    int choice;
    string id, city, name, vehicle;
    int l, w, h;

    do                                                                         {
        cout << "\n1. Add Package\n";
        cout << "2. Add Courier\n";
        cout << "3. Dispatch\n";
        cout << "4. Display\n";
        cout << "5. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice)                                                         {
        case 1:
            cout << "Package ID: ";
            cin >> id;
            cout << "Destination City: ";
            cin >> city;
            cout << "Length Width Height: ";
            cin >> l >> w >> h;
            pushPackage(top, id, city, l, w, h);
            break;

        case 2:
            cout << "Courier Name: ";
            cin >> name;
            cout << "Vehicle Type: ";
            cin >> vehicle;
            enqueueCourier(q, rear, count, name, vehicle);
            break;

        case 3:
            dispatch(top, q, front, count);
            break;

        case 4:
            displayPackages(top);
            displayCouriers(q, front, count);
            break;

        case 5:
            cout << "Program ended.\n";
            break;

        default:
            cout << "Invalid choice.\n";
                                                                            }

                                                                            } while (choice != 5);

    return 0;
                                                                            }
