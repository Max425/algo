#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const long long MOD = 1000000000LL;

struct Node {
    long long val;
    int priority;
    Node *left, *right;
    
    Node(long long v) : val(v), priority(rand()), left(nullptr), right(nullptr) {}
};


void split(Node *t, Node *&l, Node *&r, long long key) {
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
}


Node* merge(Node *l, Node *r) {
    if (!l || !r) return l ? l : r;
    if (l->priority > r->priority) {
        l->right = merge(l->right, r);
        return l;
    } else {
        r->left = merge(l, r->left);
        return r;
    }
}


bool exists(Node *t, long long val) {
    if (!t) return false;
    if (t->val == val) return true;
    if (val < t->val) return exists(t->left, val);
    return exists(t->right, val);
}


Node* insert(Node *root, long long val) {
    if (exists(root, val)) return root;
    Node *l, *r;
    split(root, l, r, val);
    return merge(merge(l, new Node(val)), r);
}

long long findNext(Node *t, long long val) {
    long long ans = -1;
    while (t) {
        if (t->val >= val) {
            ans = t->val;
            t = t->left;
        } else {
            t = t->right;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(0));
    
    int n;
    cin >> n;
    
    Node *root = nullptr;
    long long lastAns = 0;
    bool lastWasQuery = false;
    
    for (int i = 0; i < n; i++) {
        char op;
        cin >> op;
        
        if (op == '+') {
            long long x;
            cin >> x;
            if (lastWasQuery) {
                x = (x + lastAns) % MOD;
                lastWasQuery = false;
            }
            root = insert(root, x);
        } else { // op == '?'
            long long x;
            cin >> x;
            lastAns = findNext(root, x);
            cout << lastAns << '\n';
            lastWasQuery = true;
        }
    }
    
    return 0;
}