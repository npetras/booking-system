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
            plane->print(choice);
            cout << "Number of passengers: ";
            cin >> passengers;

            if (plane->checkFreeSeats(choice) >= passengers) {
                plane->suggestSeats(passengers, choice);
                plane->bookSeats(choice, passengers);
            } else {
                cout << "This class is full" << endl;
            }
        } else if (choice == EXIT) {
            cout << "Exiting..." << endl;
        } else {
            cout << "Invalid choice" << endl;
        }



        plane->print(1);

    } while (choice != EXIT);

    delete plane;
    return 0;
}
