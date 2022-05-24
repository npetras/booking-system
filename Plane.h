//
// Created by Nicolas Petras, Billy Penton-Voak and Raymond Gorle on 23/05/2022.
//

#ifndef GROUP_PROJECT_PLANE_H
#define GROUP_PROJECT_PLANE_H

#endif //GROUP_PROJECT_PLANE_H

#include <string>
#include <tuple>
#include <cstdlib>
#include <stack>
#include <algorithm>
#include <iterator>
#include <cctype>

using namespace std;

int currPos;

struct Plane {
private:
    string flightNo;
    string origin;
    string destination;

    int firstClassPrice;
    int businessClassPrice;
    int economyClassPrice;

    int firstClassSeatsPerRows;
    int firstClassRows;
    int businessClassSeatsPerRow;
    int businessClassRows;
    int economyClassSeatsPerRow;
    int economyClassRows;

    int *firstClass;
    int *businessClass;
    int *economyClass;

public:
    Plane(string flightNo, string origin, string destination, int firstClassPrice, int businessClassPrice,
          int economyClassPrice, int firstClassSeatsPerRows, int firstClassRows, int businessClassSeatsPerRow,
          int businessClassRows, int economyClassSeatsPerRow, int economyClassRows) {

        this->flightNo = flightNo;
        this->origin = origin;
        this->destination = destination;

        this->firstClassPrice = firstClassPrice;
        this->businessClassPrice = businessClassPrice;
        this->economyClassPrice = economyClassPrice;

        this->firstClassSeatsPerRows = firstClassSeatsPerRows;
        this->firstClassRows = firstClassRows;
        this->businessClassSeatsPerRow = businessClassSeatsPerRow;
        this->businessClassRows = businessClassRows;
        this->economyClassSeatsPerRow = economyClassSeatsPerRow;
        this->economyClassRows = economyClassRows;

        this->firstClass = static_cast<int *>(malloc((firstClassSeatsPerRows * firstClassRows) * sizeof(int)));
        this->businessClass = static_cast<int *>(malloc((businessClassSeatsPerRow * businessClassRows) * sizeof(int)));
        this->economyClass = static_cast<int *>(malloc((economyClassSeatsPerRow * economyClassRows) * sizeof(int)));

        for (int i = 0; i < firstClassSeatsPerRows * firstClassRows; ++i) {
            firstClass[i] = 0;
        }

        for (int i = 0; i < businessClassSeatsPerRow * businessClassRows; ++i) {
            businessClass[i] = 0;
        }

        for (int i = 0; i < economyClassSeatsPerRow * economyClassRows; ++i) {
            economyClass[i] = 0;
        }
    }

    ~Plane() {
        free(firstClass);
        free(businessClass);
        free(economyClass);
    }

    void printClass(string className, int *classArr, int classRows, int classSeatsPerRow) {
        cout << className << " class";
        for (int i = 0; i < classRows * classSeatsPerRow; i++) {
            if (i % classSeatsPerRow == 0) {
                cout << endl;
                int row = i / classSeatsPerRow + 1 < 13 ?
                          i / classSeatsPerRow + 1 :
                          i / classSeatsPerRow + 2;

                cout << "Row: " << row << "\t\t";
            }

            if (classArr[i] == 0) {
                cout << static_cast<char>(65 + (i % classSeatsPerRow));
            } else {
                cout << '-';
            }
        }
        cout << endl;
    }

    void printAll() {
        printClass("First", firstClass, firstClassRows,
                   firstClassSeatsPerRows);
        printClass("Business", businessClass, businessClassRows,
                   businessClassSeatsPerRow);
        printClass("Economy", economyClass, economyClassRows,
                   economyClassSeatsPerRow);
    }

    int checkFreeSeats(int* classArr, int classRows, int classSeatsPerRow) {
        int counter = 0;

        for (int i = 0; i < classRows * classSeatsPerRow; i++) {
            if (classArr[i] == 0) {
                counter++;
            }
        }
        cout << "Seats remaining: " << counter << endl;
        return counter;
    }

    string convertIndexToSeat(int index, int classSeatsPerRow) {
        string temp;

        int row = (index / classSeatsPerRow) + 1;
        char seat = static_cast<char>(65 + (index % classSeatsPerRow));
        temp = to_string(row);
        temp.push_back(seat);
        return temp;
    }

    int convertSeatToIndex(int row, char seat, int classSeatsPerRow) {
        int index = ((row - 1) * classSeatsPerRow) + (static_cast<int>(seat) - 65);
        return index;
    }

    void bookSuggestedSeats(int passengers, int* seats, int* classArr) {
        for (int i = 0; i < passengers; ++i) {
            classArr[seats[i]] = 1;
        }
    }

    void suggestSeats(int passengers, int* classArr, int classRows, int classSeatsPerRow, int* seats) {

        currPos = 0;

        findSeats(passengers, seats, classArr, classRows, classSeatsPerRow);

        cout << "Suggested Seats: ";
        for (int i = 0; i < passengers; ++i) {
            cout << convertIndexToSeat(seats[i], classSeatsPerRow) << "\t";
        }
        cout << endl;

    }

    static bool isInSeats(const int *seats, int index) {
        bool inSeats = false;
        for (int k = 0; k < currPos; ++k) {
            if (seats[k] == index) {
                inSeats = true;
                break;
            }
        }
        return inSeats;
    }

    void findSeats(int passengers, int *seats, int *classArr, int classRows, int classSeatsPerRow) {
        int counter;
        for (int i = 0; i < classRows; i++) {
            counter = 0;
            for (int j = 0; j < classSeatsPerRow; j++) {
                int index = (i * classSeatsPerRow) + j;
                if (classArr[index] == 0) {
                    bool inSeats = isInSeats(seats, index);
                    // assign seats
                    if (!inSeats) {
                        counter++;
                        if (passengers == counter) {
                            for (int k = j-counter+1; k <= j; k++) {
                                seats[currPos] = i * classSeatsPerRow + k;
                                currPos = currPos + 1;
                            }
                            return;
                        }
                    }
                } else {
                    counter = 0;
                }
            }
        }
        if (counter - 1 < passengers) {
            int splitPassengers1 = passengers / 2;
            int splitPassengers2 = passengers - splitPassengers1;

            findSeats(splitPassengers1, seats, classArr, classRows, classSeatsPerRow);
            findSeats(splitPassengers2, seats, classArr, classRows, classSeatsPerRow);
        }
    }

    void bookSeats(int passengers, int *classArr, int classRows, int classSeatsPerRow) {
        int row;
        char seat;

        while (passengers > 0) {
            bool invalidInput = false;
            do {
                if (invalidInput) {
                    cout << "Your last input was incorrect, please enter it again" << endl;
                }

                cout << "Provide seat row: ";
                cin >> row;
                cout << "Provide seat letter: ";
                cin >> seat;

                invalidInput = row < 0 || row > classRows || seat < 65 || seat > 65 + (classSeatsPerRow - 1);
            } while (invalidInput);

            int index = convertSeatToIndex(row, seat, classSeatsPerRow);
            if (classArr[index] == 0) {
                classArr[index] = 1;
                passengers--;
            } else {
                cout << "Seat is already booked, please provide another" << endl;
            }
        }
        // TODO Add confirmation
    }

    void makeBooking(int choice) {
        int passengers;

        string className;
        int *classArr;
        int classRows;
        int classSeatsPerRow;
        int classPrice;

        switch (choice) {
            case 1:
                className = "First";
                classArr = firstClass;
                classRows = firstClassRows;
                classSeatsPerRow = firstClassSeatsPerRows;
                classPrice = firstClassPrice;
                break;
            case 2:
                className = "Business";
                classArr = businessClass;
                classRows = businessClassRows;
                classSeatsPerRow = businessClassSeatsPerRow;
                classPrice = businessClassPrice;
                break;
            case 3:
                className = "Economy";
                classArr = economyClass;
                classRows = economyClassRows;
                classSeatsPerRow = economyClassSeatsPerRow;
                classPrice = economyClassPrice;
                break;
            default:
                className = "Invalid";
                classArr = nullptr;
                classRows = 0;
                classSeatsPerRow = 0;
                classPrice = 0;

                cout << "Invalid class type" << endl;
                break;
        }

        this->printClass(className, classArr, classRows, classSeatsPerRow);
        cout << className << " class seat price is £" << classPrice << endl;

        cout << "Number of passengers: ";
        cin >> passengers;

        if (this->checkFreeSeats(classArr, classRows, classSeatsPerRow) >= passengers) {
            int seats[passengers];
            this->suggestSeats(passengers, classArr, classRows, classSeatsPerRow, seats);

            char bookSuggestSheets;
            cout << "Total cost: £" << passengers * classPrice << endl;
            cout << "Do you want to book the suggested seats?" << endl;
            cout << "Please provide Y or N: ";
            cin >> bookSuggestSheets;

            if (static_cast<char>(toupper(bookSuggestSheets)) == 'Y') {
                bookSuggestedSeats(passengers, seats, classArr);
            } else {
                this->bookSeats(passengers, classArr, classRows, classSeatsPerRow);
            }
            this->printClass(className, classArr, classRows, classSeatsPerRow);
        } else {
            cout << className << " class is full" << endl;
        }
    }
};
