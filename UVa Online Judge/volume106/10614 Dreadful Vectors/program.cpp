// Dreadful Vectors
// UVa ID: 10614
// Verdict: Accepted
// Submission Date: 2026-06-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Vector {
    int x, y, z;
    Vector(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z) {}
    Vector operator+(const Vector& o) const { return Vector(x + o.x, y + o.y, z + o.z); }
    Vector operator-(const Vector& o) const { return Vector(x - o.x, y - o.y, z - o.z); }
    int operator*(const Vector& o) const { return x * o.x + y * o.y + z * o.z; }      // 点积
    Vector operator^(const Vector& o) const { return Vector(y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x); } // 叉积
    Vector operator*(int k) const { return Vector(x * k, y * k, z * k); }
};

struct Expr {
    bool isVec;
    int val;
    Vector vec;
    Expr(int v) : isVec(false), val(v) {}
    Expr(Vector v) : isVec(true), vec(v) {}
};

class Parser {
    string s;
    int p;
    bool err;
    
    void skip() { while (p < s.size() && s[p] == ' ') p++; }
    char peek() { skip(); return p < s.size() ? s[p] : 0; }
    char get() { skip(); return p < s.size() ? s[p++] : 0; }
    bool isNum(char c) { return c >= '0' && c <= '9'; }
    
    int readNum() {
        if (!isNum(peek())) { err = true; return 0; }
        int x = 0;
        while (isNum(peek())) x = x * 10 + (get() - '0');
        return x;
    }
    
    Expr primary() {
        char c = peek();
        if (c == '(') {
            get();
            Expr e = expr();
            if (err) return Expr(0);
            if (peek() != ')') err = true;
            else get();
            return e;
        }
        if (c == '[') {
            get();
            Expr x = expr();
            if (err || x.isVec) { err = true; return Expr(0); }
            if (peek() != ',') { err = true; return Expr(0); }
            get();
            Expr y = expr();
            if (err || y.isVec) { err = true; return Expr(0); }
            if (peek() != ',') { err = true; return Expr(0); }
            get();
            Expr z = expr();
            if (err || z.isVec) { err = true; return Expr(0); }
            if (peek() != ']') { err = true; return Expr(0); }
            get();
            return Expr(Vector(x.val, y.val, z.val));
        }
        if (isNum(c)) return Expr(readNum());
        err = true;
        return Expr(0);
    }
    
    Expr mul() {
        Expr left = primary();
        if (err) return Expr(0);
        while (true) {
            char op = peek();
            if (op == '*') {
                get();
                Expr right = primary();
                if (err) return Expr(0);
                if (!left.isVec && !right.isVec) left = Expr(left.val * right.val);
                else if (!left.isVec && right.isVec) left = Expr(right.vec * left.val);
                else if (left.isVec && !right.isVec) left = Expr(left.vec * right.val);
                else left = Expr(left.vec * right.vec);
            }
            else if (op == 'x') {
                get();
                Expr right = primary();
                if (err) return Expr(0);
                if (!left.isVec || !right.isVec) { err = true; return Expr(0); }
                left = Expr(left.vec ^ right.vec);
            }
            else break;
        }
        return left;
    }
    
    Expr expr() {
        Expr left = mul();
        if (err) return Expr(0);
        while (true) {
            char op = peek();
            if (op == '+' || op == '-') {
                get();
                Expr right = mul();
                if (err) return Expr(0);
                if (left.isVec && right.isVec) left = Expr(op == '+' ? left.vec + right.vec : left.vec - right.vec);
                else if (!left.isVec && !right.isVec) left = Expr(op == '+' ? left.val + right.val : left.val - right.val);
                else { err = true; return Expr(0); }
            }
            else break;
        }
        return left;
    }
    
public:
    Parser(const string& str) : s(str), p(0), err(false) {}
    Expr parse() {
        Expr res = expr();
        if (err) return Expr(0);
        skip();
        if (p != s.size()) err = true;
        return res;
    }
    bool hasErr() { return err; }
};

bool hasIllegal(const string& s) {
    for (char c : s) if (c != ' ' && !isdigit(c) && c != '+' && c != '-' && c != '*' && c != 'x' && c != ',' && c != '[' && c != ']' && c != '(' && c != ')') return true;
    return false;
}

bool spaceInNum(const string& s) {
    for (int i = 0; i < s.size(); i++) {
        if (isdigit(s[i])) {
            int j = i;
            while (j < s.size() && isdigit(s[j])) j++;
            int k = j;
            while (k < s.size() && s[k] == ' ') k++;
            if (k < s.size() && isdigit(s[k])) return true;
            i = j;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    while (getline(cin, line) && line != "#") {
        if (hasIllegal(line) || spaceInNum(line)) { cout << "Bang!" << endl; continue; }
        Parser parser(line);
        Expr res = parser.parse();
        if (parser.hasErr()) cout << "Bang!" << endl;
        else if (res.isVec) cout << "[" << res.vec.x << "," << res.vec.y << "," << res.vec.z << "]" << endl;
        else cout << res.val << endl;
    }
    return 0;
}
