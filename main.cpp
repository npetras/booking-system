#include <iostream>
#include "Plane.h"

#define EXIT 4

using namespace std;

int main() {
    auto *plane = new Plane("BA10510", 4, 3, 10, 10,
                            10, 10);
    plane->print(1);
    cout << endl;

    int choice;

    do {
        cout << endl;
        cout << "1 Book First-class" << endl;
        cout << "2 Book Business-class" << endl;
        cout << "3 Book Economy-class" << endl;
        cout << "4 Exit" << endl;

        cout << "Please enter your choice ";
        cin >> choice;

        int passengers;

        if (choice >= 1 && choice <= 3) {
            cout << "Number of passengers: ";
            cin >> passengers;
        }

        switch (choice) {
            case 1:
                if (plane->checkFreeSeats() >= passengers) {
                    plane->suggestSeats(passengers, choice);
                    plane->bookSeats(choice, passengers);
                } else {
                    cout << "First class is full" << endl;
                }
                break;
            case 2:
                break;
            case 3:
                break;
            case EXIT:
                break;
            default:
                cout << "Invalid choice" << endl;
                break;

        }

        plane->print(1);

    } while (choice != EXIT);

    delete plane;
    return 0;
}
