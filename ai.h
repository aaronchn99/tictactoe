#ifndef AI_H
#define AI_H
#include "common.h"
#include <unordered_map>
#include <climits>
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
    static unordered_map<string, Node*> NodeMap;
    int move;
    Node* parent;
    Node** children = new Node*[9]();
    int childrenTail = 0;
    int score;
    int d = 0;
    bool incomplete = false;    // Flags if node has been pruned
    Node(int move, Node* parent=nullptr) : move(move), parent(parent) {
        if (parent != nullptr) {
            d = parent->d + 1;
        }
    }
    void expandNode(uint8_t* board, int player, int a=INT_MIN, int b=INT_MAX) {
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
        score = (player == 1) ? INT_MIN : INT_MAX;
        for (int i=0; i<9; i++) {
            if (board[i] != 0) continue;
            board[i] = player;
            Node* child = new Node(i, this);
            children[childrenTail++] = child;
            child->expandNode(board, (player == 1) ? player+1 : player-1, a, b);
            board[i] = 0;
            // Alpha/Beta cutoff
            if (player == 1) {
                score = max(score, child->score);
                if (score > b) {
                    incomplete = true;
                    return;
                }
                a = max(a, score);
            } else {
                score = min(score, child->score);
                if (score < a) {
                    incomplete = true;
                    return;
                }
                b = min(b, score);
            }
            // Player 1 is Maximising, Player 2 is Minimising
        }
    };
    static Node* buildTree(Node* root = new Node(-1), int player = 1) {
        uint8_t* board = new uint8_t[9]();
        root->expandNode(board, player);
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