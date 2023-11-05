#ifndef COMMON_H
#define COMMON_H
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

const char PLAYER_KEY[3] = {' ', 'O', 'X'};

string prompt(string question) {
    string response;
    cout << question;
    cin >> response;
    return response;
}

int promptInt(string question) {
    return stoi(prompt(question));
}

struct coord {
    uint8_t x;
    uint8_t y;
};
coord promptCoord(string xQ, string yQ) {
    coord input;
    tryAgain:
    try {
        input.x = promptInt(xQ);
        if (input.x<1||input.x>3) throw out_of_range(NULL);
        input.y = promptInt(yQ);
        if (input.y<1||input.y>3) throw out_of_range(NULL);
    } catch (...) {
        cout << "Oops, please enter a value between 1 and 3" << endl;
        goto tryAgain;
    }
    input.x--; input.y--;
    return input;
}

// Line param must be between 0 - 6 inclusive
void displayBoardLine(uint8_t* board, uint8_t line) {
    switch (line) {
        case 0:
            cout << "╔═══════════╗"; break;
        case 1:
        case 3:
        case 5:
            cout << "║ ";
            for (int j=0; j<3; j++) {
                cout << PLAYER_KEY[board[3*(line-1)/2+j]];
                if (j < 2) cout << " │ ";
            }
            cout << " ║"; break;
        case 2:
        case 4:
            cout << "║───┼───┼───║"; break;
        case 6:
            cout << "╚═══════════╝"; break;
        default:
            throw out_of_range("line param not between 0 - 6");
    }
}

bool checkWin(int player, uint8_t* board) {
    uint8_t mask = 21*player;
    // Check rows and columns
    for (int i=0; i<3; i++) {
        if (((board[3*i]<<4) | (board[3*i+1]<<2) | board[3*i+2]) == mask) return true;
        if (((board[i]<<4) | (board[3+i]<<2) | board[6+i]) == mask) return true;
    }
    // Check diagonals
    if (((board[0]<<4) | (board[4]<<2) | board[8]) == mask) return true;
    if (((board[2]<<4) | (board[4]<<2) | board[6]) == mask) return true;
    return false;
}

bool checkDraw(uint8_t* board) {
    for (int i=0;i<9;i++)
        if (board[i] == 0) return false;
    return true;
}

string boardToString(uint8_t* board) {
    string result = "";
    for (int i=0; i<9; i++) {
        result += to_string(board[i]);
    }
    return result;
}
#endif