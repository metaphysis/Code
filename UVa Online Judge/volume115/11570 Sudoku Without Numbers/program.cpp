#include <bits/stdc++.h>
using namespace std;

int a[9][9], rowMask[9], colMask[9], boxMask[9];
vector<int> low[81], high[81];

void addRel(int big, int small) {
    low[big].push_back(small);
    high[small].push_back(big);
}

void readH(const string &s, int x) {
    stringstream ss(s);
    char ch;
    int block, k, y;
    for (block = 0; block < 3; block++)
        for (k = 0; k < 2; k++) {
            ss >> ch;
            y = block * 3 + k;
            if (ch == '>') addRel(x * 9 + y, x * 9 + y + 1);
            else addRel(x * 9 + y + 1, x * 9 + y);
        }
}

void readV(const string &s, int x) {
    stringstream ss(s);
    char ch;
    int y;
    for (y = 0; y < 9; y++) {
        ss >> ch;
        if (ch == 'v') addRel(x * 9 + y, (x + 1) * 9 + y);
        else addRel((x + 1) * 9 + y, x * 9 + y);
    }
}

bool canPut(int x, int y, int v) {
    int id = x * 9 + y, bit = 1 << (v - 1), box = x / 3 * 3 + y / 3;
    if (rowMask[x] & bit) return false;
    if (colMask[y] & bit) return false;
    if (boxMask[box] & bit) return false;
    for (int to : low[id])
        if (a[to / 9][to % 9] && v <= a[to / 9][to % 9]) return false;
    for (int to : high[id])
        if (a[to / 9][to % 9] && v >= a[to / 9][to % 9]) return false;
    return true;
}

int getCnt(int x, int y) {
    int cnt = 0, v;
    for (v = 1; v <= 9; v++)
        if (canPut(x, y, v)) cnt++;
    return cnt;
}

void putNum(int x, int y, int v) {
    int bit = 1 << (v - 1), box = x / 3 * 3 + y / 3;
    a[x][y] = v;
    rowMask[x] |= bit;
    colMask[y] |= bit;
    boxMask[box] |= bit;
}

void removeNum(int x, int y, int v) {
    int bit = 1 << (v - 1), box = x / 3 * 3 + y / 3;
    a[x][y] = 0;
    rowMask[x] ^= bit;
    colMask[y] ^= bit;
    boxMask[box] ^= bit;
}

bool dfs(int left) {
    int x, y, v, bx = -1, by = -1, mn = 10, cnt;
    if (!left) return true;
    for (x = 0; x < 9; x++)
        for (y = 0; y < 9; y++)
            if (!a[x][y]) {
                cnt = getCnt(x, y);
                if (!cnt) return false;
                if (cnt < mn) {
                    mn = cnt;
                    bx = x;
                    by = y;
                }
            }
    for (v = 1; v <= 9; v++)
        if (canPut(bx, by, v)) {
            putNum(bx, by, v);
            if (dfs(left - 1)) return true;
            removeNum(bx, by, v);
        }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<string> lines;
    string s;
    int pos = 0, tc = 0, band, row, x, y, v;
    while (getline(cin, s))
        if (s.find_first_not_of(" \t\r") != string::npos) lines.push_back(s);
    while (pos + 15 <= (int)lines.size()) {
        memset(a, 0, sizeof(a));
        memset(rowMask, 0, sizeof(rowMask));
        memset(colMask, 0, sizeof(colMask));
        memset(boxMask, 0, sizeof(boxMask));
        for (x = 0; x < 81; x++) {
            low[x].clear();
            high[x].clear();
        }
        for (band = 0; band < 3; band++) {
            row = band * 3;
            readH(lines[pos++], row);
            readV(lines[pos++], row);
            readH(lines[pos++], row + 1);
            readV(lines[pos++], row + 1);
            readH(lines[pos++], row + 2);
        }
        dfs(81);
        if (tc++) cout << '\n';
        for (x = 0; x < 9; x++) {
            for (y = 0; y < 9; y++) {
                if (y) cout << ' ';
                cout << a[x][y];
            }
            cout << '\n';
        }
    }
    return 0;
}
