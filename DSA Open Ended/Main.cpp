#include "Functions.h"

int CricketTeam::playerCount = 0;

int main() {
    cout << endl << endl;
    CricketTeam::initializeCounter();
    CricketTeam team;
    team.loadPlayers();

    int choice;
    do {
        MainMenu();
        choice = getValidatedInt("\n\nEnter your choice: ");

        switch (choice) {
        case 1: {
            string name = getValidatedString("\nEnter Player Name: ");
            int odi = getValidatedInt("\nEnter ODI Matches: ");
            int test = getValidatedInt("\nEnter Test Matches: ");
            int t20 = getValidatedInt("\nEnter T20 Matches: ");
            team.addPlayer(name, odi, test, t20);
            cout << "\nPlayer Added Successfully!\n";
            break;
        }
        case 2: {
            string name = getValidatedString("\nEnter Player Name to Remove: ");
            team.removePlayer(name);
            break;
        }
        case 3: {
            string name = getValidatedString("\nEnter Player Name to Update: ");
            string newName = getValidatedString("\nEnter New Player Name: ");
            int odi = getValidatedInt("\nEnter ODI Matches: ");
            int test = getValidatedInt("\nEnter Test Matches: ");
            int t20 = getValidatedInt("\nEnter T20 Matches: ");
            team.updatePlayer(name, newName, odi, test, t20);
            
            break;
        }
        case 4:
            cout << endl << endl;
            team.DisplayAllPlayers();
            cout << endl << endl;
            break;
        case 5:
            cout << "\nExiting Program.\n";
            break;
        default:
            cout << "\nInvalid choice! Please try again.\n";
        }
    } while (choice != 5);

    cout << endl << endl;
    return 0;
}
