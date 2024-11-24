#include <fstream>
#pragma Once
#include "Player.h"
#include <cstdio>

class CricketTeam {
private:
    Player* head;
    Player* tail;
    static int playerCount;

public:
    CricketTeam() : head(nullptr), tail(nullptr) {}

    ~CricketTeam() {
        Player* p = head;
        while (p != nullptr) {
            Player* temp = p;
            p = p->getNext();
            delete temp;
        }
        head = tail = nullptr;
    }

    static void initializeCounter() {
        ifstream counterFile("PlayerCounter.txt");
        if (counterFile.is_open()) {
            counterFile >> playerCount;
            counterFile.close();
        } else {
            playerCount = 0;
        }
    }

    static void updateCounter() {
        ofstream counterFile("PlayerCounter.txt", ios::trunc);
        counterFile << playerCount;
        counterFile.close();
    }

    void loadPlayers() {
        string *Names = new string[playerCount];
        ifstream NamesFile("Names.txt");

        for(int i = 1; i <= playerCount; i++){
            if(NamesFile.is_open()){
                getline(NamesFile, Names[i]);
            }
        }

        NamesFile.close();

        for (int i = 1; i <= playerCount; i++) {
            ifstream playerFile(Names[i] + ".txt");
            if (playerFile.is_open()) {
                string name;
                int odi, test, t20;
                getline(playerFile, name);
                playerFile >> odi >> test >> t20;
                playerFile.close();

                Player* newPlayer = new Player(name, odi, test, t20);
                addToList(newPlayer);
            }
        }
        delete [] Names;
    }

    void addPlayer(string name, int odi, int test, int t20) {
        Player* newPlayer = new Player(name, odi, test, t20);
        playerCount++;
        savePlayerToFile(newPlayer);
        addToList(newPlayer);
        savePlayerName(newPlayer->getName());
        updateCounter();
    }

    void savePlayerToFile(Player* player) {
        ofstream playerFile(player->getName() + ".txt", ios::trunc);
        playerFile << player->getName() << "\n"
                   << player->getODIs() << "\n"
                   << player->getTests() << "\n"
                   << player->getT20s();
        playerFile.close();
    }

   void savePlayerName(const string& newName) {
        vector<string> names;
        string name;

        ifstream inFile("Names.txt");
        if (inFile) {
            while (getline(inFile, name)) {
                names.push_back(name);
            }
            inFile.close();
        }

        names.push_back(newName);

        ofstream outFile("Names.txt", ios::trunc);
        if (!outFile) {
            cerr << "\nError: Could not open the file to save the player's name.\n";
            return;
        }

        for (size_t i = 0; i < names.size(); ++i) {
            outFile << names[i] << endl;
        }

        outFile.close();
        cout << "\nPlayer name '" << newName << "' saved successfully.\n";
    }

    void removePlayer(string name) {
        Player* p = head;
        while (p != nullptr) {
            if (p->getName() == name) {
                if (p == head) head = p->getNext();
                if (p == tail) tail = p->getPrev();
                if (p->getPrev()) p->getPrev()->setNext(p->getNext());
                if (p->getNext()) p->getNext()->setPrev(p->getPrev());

                delete p;
                cout << "\nPlayer " << name << " removed successfully!\n";
                string filename = name + ".txt";
                if(remove(filename.c_str()) == 0){
                    cout << "\nPlayer's Record Deleted!\n";
                }else{
                    cout << "\nUnable to delete file '" << name << "'. It may not exist.\n";
                }
                playerCount--;
                updateCounter();
                deleteNameFromFile("Names.txt", name);
                return;
            }
            p = p->getNext();
        }
        cout << "\nPlayer " << name << " not found!\n";
    }

    void deleteNameFromFile(const string& fileName, const string& nameToDelete) {
        ifstream inputFile(fileName); 
        if (!inputFile) {
            cerr << "Error: File could not be opened.\n";
            return;
        }

        vector<string> names;
        string name;


        while (getline(inputFile, name)) {
            if (name != nameToDelete) { 
                names.push_back(name);
            }
        }

        inputFile.close(); 

        ofstream outputFile(fileName, ios::trunc); 
        if (!outputFile) {
            cerr << "Error: File could not be written.\n";
            return;
        }

        for (size_t i = 0; i < names.size(); ++i) {
            outputFile << names[i] << endl;
        }

        outputFile.close();
        cout << "Name '" << nameToDelete << "' deleted successfully (if it existed).\n";
    }

    void updatePlayer(string name, string newName, int odi, int test, int t20) {
        Player* p = head;
        while (p != nullptr) {
            if (p->getName() == name) {
                p->updateData(newName, odi, test, t20);
                string oldFileName = name + ".txt";
                string newFileName = newName + ".txt";

                if (rename(oldFileName.c_str(), newFileName.c_str()) == 0) {
                    cout << "\nFile renamed successfully from '" << oldFileName << "' to '" << newFileName << "'.\n";
                }else {
                    perror("\nError renaming file\n");
                }
                deleteNameFromFile("Names.txt", name);
                savePlayerName(newName);
                cout << "\nPlayer " << name << " updated successfully!\n";
                return;
            }
            p = p->getNext();
        }
        cout << "\nPlayer " << name << " not found!\n";
    }

    void DisplayAllPlayers() {
        if (head == nullptr) {
            cout << "\nNo players available.\n";
            return;
        }

        cout << left << setw(20) << "Name" << setw(10) << "ODIs" 
             << setw(10) << "T20s" << setw(10) << "Tests" << endl;
        cout << string(50, '-') << endl;

        Player* p = head;
        while (p != nullptr) {
            cout << left << setw(20) << p->getName() << setw(10) << p->getODIs() 
                 << setw(10) << p->getT20s() << setw(10) << p->getTests() << endl;
            p = p->getNext();
        }
    }

    void addToList(Player* newPlayer) {
        if (head == nullptr) {
            head = tail = newPlayer;
        } else {
            tail->setNext(newPlayer);
            newPlayer->setPrev(tail);
            tail = newPlayer;
        }
    }

    bool isEmpty() {
        return head == nullptr;
    }
};