//
// Created by LOKKA on 2020/7/22.
//

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node *left, *right;
};

int GetHeight(Node *root) {
    if (root == NULL) return 0;
    return max(GetHeight(root->left), GetHeight(root->right)) + 1;
}

Node* L(Node *root) {
    Node *t = root->right;
    root->right = t->left;
    t->left = root;
    return t;
}

Node* R(Node *root) {
    Node *t = root->left;
    root->left = t->right;
    t->right = root;
    return t;
}

Node* Insert(Node *root, int val) {
    if (root == NULL) {
        root = new Node();
        root->val = val;
        root->left = root->right = NULL;
    } else if (val < root->val) {
        root->left = Insert(root->left, val);
        if (GetHeight(root->left) - GetHeight(root->right) == 2) {
            if (val < root->left->val) {  // LL 型
                root = R(root);
            } else {  // LR 型
                root->left = L(root->left);
                root = R(root);
            }
        }
    } else {
        root->right = Insert(root->right, val);
        if (GetHeight(root->left) - GetHeight(root->right) == -2) {
            if (val >= root->right->val) {  // RR 型
                root = L(root);
            } else {  // RL 型
                root->right = R(root->right);
                root = L(root);
            }
        }
    }
    return root;
}

int main() {
    int N, val;
    cin >> N;
    Node *root = NULL;
    for (int i = 0; i < N; i++) {
        cin >> val;
        root = Insert(root, val);
    }
    cout << root->val;
}