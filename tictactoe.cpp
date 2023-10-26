#include "common.h"

void displayWelcome();
void displayBoard(uint8_t* board);

uint8_t* board;

int main() {
    int x,y;
    uint8_t currentPlayer = 1;
    bool isWin = false;
    board = new uint8_t[9]();
    displayWelcome();
    prompt("==============================Type Any Key To Start=============================");
    displayBoard(board);
    for (int t=0; t<9; t++) {
        do {
            coord input = promptCoord(
                (string) "Player "+PLAYER_KEY[currentPlayer]+", pick your column [1-3] ",
                (string) "Player "+PLAYER_KEY[currentPlayer]+", pick your row [1-3] "
            );
            x = input.x; y = input.y;
            if (board[y*3+x] > 0)
                cout << "That cell has been filled in, select another one" << endl;
        } while (board[y*3+x] > 0);
        board[3*y+x] = currentPlayer;
        displayBoard(board);
        if (isWin = checkWin(currentPlayer, board)) break;
        (currentPlayer == 1) ? currentPlayer++ : currentPlayer--;
    }
    if (isWin) prompt((string) "Yaass! Player "+PLAYER_KEY[currentPlayer]+" has won! Type any key to exit ");
    else prompt((string) "Eh! It's a draw... Type any key to exit ");
    return 0;
}

void displayWelcome() {
    cout << "================================================================================" << endl;
    cout << "                  ███ █ ███    ███ ███ █▀▀    ███ ███ █▀▀                       " << endl;
    cout << "                   █  █ █   ██  █  █▄█ █   ██  █  █ █ █▇                       " << endl;
    cout << "                   █  █ ███     █  █ █ █▄▄     █  ███ █▄▄                       " << endl;
    cout << "================================================================================" << endl;
}

void displayBoard(uint8_t* board) {
    cout << endl;
    for (int i=0; i<=6; i++) {
        displayBoardLine(board, i);
        cout << endl;
    }
}