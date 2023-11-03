#include "common.h"

void displayWelcome();
void displayBoard(uint8_t* board);
uint8_t playHuman(uint8_t* board, char playerKey);
uint8_t playCPU(uint8_t* board);

uint8_t* board;

int main() {
    srand(time(nullptr));
    uint8_t currentPlayer = 1;
    bool isWin = false;
    board = new uint8_t[9]();
    displayWelcome();
    prompt("==============================Type Any Key To Start=============================");
    displayBoard(board);
    for (int t=0; t<9; t++) {
        uint8_t cell;
        cell = (currentPlayer == 1) ? playHuman(board, PLAYER_KEY[currentPlayer]) : playCPU(board);
        board[cell] = currentPlayer;
        displayBoard(board);
        if (isWin = checkWin(currentPlayer, board)) break;
        (currentPlayer == 1) ? currentPlayer++ : currentPlayer--;
    }
    if (isWin) prompt((string) "Yaass! Player "+PLAYER_KEY[currentPlayer]+" has won! Type any key to exit ");
    else prompt((string) "Eh! It's a draw... Type any key to exit ");
    return 0;
}

uint8_t playHuman(uint8_t* board, char playerKey) {
    uint8_t cell;
    do {
        coord input = promptCoord(
            (string) "Player "+playerKey+", pick your column [1-3] ",
            (string) "Player "+playerKey+", pick your row [1-3] "
        );
        cell = input.y*3 + input.x;
        if (board[cell] > 0)
            cout << "That cell has been filled in, select another one" << endl;
    } while (board[cell] > 0);
    return cell;
}

uint8_t playCPU(uint8_t* board) {
    int cell;
    do {
        cell = 9*((float) rand()/RAND_MAX);
    } while (board[cell] > 0); 
    return cell;
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