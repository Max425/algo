#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Node {
    int val;
    int min_val;
    int priority;
    int size;
    bool rev;
    Node *left, *right;
    
    Node(int v) : val(v), min_val(v), priority(rand()), size(1), rev(false), left(nullptr), right(nullptr) {}
};

int getSize(Node *t) {
    return t ? t->size : 0;
}

int getMin(Node *t) {
    return t ? t->min_val : 2e9;
}

void push(Node *t) {
    if (t && t->rev) {
        t->rev = false;
        swap(t->left, t->right);
        if (t->left) t->left->rev ^= true;
        if (t->right) t->right->rev ^= true;
    }
}

void upd(Node *t) {
    if (t) {
        t->size = 1 + getSize(t->left) + getSize(t->right);
        t->min_val = min({t->val, getMin(t->left), getMin(t->right)});
    }
}

void split(Node *t, Node *&l, Node *&r, int key, int add = 0) {
    if (!t) {
        l = r = nullptr;
        return;
    }
    push(t);
    int curPos = add + getSize(t->left);
    if (curPos < key) {
        split(t->right, t->right, r, key, curPos + 1);
        l = t;
    } else {
        split(t->left, l, t->left, key, add);
        r = t;
    }
    upd(t);
}

Node* merge(Node *l, Node *r) {
    if (!l || !r) return l ? l : r;
    if (l->priority > r->priority) {
        push(l);
        l->right = merge(l->right, r);
        upd(l);
        return l;
    } else {
        push(r);
        r->left = merge(l, r->left);
        upd(r);
        return r;
    }
}

Node* reverseSegment(Node *root, int L, int R) {
    Node *t1, *t2, *t3;
    split(root, t1, t2, L - 1);
    split(t2, t2, t3, R - L + 1);
    if (t2) t2->rev ^= true;
    return merge(merge(t1, t2), t3);
}

int rangeMin(Node *&root, int L, int R) {
    Node *t1, *t2, *t3;
    split(root, t1, t2, L - 1);
    split(t2, t2, t3, R - L + 1);
    int ans = getMin(t2);
    root = merge(merge(t1, t2), t3);
    return ans;
}

void printTree(Node *t) {
    if (!t) return;
    push(t);
    printTree(t->left);
    cout << t->val << " ";
    printTree(t->right);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(0));
    
    int n, m;
    cin >> n >> m;
    
    Node *root = nullptr;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        root = merge(root, new Node(x));
    }
    
    while (m--) {
        int type, L, R;
        cin >> type >> L >> R;
        if (type == 1) {
            root = reverseSegment(root, L, R);
        } else {
            cout << rangeMin(root, L, R) << '\n';
        }
    }
    
    return 0;
}