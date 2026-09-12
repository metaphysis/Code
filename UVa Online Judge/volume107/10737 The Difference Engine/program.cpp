#include <bits/stdc++.h>
using namespace std;

int modPow(int a, int b, int p) {
    int ans = 1;
    while (b > 0) {
        if (b & 1) ans = ans * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return ans;
}

vector<vector<int>> getNullSpace(vector<vector<int>> a, int p) {
    vector<int> piv(p, -1);
    int row = 0;
    for (int col = 0; col < p && row < p; col++) {
        int sel = row;
        while (sel < p && a[sel][col] == 0) sel++;
        if (sel == p) continue;
        swap(a[sel], a[row]);
        int inv = modPow(a[row][col], p - 2, p);
        for (int j = 0; j < p; j++) a[row][j] = a[row][j] * inv % p;
        for (int i = 0; i < p; i++) {
            if (i == row || a[i][col] == 0) continue;
            int factor = a[i][col];
            for (int j = 0; j < p; j++) {
                a[i][j] = (a[i][j] - factor * a[row][j]) % p;
                if (a[i][j] < 0) a[i][j] += p;
            }
        }
        piv[col] = row;
        row++;
    }
    vector<vector<int>> basis;
    for (int freeCol = 0; freeCol < p; freeCol++) {
        if (piv[freeCol] != -1) continue;
        vector<int> vec(p, 0);
        vec[freeCol] = 1;
        for (int col = 0; col < p; col++) {
            if (piv[col] == -1) continue;
            vec[col] = (p - a[piv[col]][freeCol]) % p;
        }
        basis.push_back(vec);
    }
    return basis;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int p, n;
    while (cin >> p >> n && (p != 0 || n != 0)) {
        vector<string> msg(p);
        for (int i = 0; i < p; i++) cin >> msg[i];
        vector<vector<int>> mat(p, vector<int>(p, 0));
        for (int i = 0; i < p; i++) mat[i][i] = 1;
        for (int k = 0; k < n && k < p; k++) {
            vector<vector<int>> nxt(p, vector<int>(p, 0));
            for (int i = 0; i < p; i++)
                for (int j = 0; j < p; j++) {
                    nxt[i][j] = mat[(i + 1) % p][j] - mat[i][j];
                    nxt[i][j] %= p;
                    if (nxt[i][j] < 0) nxt[i][j] += p;
                }
            mat = nxt;
        }
        vector<vector<int>> trans(p, vector<int>(p, 0));
        for (int i = 0; i < p; i++)
            for (int j = 0; j < p; j++)
                trans[i][j] = mat[j][i];
        vector<vector<int>> basis = getNullSpace(trans, p);
        vector<int> pos(p, -1), ans(p, 0);
        int miss = 0;
        for (int i = 0; i < p; i++) {
            if (msg[i] == "?") pos[i] = miss++;
            else ans[i] = stoi(msg[i]);
        }
        vector<vector<int>> eq;
        for (const vector<int>& vec : basis) {
            vector<int> cur(miss + 1, 0);
            for (int i = 0; i < p; i++) {
                if (pos[i] != -1) {
                    cur[pos[i]] = (cur[pos[i]] + vec[i]) % p;
                } else {
                    cur[miss] = (cur[miss] - vec[i] * ans[i]) % p;
                }
            }
            if (cur[miss] < 0) cur[miss] += p;
            eq.push_back(cur);
        }
        int row = 0;
        vector<int> colRow(miss, -1);
        for (int col = 0; col < miss && row < static_cast<int>(eq.size()); col++) {
            int sel = row;
            while (sel < static_cast<int>(eq.size()) && eq[sel][col] == 0) sel++;
            if (sel == static_cast<int>(eq.size())) continue;
            swap(eq[sel], eq[row]);
            int inv = modPow(eq[row][col], p - 2, p);
            for (int j = col; j <= miss; j++) eq[row][j] = eq[row][j] * inv % p;
            for (int i = 0; i < static_cast<int>(eq.size()); i++) {
                if (i == row || eq[i][col] == 0) continue;
                int factor = eq[i][col];
                for (int j = col; j <= miss; j++) {
                    eq[i][j] = (eq[i][j] - factor * eq[row][j]) % p;
                    if (eq[i][j] < 0) eq[i][j] += p;
                }
            }
            colRow[col] = row++;
        }
        bool valid = true;
        for (const vector<int>& cur : eq) {
            bool zero = true;
            for (int j = 0; j < miss; j++) {
                if (cur[j] != 0) {
                    zero = false;
                    break;
                }
            }
            if (zero && cur[miss] != 0) {
                valid = false;
                break;
            }
        }
        for (int col = 0; col < miss; col++)
            if (colRow[col] == -1) valid = false;
        if (!valid) {
            cout << "Invalid message!\n";
            continue;
        }
        vector<int> value(miss, 0);
        for (int col = 0; col < miss; col++) value[col] = eq[colRow[col]][miss];
        for (int i = 0; i < p; i++)
            if (pos[i] != -1) ans[i] = value[pos[i]];
        for (int i = 0; i < p; i++) {
            if (i > 0) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }
    return 0;
}
