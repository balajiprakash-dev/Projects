/*
Requirements:
    1. Player can select the box number where they want to block
    2. Display board after selection
    3. Evaluate results and show winner/loser/tie
    4. Each player gets one turn
    5. Ask them if they want to start again or quit
*/
#include <iostream>
#include <vector>
#include<unistd.h>

using namespace std;

#define BOARD_SIZE 3

#define EMPTY_CELL '-'
#define X_CELL     'X'
#define O_CELL     'O'

class Board {
private:
    vector<vector<char>> grid;
    int gridSize;
public:
    Board(int board_size) {
        gridSize = board_size;
        grid.resize(board_size);
        for (int i=0; i<board_size; i++) {
            grid[i].resize(board_size, EMPTY_CELL);
        }
    }

    void boardDisplay(void) {
        cout<<endl<<"===== BOARD ====="<<endl;

        for (int i=0; i<gridSize; i++) {
            for (int j=0; j<gridSize; j++) {
                cout<<grid[i][j]<<'\t';
            }
            cout<<endl;
        }
        cout<<endl;
    }

    int boardPlacePlayer(char c, int i, int j) {
        if (i>=0 && i<gridSize && j>=0 && j<gridSize && grid[i][j] == EMPTY_CELL) {
            grid[i][j] = c;
            return 0;
        }

        cout<<endl<<"!! INVALID MOVE !! TRY AGAIN..."<<endl<<endl;

        usleep(1000000);

        return -1;
    }

    int boardIsGameOver() {
        int xCount;
        int oCount;

        // check match for row
        for (int i=0; i<gridSize; i++) {
            xCount = 0;
            oCount = 0;
            for (int j=0; j<gridSize; j++) {
                switch (grid[i][j])
                {
                case X_CELL:
                    xCount++;
                    break;
                case O_CELL:
                    oCount++;
                    break;
                default:
                    break;
                }
            }
            if (xCount == gridSize) {
                return 1;
            }
            if (oCount == gridSize) {
                return 2;
            }
        }

        // check column
        for (int j=0; j<gridSize; j++) {
            xCount = 0;
            oCount = 0;
            for (int i=0; i<gridSize; i++) {
                switch (grid[i][j])
                {
                case X_CELL:
                    xCount++;
                    break;
                case O_CELL:
                    oCount++;
                    break;
                default:
                    break;
                }
            }
            if (xCount == gridSize) {
                return 1;
            }
            if (oCount == gridSize) {
                return 2;
            }
        }

        // check right diagonal
        xCount = 0;
        oCount = 0;
        for (int i=0; i<gridSize; i++) {
            switch (grid[i][i])
            {
            case X_CELL:
                xCount++;
                break;
            case O_CELL:
                oCount++;
                break;
            default:
                break;
            }
        }
        if (xCount == gridSize) {
            return 1;
        }
        if (oCount == gridSize) {
            return 2;
        }
        // check left diagonal
        xCount = 0;
        oCount = 0;
        for (int i=0; i<gridSize; i++) {
            switch (grid[i][gridSize-i-1])
            {
            case X_CELL:
                xCount++;
                break;
            case O_CELL:
                oCount++;
                break;
            default:
                break;
            }
        }
        if (xCount == gridSize) {
            return 1;
        }
        if (oCount == gridSize) {
            return 2;
        }

        return 0;
    }
};

class Player {
private:
    string username;
    int gamesWon;
    int gamesPlayed;
    char curTeam;
public:
    Player(string name) {
        username = name;
        gamesWon = 0;
        gamesPlayed = 0;
    }

    string getUserName(void) {
        return username;
    }

    void setTeam(char team) {
        curTeam = team;
    }

    char getTeam(void) {
        return curTeam;
    }

    void displayUser(void) {
        cout<<"Username: "<<username<<endl;
        cout<<"Games Played: "<<gamesPlayed<<endl;
        cout<<"Games Won: "<< gamesWon<<endl;
    }

    void updatePlayerStats(bool won) {
        if (won == true) {
            gamesWon++;
        }
        gamesPlayed++;
    }
};

class Game {
private:
    Player* p1;
    Player* p2;
    Player* curP;
    Board* b;

public:
    Game(string username1, string username2, int board_size) {
        p1 = new Player(username1);
        p1->setTeam(X_CELL);
        p2 = new Player(username2);
        p2->setTeam(O_CELL);
        b = new Board(board_size);
    }

    void beginGameLoop() {
        int result;
        bool turnX = true;
        int x, y;

        b->boardDisplay();

        while(1) {
            if (turnX == true) {
                curP = p1;
            } else {
                curP = p2;
            }

            do {
                cout<<"Player '"<<curP->getTeam()<<"' : '"<<curP->getUserName()<<"' your turn! ";
                cout<<"Enter location: (x, y): ";
                cin>>x>>y;
            } while (b->boardPlacePlayer(curP->getTeam(), x, y));

            b->boardDisplay();

            result = b->boardIsGameOver();

            if (result != 0) {
                cout<<"Player '"<<curP->getTeam()<<"' : '"<<curP->getUserName()<<"' won!!\n";
                if (turnX == true) {
                    p1->updatePlayerStats(true);
                    p2->updatePlayerStats(false);
                } else {
                    p1->updatePlayerStats(false);
                    p2->updatePlayerStats(true);
                }
                return;
            }

            turnX = !turnX;
        }
    }

    void displayUsers(void) {
        cout<<endl<<"===== Player Stats ====="<<endl;
        p1->displayUser();
        cout<<endl;
        p2->displayUser();
    }
};

int main() {
    Game *game;
    string player1;
    string player2;

    cout<<"Enter 'X' player username: ";
    cin>>player1;

    for (auto & c : player1) c = toupper(c);

    cout<<"Enter 'O' player username: ";
    cin>>player2;

    for (auto & c : player2) c = toupper(c);

    game = new Game(player1, player2, BOARD_SIZE);

    game->beginGameLoop();

    game->displayUsers();
    
    return 0;
}