// SMS for Blind
// UVa ID: 11602
// Verdict: Accepted
// Submission Date: 2026-07-31
// UVa Run Time: 0.030s

#include <bits/stdc++.h>
using namespace std;

const int N = 19;
const char ALL_CHARS[N] = {'a','b','c','d','e','f','g','h','i','l','m','n','o','p','r','s','t','u','_'};
unordered_map<char,int> idxMap;
int cnt[N], targetC;
char ans[N];
int orderIdx[N];
bool found;

void initMap() {
    for (int i = 0; i < N; ++i) idxMap[ALL_CHARS[i]] = i;
}

bool dfs(int pos, int mask, int cur) {
    if (pos == N) {
        if (cur == targetC) { found = true; return true; }
        return false;
    }
    int remain = N - pos;
    vector<int> rem;
    for (int i = 0; i < N; ++i)
        if (!(mask & (1 << i))) rem.push_back(cnt[i]);
    sort(rem.begin(), rem.end());
    int minAdd = 0, maxAdd = 0;
    for (int i = 0; i < remain; ++i) {
        int p = pos + 1 + i;
        minAdd += rem[i] * p;
        maxAdd += rem[remain - 1 - i] * p;
    }
    if (cur + minAdd > targetC || cur + maxAdd < targetC) return false;
    for (int k = 0; k < N; ++k) {
        int idx = orderIdx[k];
        if (mask & (1 << idx)) continue;
        int newCur = cur + cnt[idx] * (pos + 1);
        ans[pos] = ALL_CHARS[idx];
        if (dfs(pos + 1, mask | (1 << idx), newCur)) return true;
    }
    return false;
}

bool randomSolve() {
    vector<int> perm(N);
    iota(perm.begin(), perm.end(), 0);
    random_device rd;
    mt19937 g(rd());
    for (int attempt = 0; attempt < 200; ++attempt) {
        shuffle(perm.begin(), perm.end(), g);
        int cur = 0;
        for (int i = 0; i < N; ++i) cur += cnt[perm[i]] * (i + 1);
        int diff = targetC - cur;
        if (diff == 0) {
            for (int i = 0; i < N; ++i) ans[i] = ALL_CHARS[perm[i]];
            return true;
        }
        for (int iter = 0; iter < 1000; ++iter) {
            bool improved = false;
            for (int i = 0; i < N; ++i) {
                for (int j = i + 1; j < N; ++j) {
                    int delta = (cnt[perm[i]] - cnt[perm[j]]) * ((j + 1) - (i + 1));
                    if (delta == 0) continue;
                    int newDiff = diff - delta;
                    if (abs(newDiff) < abs(diff)) {
                        swap(perm[i], perm[j]);
                        diff = newDiff;
                        if (diff == 0) {
                            for (int i = 0; i < N; ++i) ans[i] = ALL_CHARS[perm[i]];
                            return true;
                        }
                        improved = true;
                        break;
                    }
                }
                if (improved) break;
            }
            if (!improved) break;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    initMap();
    string S;
    while (cin >> S && S != "*") {
        cin >> targetC;
        memset(cnt, 0, sizeof(cnt));
        for (char c : S) cnt[idxMap[c]]++;
        iota(orderIdx, orderIdx + N, 0);
        sort(orderIdx, orderIdx + N, [&](int a, int b) {
            if (cnt[a] != cnt[b]) return cnt[a] > cnt[b];
            return ALL_CHARS[a] < ALL_CHARS[b];
        });
        found = false;
        if (!dfs(0, 0, 0)) {
            if (!randomSolve()) {
                for (int i = 0; i < N; ++i) ans[i] = ALL_CHARS[i];
            }
        }
        for (int i = 0; i < N; ++i) cout << ans[i];
        cout << '\n';
    }
    return 0;
}
