// Non Decreasing Prime Sequence
// UVa ID: 11669
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.730s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXV = 1000000;

vector<int> spf(MAXV + 1);
vector<vector<int>> factors(MAXV + 1);

void precompute() {
    vector<int> primes;
    for (int i = 2; i <= MAXV; ++i) {
        if (!spf[i]) {
            spf[i] = i;
            primes.push_back(i);
        }
        for (int p : primes) {
            if (p > spf[i] || 1LL * i * p > MAXV) break;
            spf[i * p] = p;
        }
    }
    for (int i = 2; i <= MAXV; ++i) {
        int x = i;
        while (x > 1) {
            int p = spf[x];
            while (x % p == 0) {
                factors[i].push_back(p);
                x /= p;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    precompute();
    vector<int> order;
    order.reserve(MAXV - 1);
    for (int i = 2; i <= MAXV; ++i) order.push_back(i);
    sort(order.begin(), order.end(), [&](int a, int b) {
        if (factors[a].size() != factors[b].size())
            return factors[a].size() < factors[b].size();
        return factors[a] < factors[b];
    });
    int N = (int)order.size();
    int blockSize = 2500;
    int numBlocks = (N + blockSize - 1) / blockSize;
    vector<int> blockStart(numBlocks), blockEnd(numBlocks);
    vector<vector<int>> blockSorted(numBlocks);
    for (int b = 0; b < numBlocks; ++b) {
        int l = b * blockSize;
        int r = min(N, l + blockSize);
        blockStart[b] = l;
        blockEnd[b] = r;
        blockSorted[b].reserve(r - l);
        for (int i = l; i < r; ++i) blockSorted[b].push_back(order[i]);
        sort(blockSorted[b].begin(), blockSorted[b].end());
    }
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        int A, B, K;
        cin >> A >> B >> K;
        int ans = -1;
        int cnt = 0;
        for (int b = 0; b < numBlocks; ++b) {
            auto &vec = blockSorted[b];
            auto itL = lower_bound(vec.begin(), vec.end(), A);
            auto itR = upper_bound(vec.begin(), vec.end(), B);
            int num = (int)(itR - itL);
            if (cnt + num >= K) {
                int need = K - cnt;
                for (int i = blockStart[b]; i < blockEnd[b]; ++i) {
                    int w = order[i];
                    if (w >= A && w <= B) {
                        --need;
                        if (need == 0) {
                            ans = w;
                            break;
                        }
                    }
                }
                break;
            } else cnt += num;
        }
        cout << "Case " << tc << ": ";
        const auto &fac = factors[ans];
        for (size_t i = 0; i < fac.size(); ++i) {
            if (i) cout << ' ';
            cout << fac[i];
        }
        cout << '\n';
    }
    return 0;
}
