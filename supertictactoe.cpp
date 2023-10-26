#include "common.h"

void displayWelcome();
void displayBigBoard(uint8_t** board);
void displayWinGrid(uint8_t player, uint8_t line);
void displayDrawGrid(uint8_t line);
bool checkGameWin(uint8_t player, uint8_t** board);

uint8_t** board;
coord inputCoord;

int main() {
    uint8_t x, y, a, b;    // a, b is the coord of the outer grid
    uint8_t player = 1;
    inputCoord.x, inputCoord.y = 20;
    board = new uint8_t*[9];
    for (int i=0;i<9;i++)
        board[i] = new uint8_t[9]();
    displayWelcome();
    prompt("==============================Type Any Key To Start=============================");
        inputGrid:
        displayBigBoard(board);
        inputCoord = promptCoord(
            (string) "Player "+PLAYER_KEY[player]+", select the grid you want to play [column (1-3)]: ",
            (string) "Player "+PLAYER_KEY[player]+", select the grid you want to play [row (1-3)]: "
        );
        a = inputCoord.x; b = inputCoord.y;
        checkGrid:
        // Play grid if not already won or a draw
        if (checkWin(1, board[3*b+a]) || checkWin(2, board[3*b+a]) || checkDraw(board[3*b+a])) {
            prompt("This grid is complete, please pick another grid (Type and enter to continue)");
            goto inputGrid;
        }
        inputCell:
        displayBigBoard(board);
        inputCoord = promptCoord(
            (string) "Player "+PLAYER_KEY[player]+", pick your column [1-3] ",
            (string) "Player "+PLAYER_KEY[player]+", pick your row [1-3] "
        );
        x = inputCoord.x; y = inputCoord.y;
        if (board[3*b+a][y*3+x] > 0){
            prompt("That cell has been filled in, select another one (Type and enter to continue)");
            goto inputCell;
        }
        board[3*b+a][y*3+x] = player;
        /* Check win/draw states */
        if (checkWin(player, board[3*b+a]))
            cout << "Yaass! Player " << PLAYER_KEY[player] << " has won and claimed grid (" << a+1 << ", " << b+1 << ")" << endl;
        else if (checkDraw(board[3*b+a]))
            cout << "Eh... Grid (" << a+1 << ", " << b+1 << ") results in a draw. This means both players claim it" << endl;
        if (checkGameWin(player, board)) {
            cout << "Yaaaassss!!! Player " << PLAYER_KEY[player] << " has won the game! Congrats!" << endl;
            displayBigBoard(board);
            return 0;
        }
        // Check if all grids have been claimed. If so, winner goes to the most claimed grids
        uint8_t p1Count, p2Count = 0;
        for (int i=0; i<9; i++) {
            if (checkWin(1, board[i])) p1Count++;
            else if (checkWin(2, board[i])) p2Count++;
            else if (checkDraw(board[i])) p1Count++, p2Count++;
            else {  // Grid not yet claimed, so game is still on
                p1Count = p2Count = 0; break;
            } 
        }
        if (p1Count > p2Count) {
            cout << "Yaaaassss!!! Player " << PLAYER_KEY[1] << " has won the game by having the most claims! Congrats!" << endl;
            displayBigBoard(board);
            return 0;
        } else if (p1Count < p2Count) {
            cout << "Yaaaassss!!! Player " << PLAYER_KEY[2] << " has won the game by having the most claims! Congrats!" << endl;
            displayBigBoard(board);
            return 0;
        } else if (p1Count > 0 && p2Count > 0) {
            cout << "Eh... It's a draw" << endl;
            displayBigBoard(board);
            return 0;
        }
        // Continue game
        a = x; b = y;
        (player == 1) ? player++ : player--;
        cout << "Checking if grid (" << a+1 << ", " << b+1 << ") can be played..." << endl;
        goto checkGrid;
}

void displayWelcome() {
    cout << "================================================================================" << endl;
    cout << "        ▛▀▀ █ █ █▀▜ █▀▀ █▀█     ███ █ ███    ███ ███ █▀▀    ███ ███ █▀▀         " << endl;
    cout << "        ▀▇▄ █ █ █▄▟ █▇  ██▀      █  █ █   ██  █  █▄█ █   ██  █  █ █ █▇          " << endl;
    cout << "        ▄▄▟ ███ █   █▄▄ █ ▚      █  █ ███     █  █ █ █▄▄     █  ███ █▄▄         " << endl;
    cout << "================================================================================" << endl;
}

void displayBigBoard(uint8_t** board) {
    cout << endl;
    for (int i=0; i<3; i++) {
        for (int l=0; l<=6; l++) {  // Iterates over each line of sub grid image
            for (int j=0; j<3; j++) {
                cout << ((inputCoord.y == i && inputCoord.x == j) ? '|' : ' ');
                if (checkWin(1, board[3*i+j]))
                    displayWinGrid(1, l);
                else if (checkWin(2, board[3*i+j]))
                    displayWinGrid(2, l);
                else if (checkDraw(board[3*i+j]))
                    displayDrawGrid(l);
                else
                    displayBoardLine(board[3*i+j], l);
                cout << ((inputCoord.y == i && inputCoord.x == j) ? '|' : ' ');
            }
            cout << endl;
        }
    }
}

void displayWinGrid(uint8_t player, uint8_t line) {
    char key = PLAYER_KEY[player];
    switch (line) {
        case 0:
            if (key == 'X') cout << "             ";
            else cout << "     ---     ";
            break;
        case 1:
            if (key == 'X') cout << "    \\   /    ";
            else cout << "    /   \\    ";
            break;
        case 2:
            if (key == 'X') cout << "     \\ /     ";
            else cout << "   |     |   ";
            break;
        case 3:
            if (key == 'X') cout << "      X      ";
            else cout << "   |     |   ";
            break;
        case 4:
            if (key == 'X') cout << "     / \\     ";
            else cout << "   |     |   ";
            break;
        case 5:
            if (key == 'X') cout << "    /   \\    ";
            else cout << "    \\   /    ";
            break;
        case 6:
            if (key == 'X') cout << "             ";
            else cout << "     ---     ";
            break;
        default:
            throw out_of_range("line param not between 0 - 6");
    }
}

void displayDrawGrid(uint8_t line) {
    switch (line) {
        case 0:
            cout << "     --      "; break;
        case 1:
            cout << "    / | /    "; break;
        case 2:
            cout << "   |  |/     "; break;
        case 3:
            cout << "   |  X      "; break;
        case 4:
            cout << "   |  |\\     "; break;
        case 5:
            cout << "    \\ | \\    "; break;
        case 6:
            cout << "     --      "; break;
        default:
            throw out_of_range("line param not between 0 - 6");
    }
}

bool checkGameWin(uint8_t player, uint8_t** board) {
    auto checkClaim = [=](uint8_t* board) {
        return checkWin(player, board) || checkDraw(board);
    };
    // Check rows and columns
    for (int i=0; i<3; i++) {
        if (checkClaim(board[3*i]) && checkClaim(board[3*i+1]) && checkClaim(board[3*i+2])) return true;
        if (checkClaim(board[i]) && checkClaim(board[3+i]) && checkClaim(board[6+i])) return true;
    }
    // Check diagonals
    if (checkClaim(board[0]) && checkClaim(board[4]) && checkClaim(board[8])) return true;
    if (checkClaim(board[2]) && checkClaim(board[4]) && checkClaim(board[6])) return true;
    return false;
}
