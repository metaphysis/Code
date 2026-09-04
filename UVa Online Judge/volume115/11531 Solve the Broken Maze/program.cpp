#include <bits/stdc++.h>
using namespace std;

int fa[32], typ[4], dir[4], part[55][5], tmp[5], stateCnt;
int idMap[32768];
unsigned long long trans[81][55];

int findSet(int x) {
    if (fa[x] == x) return x;
    return fa[x] = findSet(fa[x]);
}

void mergeSet(int x, int y) {
    x = findSet(x);
    y = findSet(y);
    if (x != y) fa[x] = y;
}

int getCode(int a[]) {
    int code = 0;
    for (int i = 0; i < 5; i++) code |= a[i] << (i * 3);
    return code;
}

void genState(int pos, int maxVal) {
    if (pos == 5) {
        int code = getCode(tmp);
        for (int i = 0; i < 5; i++) part[stateCnt][i] = tmp[i];
        idMap[code] = stateCnt++;
        return;
    }
    for (int i = 0; i <= maxVal + 1; i++) {
        tmp[pos] = i;
        genState(pos + 1, max(maxVal, i));
    }
}

int getNextState(int id) {
    int lab[5], root[32], cnt = 0;
    for (int i = 0; i < 32; i++) fa[i] = i;
    for (int i = 0; i < 5; i++)
        for (int j = i + 1; j < 5; j++)
            if (part[id][i] == part[id][j])
                mergeSet(i, j);
    for (int i = 0; i < 4; i++) {
        int base = 9 + i * 4;
        mergeSet(i, base);
        mergeSet(5 + i, base + 1);
        if (typ[i] == 1) {
            if (dir[i] == 0) mergeSet(base, base + 1);
            else mergeSet(base + 2, base + 3);
        } else if (typ[i] == 2) {
            if (dir[i] == 0) mergeSet(base, base + 2);
            else if (dir[i] == 1) mergeSet(base + 2, base + 1);
            else if (dir[i] == 2) mergeSet(base + 1, base + 3);
            else mergeSet(base + 3, base);
        }
    }
    for (int i = 0; i < 3; i++)
        if (typ[i] != 0 && typ[i + 1] != 0)
            mergeSet(9 + i * 4 + 3, 9 + (i + 1) * 4 + 2);
    for (int i = 0; i < 32; i++) root[i] = -1;
    for (int i = 0; i < 5; i++) {
        int node = i < 4 ? 5 + i : 4;
        int rt = findSet(node);
        if (root[rt] == -1) root[rt] = cnt++;
        lab[i] = root[rt];
    }
    return idMap[getCode(lab)];
}

void addTrans(int code) {
    for (int i = 0; i < stateCnt; i++) {
        int nextId = getNextState(i);
        trans[code][i] |= 1ULL << nextId;
    }
}

void buildDir(int code, int row) {
    if (row == 4) {
        addTrans(code);
        return;
    }
    if (typ[row] == 0) {
        dir[row] = 0;
        buildDir(code, row + 1);
    } else if (typ[row] == 1) {
        for (int i = 0; i < 2; i++) {
            dir[row] = i;
            buildDir(code, row + 1);
        }
    } else {
        for (int i = 0; i < 4; i++) {
            dir[row] = i;
            buildDir(code, row + 1);
        }
    }
}

void initTrans() {
    for (int i = 0; i < 32768; i++) idMap[i] = -1;
    tmp[0] = 0;
    genState(1, 0);
    for (int code = 0; code < 81; code++) {
        int val = code;
        for (int i = 0; i < 4; i++) {
            typ[i] = val % 3;
            val /= 3;
        }
        buildDir(code, 0);
    }
}

int getType(char ch) {
    if (ch == 'X') return 0;
    if (ch == 'A') return 1;
    return 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    initTrans();
    int t, n;
    string maze[4];
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 0; i < 4; i++) cin >> maze[i];
        int initLab[5] = {0, 0, 0, 0, 0};
        unsigned long long states = 1ULL << idMap[getCode(initLab)];
        for (int col = 0; col < n; col++) {
            int code = 0, mul = 1;
            unsigned long long nextStates = 0;
            for (int row = 0; row < 4; row++) {
                code += getType(maze[row][col]) * mul;
                mul *= 3;
            }
            for (int i = 0; i < stateCnt; i++)
                if (states & (1ULL << i))
                    nextStates |= trans[code][i];
            states = nextStates;
        }
        bool ok = false;
        for (int i = 0; i < stateCnt; i++) {
            if (!(states & (1ULL << i))) continue;
            for (int row = 0; row < 4; row++)
                if (part[i][row] == part[i][4])
                    ok = true;
        }
        if (ok) cout << "Try.\n";
        else cout << "Don't Try.\n";
    }
    return 0;
}
