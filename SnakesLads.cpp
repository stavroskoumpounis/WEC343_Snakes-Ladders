#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int SIZE = 100;

bool takeTurn(int player, int& position, char board[], int ladders[][2], int snakes[][2]);
void printBoard(int players[], char board[], int ladders[][2], int snakes[][2]);

int main() {
    char board[SIZE];
    int players[2] = {1, 1};
    bool gameOver = false;

    //init board
    fill_n(board, SIZE, '_');


    int ladders[4][2] = {{6,46},{19,43},{52,71},{57,98}};
    int snakes[3][2] = {{47,9},{62,40},{96,75}};


    //init ladders
    for(int i = 0; i < 4; i++){
        int start = ladders[i][0];
        int end = ladders[i][1];

        board[start] = 'L';
        board[end] = 'L';
    }

    //init snakes
    for(int i = 0; i < 3; i++){
        int start = snakes[i][0];
        int end = snakes[i][1];

        board[start] = 'S';
        board[end] = 'S';
    }


    //random seed
    srand(time(NULL));

    int roll1, roll2, first, turn = 1;
    cout << "Players roll off for first: " << endl;
    roll1 = rand() % 6 + 1;
    roll2 = rand() % 6 + 1;
    cout << "\nPlayer 1 roll: " << roll1 << "\nPlayer 2 roll: " << roll2 << endl;
    if (roll1 >= roll2){
        first = 1;
        cout << "Player 1 goes first" << endl;
    } else {
        first = 2;
        cout << "Player 2 goes first" << endl;
    }
    cout << "\n|====GAME BEGINS====|" << endl;
    printBoard(players, board , ladders, snakes);


    while(!gameOver){


        gameOver = takeTurn(first, players[first == 1 ? 0 : 1], board, ladders, snakes);
        printBoard(players, board , ladders, snakes);

        if (gameOver) {break;}

        gameOver = takeTurn(first == 1 ? 2 : 1, players[first == 1 ? 1 : 0], board, ladders, snakes);
        printBoard(players, board , ladders, snakes);


    }

    return 0;
}

bool takeTurn(int player, int& position, char board[], int ladders[][2], int snakes[][2]) {
    int roll = rand() % 6 + 1;


    if ((position +roll) > SIZE) {
        cout << "\nPlayer " << player<< " rolled a " << roll << " and went over the board!";
        cout << "\nPlayer " << player<< " will stay on square " << position << endl;
    } else {
        position += roll;
        cout << "\nPlayer " << player << " rolled a " << roll << " and landed on square " << position << endl;

        if (position == SIZE) {
            cout << "Player " << player << " wins!" << endl;
            cout << "\n|====GAME OVER====|" << endl;
            return true;
        } else if (board[position] == 'L') {
            for (int i = 0; i < 4; i++) {
                if (ladders[i][0] == position) {
                    position = ladders[i][1];
                    cout << (player == 1 ? "Player 1" : "Player 2") << " took a ladder from square " << ladders[i][0]
                         << " to " << ladders[i][1] << endl;
                    break;
                }
            }
        } else if (board[position] == 'S') {
            for (int i = 0; i < 3; i++) {
                if (snakes[i][0] == position) {
                    position = snakes[i][1];
                    cout << (player == 1 ? "Player 1" : "Player 2") << " fell down a snake from square " << snakes[i][0]
                         << " to " << snakes[i][1] << endl;
                    break;
                }
            }
        }

        cout << "Player " << player << " has now moved to square " << position << endl;

    }

    //waits for key input to take next turn
    cin.get();
    return false;

}

void printBoard(int players[], char board[], int ladders[][2], int snakes[][2]) {
        bool rev = false;
        cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
        for (int i = 100; i > 0; rev ? i++ : i--){
            if(i == players[0] || i == players[1]){
                cout << "+";
                if(i < 10){cout << "  ";}
                else if(i < 100){cout << " ";}
                cout << (i == players[0] ? "[1]" : "[2]");
            } else if(board[i] == 'L' || board[i] == 'S'){
                cout << "+";
                if(i < 10){cout << "  ";}
                else if(i < 100){cout << " ";}
                cout << (board[i] == 'L' ? "[L]" : "[S]");
            } else {
                cout << "+   ";
                if(i < 10){cout << "  ";}
                else if(i < 100){cout << " ";}
            }
            cout << i << " ";
            if((i-1)%10 == 0 && (i-1)%20 == 10){
                i-=11;
                cout << "+";
                cout << endl;
                cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
                rev = true;
            }
            else if ((i)%10 == 0 && (i)%20 == 10){
                i-=9;
                cout << "+";
                cout << endl;
                cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
                rev = false;
            }
        }

}