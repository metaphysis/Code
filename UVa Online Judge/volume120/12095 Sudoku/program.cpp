#include <bits/stdc++.h>
using namespace std;

struct Pos {
    int row, col, val;
};

vector<array<int, 9> > getPerm() {
    vector<array<int, 9> > res;
    array<int, 3> seg = {0, 1, 2};
    do {
        array<int, 3> a = {0, 1, 2}, b = {0, 1, 2}, c = {0, 1, 2};
        do {
            do {
                do {
                    array<int, 9> cur;
                    array<array<int, 3>, 3> ord = {a, b, c};
                    for (int i = 0; i < 3; i++)
                        for (int j = 0; j < 3; j++)
                            cur[i * 3 + j] = seg[i] * 3 + ord[i][j];
                    res.push_back(cur);
                } while (next_permutation(c.begin(), c.end()));
                c = {0, 1, 2};
            } while (next_permutation(b.begin(), b.end()));
            b = {0, 1, 2};
        } while (next_permutation(a.begin(), a.end()));
    } while (next_permutation(seg.begin(), seg.end()));
    return res;
}

bool check(const int old[9][9], const int now[9][9], const vector<array<int, 9> > &per) {
    vector<Pos> fst, oth;
    bool used[10] = {};
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (now[i][j]) {
                Pos cur = {i, j, now[i][j]};
                if (!used[now[i][j]]) {
                    used[now[i][j]] = true;
                    fst.push_back(cur);
                } else
                    oth.push_back(cur);
            }
    fst.insert(fst.end(), oth.begin(), oth.end());
    for (int rot = 0; rot < 4; rot++) {
        int src[9][9];
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++) {
                if (rot == 0) src[i][j] = old[i][j];
                else if (rot == 1) src[i][j] = old[8 - j][i];
                else if (rot == 2) src[i][j] = old[8 - i][8 - j];
                else src[i][j] = old[j][8 - i];
            }
        for (int a = 0; a < (int)per.size(); a++) {
            for (int b = 0; b < (int)per.size(); b++) {
                int mp[10] = {}, rev[10] = {};
                bool ok = true;
                for (int k = 0; k < (int)fst.size(); k++) {
                    int x = src[per[a][fst[k].row]][per[b][fst[k].col]], y = fst[k].val;
                    if (mp[x] && mp[x] != y) {
                        ok = false;
                        break;
                    }
                    if (rev[y] && rev[y] != x) {
                        ok = false;
                        break;
                    }
                    mp[x] = y;
                    rev[y] = x;
                }
                if (ok) return true;
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<array<int, 9> > per = getPerm();
    int num;
    cin >> num;
    while (num--) {
        int old[9][9], now[9][9];
        string str;
        for (int i = 0; i < 9; i++) {
            cin >> str;
            for (int j = 0; j < 9; j++)
                old[i][j] = str[j] - '0';
        }
        for (int i = 0; i < 9; i++) {
            cin >> str;
            for (int j = 0; j < 9; j++)
                now[i][j] = str[j] - '0';
        }
        if (check(old, now, per)) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}
