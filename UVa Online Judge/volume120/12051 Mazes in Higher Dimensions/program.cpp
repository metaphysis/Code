#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int dim, r, tc = 0;
    const unsigned long long lim = (1ULL << 63) - 1;
    while (cin >> dim >> r) {
        if (dim == 0 && r == 0) break;
        vector<int> len(dim), stride(dim), pos(dim);
        int total = 1;
        for (int i = 0; i < dim; i++) {
            cin >> pos[i];
            len[i] = pos[i] + 1;
            stride[i] = total;
            total *= len[i];
        }
        vector<char> block(total, 0);
        for (int i = 0; i < r; i++) {
            int id = 0;
            for (int j = 0; j < dim; j++) {
                cin >> pos[j];
                id += pos[j] * stride[j];
            }
            block[id] = 1;
        }
        vector<unsigned long long> ways(total, 0);
        if (!block[0]) ways[0] = 1;
        for (int id = 1; id < total; id++) {
            if (block[id]) continue;
            for (int i = 0; i < dim; i++) {
                if ((id / stride[i]) % len[i] == 0) continue;
                unsigned long long add = ways[id - stride[i]];
                if (ways[id] > lim - add) ways[id] = lim;
                else ways[id] += add;
            }
        }
        cout << "Case " << ++tc << ": " << ways[total - 1] << '\n';
    }
    return 0;
}
