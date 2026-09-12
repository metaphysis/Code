#include <bits/stdc++.h>
using namespace std;

int n, m;
int id(int a, int b) { return a * m + b; }

struct State {
    string s, op;
    int w, step;
    State(string s = " ", int w = 0, int step = 0) : s(s), w(w), step(step) { op.clear(); }
    bool operator < (const State& b) const { return s < b.s || (s == b.s && w < b.w); }
};

set<State> dic;

int fall(string& s) {
    for (int i = n - 1; i >= 0; i--)
        for (int j = 0; j < m; j++) {
            int left = id(i, j);
            if (s[left] == '@' || s[left] == 'O') {
                int down = left + m;
                while (down < m * n && s[down] == '.') down += m;
                down -= m;
                if (left != down) swap(s[left], s[down]); // note that wh might equal to L, so swap is a good way to do the change
            } else if (s[left] == '[') {
                for (int k = j + 1; k < m; k++) {
                    int right = id(i, k);
                    if (s[right] == 'X') break;
                    if (s[right] == ']') {
                        int to = 0;
                        for (int l = i + 1; l < n; l++) {
                            bool ok = true;
                            for (int ii = j; ii <= k; ii++)
                                if (s[id(l, ii)] != '.') {
                                    ok = false;
                                    break;
                                }
                            if (!ok) {
                                to = l - 1;
                                break;
                            }
                        }
                        if (to != i)
                            for (int l = j; l <= k; l++) swap(s[id(i, l)], s[id(to, l)]);
                        j = k;
                        break;
                    }
                }
            }
        }
    for (int i = 0; i < s.size(); i++)
        if (s[i] == '@') return i;
    return -1;
}

void linkRight(char& c) {
    if (c == ']') c = '=';
    else if (c == 'O') c = '[';
}

void linkLeft(char& c) {
    if (c == '[') c = '=';
    else if (c == 'O') c = ']';
}

bool solveMagic(State& s, int x, int y) {
    int pos = id(x, y);
    if (s.s[pos] == 'X') return false;
    if (s.s[pos] == '.') {
        if (s.s[pos - 1] != '.' && s.s[pos + 1] != '.') {
            s.s[pos] = '=';
            linkRight(s.s[pos - 1]);
            linkLeft(s.s[pos + 1]);
        } else if (s.s[pos - 1] != '.') {
            s.s[pos] = ']';
            linkRight(s.s[pos - 1]);
        } else if (s.s[pos + 1] != '.') {
            s.s[pos] = '[';
            linkLeft(s.s[pos + 1]);
        } else s.s[pos] = 'O';
    } else {
        s.s[pos] = '.';
        if (s.s[pos - 1] == '=') s.s[pos - 1] = ']';
        if (s.s[pos - 1] == '[') s.s[pos - 1] = 'O';
        if (s.s[pos + 1] == '=') s.s[pos + 1] = '[';
        if (s.s[pos + 1] == ']') s.s[pos + 1] = 'O';
    }
    s.w = fall(s.s);
    return true;
}

bool solveMove(State& s, int k) {
    int pos = s.w + k;
    if (s.s[pos] == '.') swap(s.s[s.w], s.s[pos]);
    else if (s.s[pos] == 'O' && s.s[pos + k] == '.') {
        int down = pos;
        while (s.s[down + k] == '.') {
            down += k;
            if (s.s[down + m] == '.') break;
        }
        swap(s.s[pos], s.s[down]);
    } else if (s.s[pos - m] == '.' && s.s[s.w - m] == '.') swap(s.s[s.w], s.s[pos - m]);
    else return false;
    s.w = fall(s.s);
    return true;
}

void printNow(string s) {
    cout << endl;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) cout << s[id(i, j)] << (j == m - 1 ? "\n" : "");
}

int main(int argc, char* argv[]) {
    int caseNum = 0;
    while (cin >> n && n && cin >> m) {
        dic.clear();
        string s;
        char op;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                cin >> op;
                s = s + op;
            }
        int start = 0, target = 0, targetX, targetY;
        for (int i = 0; i < s.size(); i++)
            if (s[i] == '@') start = i;
            else if (s[i] == '#') {
                target = i;
                s[i] = '.';
            }
        targetX = target / m;
        targetY = target % m;
        queue<State> q;
        q.push(State(s, start, 0));
        cout << "Case " << ++caseNum << ": ";
        while (!q.empty()) {
            State now = q.front(), next;
            q.pop();
            if (now.w == target) {
                cout << now.op;
                break;
            }
            int x = now.w / m, y = now.w % m;
            if (abs(y - targetY) + now.step > 15) continue;
            next = now;
            if (solveMagic(next, x + 1, y + 1)) {
                next.op.push_back('>');
                next.step++;
                if (dic.count(next) == 0) {
                    dic.insert(next);
                    q.push(next);
                }
            }
            next = now;
            if (solveMagic(next, x + 1, y - 1)) {
                next.op.push_back('<');
                next.step++;
                if (dic.count(next) == 0) {
                    dic.insert(next);
                    q.push(next);
                }
            }
            next = now;
            if (solveMove(next, -1)) {
                next.op.push_back('L');
                if (dic.count(next) == 0) {
                    dic.insert(next);
                    q.push(next);
                }
            }
            next = now;
            if (solveMove(next, +1)) {
                next.op.push_back('R');
                if (dic.count(next) == 0) {
                    dic.insert(next);
                    q.push(next);
                }
            }
        }
        cout << endl;
    }
    return 0;
}
