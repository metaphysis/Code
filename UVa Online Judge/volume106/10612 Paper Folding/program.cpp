// Paper Folding
// UVa ID: 10612
// Verdict: Accepted
// Submission Date: 2026-07-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int SZ = 1048576;

struct Rect {
    int x1, x2, y1, y2, side;
    Rect(int a = 0, int b = 0, int c = 0, int d = 0, int s = 0) : x1(a), x2(b), y1(c), y2(d), side(s) {}
    int midX() const { return (x1 + x2) >> 1; }
    int midY() const { return (y1 + y2) >> 1; }
    void normalize() {
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
    }
};

pair<Rect, Rect> applyFold(char op, const Rect& front, const Rect& back) {
    Rect nf = front, nb = back;
    if (op == 'l') {
        int m = back.midX();
        nf = Rect(m, back.x1, back.y1, back.y2, back.side);
        nb = Rect(m, back.x2, back.y1, back.y2, back.side);
    } else if (op == 'r') {
        int m = back.midX();
        nf = Rect(back.x2, m, back.y1, back.y2, back.side);
        nb = Rect(back.x1, m, back.y1, back.y2, back.side);
    } else if (op == 't') {
        int m = back.midY();
        nf = Rect(back.x1, back.x2, m, back.y1, back.side);
        nb = Rect(back.x1, back.x2, m, back.y2, back.side);
    } else if (op == 'b') {
        int m = back.midY();
        nf = Rect(back.x1, back.x2, back.y2, m, back.side);
        nb = Rect(back.x1, back.x2, back.y1, m, back.side);
    } else if (op == 'L') {
        int m = front.midX();
        nb = Rect(m, front.x1, front.y1, front.y2, front.side);
        nf = Rect(m, front.x2, front.y1, front.y2, front.side);
    } else if (op == 'R') {
        int m = front.midX();
        nb = Rect(front.x2, m, front.y1, front.y2, front.side);
        nf = Rect(front.x1, m, front.y1, front.y2, front.side);
    } else if (op == 'T') {
        int m = front.midY();
        nb = Rect(front.x1, front.x2, m, front.y1, front.side);
        nf = Rect(front.x1, front.x2, m, front.y2, front.side);
    } else if (op == 'B') {
        int m = front.midY();
        nb = Rect(front.x1, front.x2, front.y2, m, front.side);
        nf = Rect(front.x1, front.x2, front.y1, m, front.side);
    }
    return {nf, nb};
}

void forwardSolve(const string& seq) {
    Rect front(0, SZ, 0, SZ, 0), back(0, SZ, 0, SZ, 1);
    for (char c : seq) {
        auto p = applyFold(c, front, back);
        front = p.first;
        back = p.second;
    }
    front.normalize();
    char sc = front.side ? 'B' : 'F';
    cout << "(" + to_string(front.x1) + "," + to_string(front.y1) + ")-(" +
           to_string(front.x2) + "," + to_string(front.y2) + ") " + sc << '\n';
}

void reverseSolve(const string& line) {
    int x1, y1, x2, y2;
    char sc;
    sscanf(line.c_str(), "(%d,%d)-(%d,%d) %c", &x1, &y1, &x2, &y2, &sc);
    Rect target(x1, x2, y1, y2, (sc == 'F' ? 0 : 1));
    int w = target.x2 - target.x1, h = target.y2 - target.y1;
    int cx = 0, cy = 0;
    for (int t = SZ / w; t > 1; t >>= 1) ++cx;
    for (int t = SZ / h; t > 1; t >>= 1) ++cy;
    Rect front(0, SZ, 0, SZ, 0);
    string s;
    while (cy) {
        if (cy == 1 && !cx) { s += target.side ? "bt"[target.y1 == front.y1] : "TB"[target.y1 == front.y1]; break; }
        int mid = front.midY();
        s += "Bb"[target.side];
        if (target.y1 >= mid) {
            target.side = !target.side;
            int oldY1 = target.y1, oldY2 = target.y2;
            target.y1 = front.y2 - oldY2;
            target.y2 = front.y2 - oldY1;
        }
        front.y2 = mid;
        --cy;
    }
    while (cx) {
        if (cx == 1) { s += target.side ? "rl"[target.x1 == front.x1] : "LR"[target.x1 == front.x1]; break; }
        int mid = front.midX();
        s += "Ll"[target.side];
        if (target.x2 <= mid) {
            target.side = !target.side;
            int oldX1 = target.x1, oldX2 = target.x2;
            target.x1 = front.x1 + front.x2 - oldX2;
            target.x2 = front.x1 + front.x2 - oldX1;
        }
        front.x1 = mid;
        --cx;
    }
    cout << s << '\n';
}

int main() {
    int n;
    cin >> n;
    string line;
    getline(cin, line);
    for (int i = 0; i < n; ++i) {
        getline(cin, line);
        if (line[0] == '(') reverseSolve(line);
        else forwardSolve(line);
    }
    return 0;
}
