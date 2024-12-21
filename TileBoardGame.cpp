#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
using namespace std;

class Tile {
    public:
        bool visited;
        bool isSafeTile;
        string status;

        Tile() : visited(false), isSafeTile(false), status("X") {}

        bool makeSafe() {
            isSafeTile = true;
            return isSafeTile;
        }

        bool visit() {
            visited = true;
            return visited;
        }

        string getStatus() {
            return status;
        }

        string checkOut() {
            if (isSafeTile) {
                status = "O";
            } else {
                status = "D";
            }
            return status;
        }
};

class TileBoard {
    public:
        int level;
        Tile board[16][16];

    TileBoard() : level(16) {
        std::random_device rd;
        std::default_random_engine engine(rd());
        std::uniform_int_distribution<int> dist(0, level - 1);

        for (int i = 0; i < level; i++) {
            vector<int> safeTiles;
            while (safeTiles.size() < 8) { 
                int random_number = dist(engine);
                if (find(safeTiles.begin(), safeTiles.end(), random_number) == safeTiles.end()) {
                    safeTiles.push_back(random_number);
                }
            }
            for (int tile : safeTiles) {
                (board[i][tile]).makeSafe();
            }
        }
        
        for (int i = 0; i < level; i++) {
            for (int j = 0; j < level; j++) {
                (board[i][j]).status = "X";
                (board[i][j]).visited = false;
            }
        }
    }

    void printBoard() {
        for (int i = 0; i < level; i++) {
            for (int j = 0; j < level; j++) {
                cout << (board[i][j]).getStatus() << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    void play() {
        cout << "You are on a tile of 16 x 16 square board. Only one tile per row is safe to step on." << endl;
        int level = 1;
        bool playerisSafe = true;

        while (level <= 16 && playerisSafe) {
            cout << "You are on level " << level << endl;
            printBoard();
            cout << "choose a tile to step on. The numbers you are allowed to input are 1 to 16." << endl;
            
            int input;
            cin >> input; 

            while (input < 1 || input > 16) {
                cout << "Invalid input. Number should be between 1 to 16." << endl;
                cin >> input;
            }

            Tile& current = board[level - 1][input - 1];
            current.visit();
            current.checkOut();

          if (current.isSafeTile) {
                current.status = "O"; 
                cout << "Tile is safe." << endl;
            } else {
                current.status = "D"; 
                cout << "You stepped on a dangerous tile. Game over." << endl;
                playerisSafe = false;
            }

            printBoard();

            if (playerisSafe) {
                level++; 
            }
        }

        if (level > 16) {
            cout << "All levels complete." << endl;
        }
    }

};

int main() {
    TileBoard taylor;
    string choice;
    cout << "Welcome to the Tile game!" << endl;
    cout << "Would you like to play?" << endl;
    cin >> choice;
    
    while (choice == "yes") {
        taylor.play();
        cout << "Keep playing?" << endl;
        cin >> choice;
    }
    
    cout << "Thanks for playing! See you next time :)" << endl;
    return 0;
}