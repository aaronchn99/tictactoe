#ifndef AI_H
#define AI_H
#include "common.h"
#include <unordered_map>
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
    static unordered_map<string, Node*> NodeMap;
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
        if (NodeMap.find(boardToString(board)) != NodeMap.end()) {
            score = NodeMap.find(boardToString(board))->second->score;
            return;
        }
        NodeMap[boardToString(board)] = this;
        if (checkWin(1, board)) {
            score = 10-d;
            return;
        }
        if (checkWin(2, board)) {
            score = d-10;
            return;
        }
        if (checkDraw(board)) {
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
    static Node* buildTree() {
        uint8_t* board = new uint8_t[9]();
        Node* root = new Node(-1);
        root->expandNode(board, 1);
        return root;
    }
    static void printTree(Node* root, int max_depth) {
        queue<Node*> NodeQueue;
        Node* node;
        int d = 0;
        NodeQueue.push(root);
        while (!NodeQueue.empty()) {
            node = NodeQueue.front();
            NodeQueue.pop();
            if (d < node->d) {
                cout << endl;
                d = node->d;
            }
            cout << "(" << node->move << " : " << node->score << ")";
            if (d < max_depth) {
                for (int i=0;i<node->childrenTail;i++){
                    NodeQueue.push(node->children[i]);
                }
            }
        }
    }
};
unordered_map<string, Node*> Node::NodeMap = unordered_map<string, Node*>();

ostream& operator <<(ostream &os, const Node &n) {
    return (os << "(" << n.move << " : " << n.score << ")");
}
#endif