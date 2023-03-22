#include <random>
#include <iostream>
#include <ctime>
#include <chrono>
using namespace std;


struct node {
    node* left, * right;

    int data;

    node(int data) {
        this->data = data;
        this->left = this->right = NULL;
    }
};


void nodeInorder(node* root, bool last) {
    if (root != NULL) {
        nodeInorder(root->left, false);

        cout << root->data << (last && root->right == NULL ? "\n" : " -> ");

        nodeInorder(root->right, last);
    }
}

node* nodeInsert(node* root, int data) {
    if (root == NULL) return new node(data);

    if (data < root->data)
        root->left = nodeInsert(root->left, data);
    else
        root->right = nodeInsert(root->right, data);

    return root;
}

node* nodeMinValueNode(node* root) {
    node* current = root;

    while (current && current->left != NULL)
        current = current->left;

    return current;
}

node* nodeDeleteNode(node* root, int data) {
    if (root == NULL) return root;

    if (data < root->data)
        root->left = nodeDeleteNode(root->left, data);
    else if (data > root->data)
        root->right = nodeDeleteNode(root->right, data);
    else {
        if (root->left == NULL) {
            node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            node* temp = root->left;
            free(root);
            return temp;
        }

        node* temp = nodeMinValueNode(root->right);

        root->data = temp->data;

        root->right = nodeDeleteNode(root->right, temp->data);
    }
    return root;
}


class binTree {
private:
    node* root = NULL;

public:
    void insertNode(int data) {
        this->root = nodeInsert(this->root, data);
    }

    void inorder() {
        nodeInorder(this->root, true);
    }

    void deleteNode(int data) {
        this->root = nodeDeleteNode(this->root, data);
    }
private:
    int h(node* r) {
        if (r->left == NULL && r->right == NULL)
            return 1;
        if (r->left != NULL && r->right == NULL)
            return h(r->left) + 1;
        if (r->left == NULL && r->right != NULL)
            return h(r->right) + 1;
        return max(h(r->left), h(r->right)) + 1;
    }

public:
    int h() {
        return h(this->root);
    }
};


int main() {
    setlocale(0, "");


    binTree tree;

    auto start = chrono::high_resolution_clock::now();

    /*for (int i = 0; i < 500; i++)
    {
        int t = i;

        tree.insertNode(t);
    }*/

    for (int i = 0; i < 500; i++)
    {
        int t = rand() % 500;
        
        tree.insertNode(t);
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<float> duration = end - start;
    std::cout << "t" << duration.count() * 1000 << "\n";

    std::cout << tree.h();
}