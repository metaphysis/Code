#include <bits/stdc++.h>
using namespace std;

struct Frac {
    long long a, b;
    Frac(long long a = 0, long long b = 1) : a(a), b(b) {
        norm();
    }
    long long getGcd(long long x, long long y) {
        x = x < 0 ? -x : x;
        y = y < 0 ? -y : y;
        while (y) {
            long long z = x % y;
            x = y;
            y = z;
        }
        return x;
    }
    void norm() {
        if (a == 0) {
            b = 1;
            return;
        }
        if (b < 0) {
            a = -a;
            b = -b;
        }
        long long g = getGcd(a, b);
        a /= g;
        b /= g;
    }
};

Frac add(Frac x, Frac y) {
    return Frac(x.a * y.b + y.a * x.b, x.b * y.b);
}

Frac mul(Frac x, Frac y) {
    return Frac(x.a * y.a, x.b * y.b);
}

struct Node {
    Frac val, der;
};

struct Parser {
    string str;
    Frac time;
    int pos;
    Parser(string str, Frac time) : str(str), time(time), pos(0) {}
    Frac parseFrac() {
        long long x = 0, y = 0;
        while (pos < (int)str.size() && isdigit(str[pos]))
            x = x * 10 + str[pos++] - '0';
        pos++;
        while (pos < (int)str.size() && isdigit(str[pos]))
            y = y * 10 + str[pos++] - '0';
        return Frac(x, y);
    }
    Node parseFactor() {
        if (str[pos] == '(') {
            pos++;
            Node res = parseExpr();
            pos++;
            return res;
        }
        if (str[pos] == 't') {
            pos++;
            return {time, Frac(1)};
        }
        return {parseFrac(), Frac(0)};
    }
    Node parseTerm() {
        Node res = parseFactor();
        while (pos < (int)str.size() && str[pos] == '*') {
            pos++;
            Node nxt = parseFactor();
            res = {mul(res.val, nxt.val), add(mul(res.der, nxt.val), mul(res.val, nxt.der))};
        }
        return res;
    }
    Node parseExpr() {
        Node res = parseTerm();
        while (pos < (int)str.size() && str[pos] == '+') {
            pos++;
            Node nxt = parseTerm();
            res = {add(res.val, nxt.val), add(res.der, nxt.der)};
        }
        return res;
    }
};

Frac readTime(string str) {
    int pos = 0, sign = 1;
    long long x = 0, y = 0;
    if (str[pos] == '-') {
        sign = -1;
        pos++;
    }
    while (pos < (int)str.size() && isdigit(str[pos]))
        x = x * 10 + str[pos++] - '0';
    pos++;
    if (str[pos] == '-') {
        sign = -sign;
        pos++;
    }
    while (pos < (int)str.size() && isdigit(str[pos]))
        y = y * 10 + str[pos++] - '0';
    return Frac(sign * x, y);
}

string toString(Frac x) {
    return to_string(x.a) + "/" + to_string(x.b);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string expr, line;
    int tc = 0;
    while (getline(cin, expr) && getline(cin, line)) {
        Frac time = readTime(line);
        Parser parser(expr, time);
        Node ans = parser.parseExpr();
        cout << "Case #" << ++tc << ": " << toString(ans.val) << " " << toString(ans.der) << '\n';
    }
    return 0;
}
