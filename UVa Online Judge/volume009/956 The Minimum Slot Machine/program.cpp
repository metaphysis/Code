#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        if (n <= 0) break;
        int go1[26], go2[26], isWin[26];
        bool diff[26][26] = {};
        for (int i = 0; i < n; i++) {
            char name, to1, to2, result;
            cin >> name >> to1 >> to2 >> result;
            int id = name - 'A';
            go1[id] = to1 - 'A';
            go2[id] = to2 - 'A';
            isWin[id] = result == 'w';
        }
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                diff[i][j] = isWin[i] != isWin[j];
        bool changed = true;
        while (changed) {
            changed = false;
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    if (diff[i][j]) continue;
                    int a = min(go1[i], go1[j]), b = max(go1[i], go1[j]);
                    if (a != b && diff[a][b]) {
                        diff[i][j] = true;
                        changed = true;
                        continue;
                    }
                    a = min(go2[i], go2[j]);
                    b = max(go2[i], go2[j]);
                    if (a != b && diff[a][b]) {
                        diff[i][j] = true;
                        changed = true;
                    }
                }
            }
        }
        bool first = true;
        for (int i = 0; i < n; i++) {
            bool keep = true;
            for (int j = 0; j < i; j++) {
                int a = j, b = i;
                if (diff[a][b]) continue;
                keep = false;
                break;
            }
            if (keep) {
                if (!first) cout << ' ';
                cout << char('A' + i);
                first = false;
            }
        }
        cout << '\n';
    }
    return 0;
}
