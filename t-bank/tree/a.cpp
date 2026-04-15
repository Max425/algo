#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const long long MOD = 1000000000LL;

struct Node {
    long long val;
    long long sum;
    int priority;
    Node *left, *right;
    
    Node(long long v) : val(v), sum(v), priority(rand()), left(nullptr), right(nullptr) {}
};

long long getSum(Node *t) {
    return t ? t->sum : 0;
}

void upd(Node *t) {
    if (t) {
        t->sum = t->val + getSum(t->left) + getSum(t->right);
    }
}

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
    upd(t);
}

Node* merge(Node *l, Node *r) {
    if (!l || !r) return l ? l : r;
    if (l->priority > r->priority) {
        l->right = merge(l->right, r);
        upd(l);
        return l;
    } else {
        r->left = merge(l, r->left);
        upd(r);
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

long long rangeSum(Node *&root, long long L, long long R) {
    Node *t1, *t2, *t3, *t4;
    split(root, t1, t2, L);
    split(t2, t3, t4, R + 1);
    
    long long ans = getSum(t3);
    
    root = merge(t1, merge(t3, t4));
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
    
    for (int i = 0; i < n; i++) {
        char op;
        cin >> op;
        
        if (op == '+') {
            long long x;
            cin >> x;
            if (lastAns != 0) {
                x = (x + lastAns) % MOD;
                lastAns = 0;
            }
            root = insert(root, x);
        } else {
            long long l, r;
            cin >> l >> r;
            lastAns = rangeSum(root, l, r);
            cout << lastAns << '\n';
        }
    }
    
    return 0;
}