#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Node {
    int val;
    int priority;
    int size;
    Node *left, *right;
    
    Node(int v) : val(v), priority(rand()), size(1), left(nullptr), right(nullptr) {}
};

int getSize(Node *t) {
    return t ? t->size : 0;
}

void updSize(Node *t) {
    if (t) t->size = 1 + getSize(t->left) + getSize(t->right);
}


void split(Node *t, Node *&l, Node *&r, int key, int add = 0) {
    if (!t) {
        l = r = nullptr;
        return;
    }
    int curPos = add + getSize(t->left);
    if (curPos < key) {
        split(t->right, t->right, r, key, curPos + 1);
        l = t;
    } else {
        split(t->left, l, t->left, key, add);
        r = t;
    }
    updSize(t);
}

Node* merge(Node *l, Node *r) {
    if (!l || !r) return l ? l : r;
    if (l->priority > r->priority) {
        l->right = merge(l->right, r);
        updSize(l);
        return l;
    } else {
        r->left = merge(l, r->left);
        updSize(r);
        return r;
    }
}

void printTree(Node *t) {
    if (!t) return;
    printTree(t->left);
    cout << t->val << " ";
    printTree(t->right);
}


Node* moveToFront(Node *root, int L, int R) {
    Node *t1, *t2, *t3, *t4;
    
    split(root, t1, t2, L - 1);

    split(t2, t3, t4, R - L + 1);
    
    return merge(merge(t3, t1), t4);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(0));
    
    int n, m;
    cin >> n >> m;
    
    Node *root = nullptr;
    
    for (int i = 1; i <= n; i++) {
        root = merge(root, new Node(i));
    }
    
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        root = moveToFront(root, l, r);
    }
    
    printTree(root);
    cout << endl;
    
    return 0;
}