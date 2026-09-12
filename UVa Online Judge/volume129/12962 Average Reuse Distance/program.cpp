#include <bits/stdc++.h>
using namespace std;

class Fenwick {
private:
    int n;
    vector<int> bit;
public:
    Fenwick(int size) {
        n = size;
        bit.assign(n + 1, 0);
    }

    void add(int x, int v) {
        for (int i = x; i <= n; i += i & -i) bit[i] += v;
    }

    int sum(int x) {
        int res = 0;
        for (int i = x; i > 0; i -= i & -i) res += bit[i];
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    while (cin >> s) {
        if (s == "0") break;
        int n = s.size(), cnt = 0;
        long long total = 0;
        vector<int> lastPos(26, 0);
        Fenwick tree(n);
        for (int i = 1; i <= n; i++) {
            int c = s[i - 1] - 'a';
            if (lastPos[c] != 0) {
                total += tree.sum(i - 1) - tree.sum(lastPos[c]);
                cnt++;
                tree.add(lastPos[c], -1);
            }
            tree.add(i, 1);
            lastPos[c] = i;
        }
        if (cnt == 0) {
            cout << "NaN\n";
        } else {
            cout << fixed << setprecision(4) << static_cast<double>(total) / cnt << '\n';
        }
    }
    return 0;
}
