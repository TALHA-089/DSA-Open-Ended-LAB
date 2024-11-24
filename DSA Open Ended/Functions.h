#pragma Once
#include "CricketTeam.h"

int getValidatedInt(const string& prompt) {
    int value;
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        stringstream ss(input);
        if (ss >> value && ss.eof() && value >= 0) { 
            return value;
        }
        cout << "\nInvalid input. Please enter a valid non-negative integer.\n";
    }
}

string getValidatedString(const string& prompt) {
    string value;
    while (true) {
        cout << prompt;
        getline(cin, value);
        if (!value.empty()) {
            return value;
        }
        cout << "Input cannot be empty. Please try again.\n";
    }
}

void MainMenu(){
    cout << "\n------------ Main Menu ------------\n";
    cout << "\n1. Add Player";
    cout << "\n2. Remove Player";
    cout << "\n3. Update Player";
    cout << "\n4. Display All Players";
    cout << "\n5. Exit";
}