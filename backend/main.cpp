#include <iostream>
#include "Plane.h"

#define EXIT 4

void runApp(Plane *plane, int choice, int passengers);

using namespace std;

int main() {
    auto *plane = new Plane("BA10510", "London", "Frankfurt", 100,
                            65,45, 4, 3,
                            6,30,6, 40);
    plane->printAll();
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
            plane->makeBooking(choice);
        } else if (choice == EXIT) {
            cout << "Exiting..." << endl;
        } else {
            cout << "Invalid choice" << endl;
        }
    } while (choice != EXIT);

    delete plane;
    return 0;
}
