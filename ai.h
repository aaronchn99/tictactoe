#ifndef AI_H
#define AI_H
#include "common.h"
#include <queue>
using namespace std;

/* Random Play */
uint8_t randomPlay(uint8_t* board) {
    int cell;
    do {
        cell = 9*((float) rand()/RAND_MAX);
    } while (board[cell] > 0); 
    return cell;
}

/* Full Game Tree */
class Node {
public:
    int move;
    Node* parent;
    Node** children = new Node*[9]();
    int childrenTail = 0;
    int score;
    int d = 0;
    Node(int move, Node* parent=nullptr) : move(move), parent(parent) {
        if (parent != nullptr) {
            d = parent->d + 1;
        }
    }
    void expandNode(uint8_t* board, int player) {
        if (checkWin(1, board)) {
            score = 10-d;
            return;
        } else if (checkWin(2, board)) {
            score = d-10;
            return;
        } else if (checkDraw(board)) {
            score = 0;
            return;
        }
        for (int i=0; i<9; i++) {
            if (board[i] != 0) continue;
            board[i] = player;
            Node* child = new Node(i, this);
            children[childrenTail++] = child;
            child->expandNode(board, (player == 1) ? player+1 : player-1);
            board[i] = 0;
            // Player 1 is Maximin, Player 2 is minimax
            if (childrenTail == 1 || d%2 == 1 && child->score < score || d%2 == 0 && child->score > score) {
                score = child->score;
            }
        }
    };
};

ostream& operator <<(ostream &os, const Node &n) {
    return (os << "(" << n.move << " : " << n.score << ")");
}

Node* buildTree() {
    uint8_t* board = new uint8_t[9]();
    Node* root = new Node(-1);
    root->expandNode(board, 1);
    return root;
}




#endif