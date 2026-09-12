// Partitions
// UVa ID: 1015
// Verdict: Accepted
// Submission Date: 2026-08-03
// UVa Run Time: 0.010s

#include <bits/stdc++.h>
using namespace std;

int w, h;
string a[50], b[50];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    while (cin >> w >> h && (w || h)) {
        for (int i = 0; i <= h; ++i)
            a[i] = b[i] = string(2 * w + 1, ' ');
        cin.ignore(32, '\n');
        for (int i = 0; i <= h; ++i) {
            string s;
            getline(cin, s);
            if (!s.empty() && s.back() == '\r')
                s.pop_back();
            if ((int)s.size() < 4 * w + 3)
                s.resize(4 * w + 3, ' ');
            for (int j = 0; j < 2 * w + 1; ++j) {
                if (s[j] != ' ')
                    a[i][j] = s[j];
                if (s[j + 2 * w + 2] != ' ')
                    a[i][j] = s[j + 2 * w + 2];
                if (s[j] != ' ' &&
                    s[j + 2 * w + 2] != ' ') {
                    b[i][j] = s[j];
                }
            }
        }
        while (true) {
            bool ok = false;
            for (int i = 1; i <= h; ++i) {
                for (int j = 2; j <= 2 * w - 2; j += 2) {
                    if (b[i][j] != ' ' &&
                        b[i - 1][j] == ' ' &&
                        (b[i - 1][j - 1] == ' ' ||
                         b[i - 1][j + 1] == ' ')) {
                        b[i][j] = ' ';
                        ok = true;
                    }
                }
            }
            for (int i = h; i >= 1; --i) {
                for (int j = 2; j <= 2 * w - 2; j += 2) {
                    if (b[i][j] != ' ' &&
                        (i == h || b[i + 1][j] == ' ') &&
                        (b[i][j - 1] == ' ' ||
                         b[i][j + 1] == ' ')) {
                        b[i][j] = ' ';
                        ok = true;
                    }
                }
            }
            for (int j = 1; j <= 2 * w - 1; j += 2) {
                for (int i = 1; i <= h - 1; ++i) {
                    if (b[i][j] != ' ' &&
                        (j == 1 || b[i][j - 2] == ' ') &&
                        (b[i][j - 1] == ' ' ||
                         b[i + 1][j - 1] == ' ')) {
                        b[i][j] = ' ';
                        ok = true;
                    }
                }
            }
            for (int j = 2 * w - 1; j >= 1; j -= 2) {
                for (int i = 1; i <= h - 1; ++i) {
                    if (b[i][j] != ' ' &&
                        (j == 2 * w - 1 || b[i][j + 2] == ' ') &&
                        (b[i][j + 1] == ' ' ||
                         b[i + 1][j + 1] == ' ')) {
                        b[i][j] = ' ';
                        ok = true;
                    }
                }
            }
            if (!ok) break;
        }
        cout << "Case " << T++ << ":\n";
        for (int i = 0; i <= h; ++i)
            cout << a[i] << ' ' << b[i] << '\n';
        cout << '\n';
    }
    return 0;
}
