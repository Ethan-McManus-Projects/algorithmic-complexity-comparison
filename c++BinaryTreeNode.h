#ifndef BINARYTREENODE_H
#define BINARYTREENODE_H

class BinaryTreeNode {
public:
    int data;
    BinaryTreeNode* left;
    BinaryTreeNode* right;

    // init node
    BinaryTreeNode(int value) : data(value), left(nullptr), right(nullptr) {}

    // free memory
    ~BinaryTreeNode() {
        delete left;
        delete right;
    }

    // add left node
    void insertLeft(int value) {
        if (!left) {
            left = new BinaryTreeNode(value);
        } else {
            BinaryTreeNode* newNode = new BinaryTreeNode(value);
            newNode->left = left;
            left = newNode;
        }
    }

    // add right node
    void insertRight(int value) {
        if (!right) {
            right = new BinaryTreeNode(value);
        } else {
            BinaryTreeNode* newNode = new BinaryTreeNode(value);
            newNode->right = right;
            right = newNode;
        }
    }
};

#endif
