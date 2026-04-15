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

void split(Node *t, Node *&l, Node *&r, int key) {
    if (!t) {
        l = r = nullptr;
        return;
    }
    if (t->val < key) {
        split(t->right, t->right, r, key);
        l = t;
    } else {
        split(t->left, l, t->left, key);
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

Node* insert(Node *root, int val) {
    Node *l, *r;
    split(root, l, r, val);
    return merge(merge(l, new Node(val)), r);
}

Node* erase(Node *root, int val) {
    Node *l, *m, *r;
    split(root, l, m, val);
    split(m, m, r, val + 1);
    delete m;
    return merge(l, r);
}

int kthMax(Node *t, int k) {
    int total = getSize(t);
    int k_min = total - k + 1;
    
    while (t) {
        int leftSize = getSize(t->left);
        if (leftSize + 1 == k_min) {
            return t->val;
        } else if (leftSize >= k_min) {
            t = t->left;
        } else {
            k_min -= leftSize + 1;
            t = t->right;
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(0));
    
    int n;
    cin >> n;
    
    Node *root = nullptr;
    
    for (int i = 0; i < n; i++) {
        int cmd, k;
        cin >> cmd >> k;
        
        if (cmd == 1) {
            root = insert(root, k);
        } else if (cmd == -1) {
            root = erase(root, k);
        } else {
            cout << kthMax(root, k) << '\n';
        }
    }
    
    return 0;
}