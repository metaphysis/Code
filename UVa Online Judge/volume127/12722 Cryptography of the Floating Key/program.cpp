#include <bits/stdc++.h>
using namespace std;

void adjustKey(int len, int& n, int& m) {
    while (n * m < len) {
        if (n < m) n += m;
        else if (n > m) m += n;
        else m += m;
    }
}

void undoSwap(vector<string>& mat, int n, int m, int last) {
    vector<vector<int>> used(n, vector<int>(m, 0));
    for (int i = 0; i < last; i++) {
        int step = i % 2 == 0 ? 1 : -1;
        int j = step == 1 ? 0 : m - 1;
        while (j >= 0 && j < m) {
            if (used[i][j]) {
                j += step;
                continue;
            }
            int ni = i, nj = j + step;
            if (nj < 0 || nj >= m) {
                if (i + 1 >= last) break;
                ni = i + 1;
                nj = j;
            }
            swap(mat[i][j], mat[ni][nj]);
            used[i][j] = 1;
            used[ni][nj] = 1;
            j += step;
        }
    }
}

string decrypt(string q, int n, int m) {
    int len = q.size();
    adjustKey(len, n, m);
    int last = (len - 1) / m;
    vector<string> rot(m, string(n, 0));
    vector<string> mat(n, string(m, 0));
    int k = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int oldI = j;
            int oldJ = m - 1 - i;
            if (oldI < n && oldI * m + oldJ < len)
                rot[i][j] = q[k++];
        }
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (i * m + j < len)
                mat[i][j] = rot[m - 1 - j][i];
    undoSwap(mat, n, m, last);
    string ans;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i * m + j >= len) continue;
            int shift = (i + j + 2) % 26;
            mat[i][j] = char((mat[i][j] - 'a' - shift + 26) % 26 + 'a');
            ans += mat[i][j];
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int cs = 1; cs <= t; cs++) {
        string q;
        int n, m;
        cin >> q >> n >> m;
        cout << "Case #" << cs << ": " << decrypt(q, n, m) << '\n';
    }
    return 0;
}
