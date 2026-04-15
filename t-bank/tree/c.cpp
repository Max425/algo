#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

long long gcd(long long a, long long b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

struct Node {
    long long val;
    int count;
    long long subtree_gcd;
    int priority;
    Node *left, *right;
    
    Node(long long v, int c = 1) : val(v), count(c), subtree_gcd(v), priority(rand()), left(nullptr), right(nullptr) {}
};

long long getGcd(Node *t) {
    return t ? t->subtree_gcd : 0;
}

void upd(Node *t) {
    if (t) {
        t->subtree_gcd = t->val;
        if (t->left) t->subtree_gcd = gcd(t->subtree_gcd, t->left->subtree_gcd);
        if (t->right) t->subtree_gcd = gcd(t->subtree_gcd, t->right->subtree_gcd);
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

Node* insert(Node *root, long long val) {
    Node *l, *m, *r;
    split(root, l, m, val);
    split(m, m, r, val + 1);
    
    if (m) {
        // Уже есть такой узел
        m->count++;
        upd(m);
    } else {
        m = new Node(val);
    }
    return merge(merge(l, m), r);
}

Node* erase(Node *root, long long val) {
    Node *l, *m, *r;
    split(root, l, m, val);
    split(m, m, r, val + 1);
    
    if (m) {
        m->count--;
        if (m->count == 0) {
            delete m;
            m = nullptr;
        } else {
            upd(m);
        }
    }
    return merge(merge(l, m), r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(0));
    
    int q;
    cin >> q;
    
    Node *root = nullptr;
    
    while (q--) {
        char op;
        long long x;
        cin >> op >> x;
        
        if (op == '+') {
            root = insert(root, x);
        } else {
            root = erase(root, x);
        }
        
        long long ans = root ? root->subtree_gcd : 1;
        cout << ans << '\n';
    }
    
    return 0;
}