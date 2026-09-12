#include <bits/stdc++.h>
using namespace std;

class Fenwick {
private:
    int size;
    vector<int> tree;
public:
    Fenwick(int n) : size(n), tree(n + 1, 0) {}

    void add(int idx, int value) {
        while (idx <= size) {
            tree[idx] += value;
            idx += idx & -idx;
        }
    }

    int sum(int idx) {
        int result = 0;
        while (idx > 0) {
            result += tree[idx];
            idx -= idx & -idx;
        }
        return result;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, n, total;
    while (cin >> m >> n) {
        total = m * n;
        Fenwick bit(total);
        int invParity = 0, emptyRow = 0, emptyCol = 0;
        for (int i = 1; i <= total; ++i) {
            int value, row, col;
            cin >> value;
            invParity ^= (i - 1 - bit.sum(value)) & 1;
            bit.add(value, 1);
            if (value == total) {
                row = (i - 1) / n;
                col = (i - 1) % n;
                emptyRow = row;
                emptyCol = col;
            }
        }
        int distance = m - 1 - emptyRow + n - 1 - emptyCol;
        cout << (((invParity + distance) % 2 == 0) ? 'Y' : 'N') << '\n';
    }
    return 0;
}
