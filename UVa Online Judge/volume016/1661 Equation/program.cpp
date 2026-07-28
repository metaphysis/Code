// Equation 
// UVa ID: 1661
// Verdict: Accepted
// Submission Date: 2026-07-28
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int MAXN = 100;

struct Fraction {
    LL p, q;
    Fraction(LL a = 0, LL b = 1) {
        p = a;
        q = b;
        simplify();
    }
    void simplify() {
        if (q < 0) { q = -q; p = -p; }
        LL g = __gcd(llabs(p), llabs(q));
        if (g != 0) { p /= g; q /= g; }
    }
    Fraction operator-() const { return Fraction(-p, q); }
    Fraction operator+(const Fraction& other) const {
        return Fraction(p * other.q + other.p * q, q * other.q);
    }
    Fraction operator-(const Fraction& other) const {
        return Fraction(p * other.q - other.p * q, q * other.q);
    }
    Fraction operator*(const Fraction& other) const {
        return Fraction(p * other.p, q * other.q);
    }
    Fraction operator/(const Fraction& other) const {
        return Fraction(p * other.q, q * other.p);
    }
    bool isZero() const { return p == 0; }
    bool isOne() const { return p == q; }
};

struct Node {
    Node *left, *right;
    char op;
    Fraction val;
    bool hasX;
    Node(): left(NULL), right(NULL), op('N'), val(0), hasX(false) {}
    Node(Fraction v): left(NULL), right(NULL), op('N'), val(v), hasX(false) {}
    Node(char c): left(NULL), right(NULL), op(c), val(0), hasX(c == 'X') {}
};

Node pool[MAXN];
int poolCnt;

Node* newNode(Fraction v) {
    pool[poolCnt] = Node(v);
    return &pool[poolCnt++];
}

Node* newNode(char c) {
    pool[poolCnt] = Node(c);
    return &pool[poolCnt++];
}

Node* newNode(char op, Node* l, Node* r) {
    pool[poolCnt].op = op;
    pool[poolCnt].left = l;
    pool[poolCnt].right = r;
    pool[poolCnt].hasX = l->hasX || r->hasX;
    pool[poolCnt].val = 0;
    return &pool[poolCnt++];
}

Fraction calc(Fraction a, Fraction b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default: return Fraction(0, 1);
    }
}

Node* simplify(Node* root) {
    if (!root) return NULL;
    if (!root->hasX) {
        if (root->op == 'N') return root;
        Fraction lv = simplify(root->left)->val;
        Fraction rv = simplify(root->right)->val;
        root->val = calc(lv, rv, root->op);
        root->op = 'N';
        root->left = root->right = NULL;
        return root;
    }
    root->left = simplify(root->left);
    root->right = simplify(root->right);
    if (root->op == '*') {
        if (root->left->hasX && root->right->op == 'N' && root->right->val.isZero()) {
            root->hasX = false;
            root->val = Fraction(0, 1);
            root->op = 'N';
            root->left = root->right = NULL;
        } else if (root->right->hasX && root->left->op == 'N' && root->left->val.isZero()) {
            root->hasX = false;
            root->val = Fraction(0, 1);
            root->op = 'N';
            root->left = root->right = NULL;
        }
    } else if (root->op == '/') {
        if (root->right->hasX && root->left->op == 'N' && root->left->val.isZero()) {
            root->hasX = false;
            root->val = Fraction(0, 1);
            root->op = 'N';
            root->left = root->right = NULL;
        }
    }
    return root;
}

struct Result {
    Fraction coef;
    Fraction constant;
    Result(Fraction c = Fraction(0, 1), Fraction b = Fraction(0, 1)): coef(c), constant(b) {}
};

Result solveEquation(Node* root, Fraction target) {
    if (!root) return Result(Fraction(0, 1), Fraction(0, 1));
    if (root->op == 'N') {
        return Result(Fraction(0, 1), root->val - target);
    }
    if (root->op == 'X') {
        return Result(Fraction(1, 1), -target);
    }
    if (root->left->hasX) {
        Fraction rv = root->right->val;
        switch (root->op) {
            case '+': return solveEquation(root->left, target - rv);
            case '-': return solveEquation(root->left, target + rv);
            case '*': {
                if (rv.isZero()) {
                    if (target.isZero()) return Result(Fraction(0, 1), Fraction(0, 1));
                    else return Result(Fraction(0, 1), Fraction(1, 1));
                }
                return solveEquation(root->left, target / rv);
            }
            case '/': return solveEquation(root->left, target * rv);
            default: return Result(Fraction(0, 1), Fraction(0, 1));
        }
    } else {
        Fraction lv = root->left->val;
        switch (root->op) {
            case '+': return solveEquation(root->right, target - lv);
            case '-': return solveEquation(root->right, lv - target);
            case '*': {
                if (lv.isZero()) {
                    if (target.isZero()) return Result(Fraction(0, 1), Fraction(0, 1));
                    else return Result(Fraction(0, 1), Fraction(1, 1));
                }
                return solveEquation(root->right, target / lv);
            }
            case '/': {
                if (target.isZero()) return Result(Fraction(0, 1), Fraction(1, 1));
                return solveEquation(root->right, lv / target);
            }
            default: return Result(Fraction(0, 1), Fraction(0, 1));
        }
    }
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string token;
    while (cin >> token) {
        poolCnt = 0;
        stack<Node*> st;

        vector<string> tokens;
        tokens.push_back(token);
        while (cin.peek() != '\n' && cin.peek() != EOF) {
            cin >> token;
            tokens.push_back(token);
        }

        for (size_t i = 0; i < tokens.size(); i++) {
            string s = tokens[i];
            if (s.size() == 1 && isOperator(s[0])) {
                Node* r = st.top(); st.pop();
                Node* l = st.top(); st.pop();
                st.push(newNode(s[0], l, r));
            } else if (s == "X") {
                st.push(newNode('X'));
            } else {
                LL num = 0;
                for (size_t j = 0; j < s.size(); j++) {
                    num = num * 10 + (s[j] - '0');
                }
                st.push(newNode(Fraction(num, 1)));
            }
        }

        Node* root = st.top();
        root = simplify(root);

        if (!root->hasX) {
            if (root->val.isZero()) {
                cout << "MULTIPLE\n";
            } else {
                cout << "NONE\n";
            }
            continue;
        }

        Result res = solveEquation(root, Fraction(0, 1));

        if (res.coef.isZero()) {
            if (res.constant.isZero()) {
                cout << "MULTIPLE\n";
            } else {
                cout << "NONE\n";
            }
        } else {
            Fraction ans = Fraction(-res.constant.p, res.constant.q) / res.coef;
            cout << "X = " << ans.p << "/" << ans.q << "\n";
        }
    }

    return 0;
}
