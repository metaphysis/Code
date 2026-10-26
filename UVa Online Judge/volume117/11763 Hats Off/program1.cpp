// Hats Off
// UVa ID: 11763
// Verdict: Accepted
// Submission Date: 2026-10-26
// UVa Run Time: 0.250s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net


#include <bits/stdc++.h>
using namespace std;

struct Range {
    int l, r;
};

struct Block {
    int sz;
    int mask;
};

struct ArrayHash {
    size_t operator()(const array<unsigned int, 9>& a) const noexcept {
        size_t h = 0;
        for (int i = 0; i < 9; ++i) {
            h ^= hash<unsigned int>{}(a[i]) + 0x9e3779b9u + (h << 6) + (h >> 2);
        }
        return h;
    }
};

bool compatible(
    int b, int sb,
    int j, int sj,
    long long limit,
    const vector<long long>& stones,
    const vector<Block>& blocks
) {
    int cb = blocks[b].sz;
    int cj = blocks[j].sz;
    // Disjoint intervals in the sorted stone array.
    if (sb < sj + cj && sj < sb + cb)
        return false;
    if (blocks[b].mask & blocks[j].mask) {
        if (stones[sb + cb - 1] - stones[sj] > limit)
            return false;
        if (stones[sj + cj - 1] - stones[sb] > limit)
            return false;
    }
    return true;
}

bool feasible(
    long long limit,
    const vector<long long>& stones,
    const vector<Block>& blocks
) {
    int n = (int)stones.size();
    int B = (int)blocks.size();
    if (B == 0)
        return true;
    vector<unsigned int> dom(B, 0);
    for (int b = 0; b < B; ++b) {
        int c = blocks[b].sz;
        unsigned int mask = 0;
        for (int st = 0; st + c <= n; ++st) {
            if (stones[st + c - 1] - stones[st] <= limit) {
                mask |= (1u << st);
            }
        }
        if (mask == 0)
            return false;
        dom[b] = mask;
    }
    unordered_set<array<unsigned int, 9>, ArrayHash> failed;
    failed.reserve(1024);
    function<bool(const vector<unsigned int>&)> dfs =
        [&](const vector<unsigned int>& cur) -> bool {
            int chosen = -1;
            int bestCnt = 1000;
            for (int i = 0; i < B; ++i) {
                if (cur[i] != 0) {
                    int cnt = __builtin_popcount(cur[i]);
                    if (cnt < bestCnt) {
                        bestCnt = cnt;
                        chosen = i;
                        if (cnt == 1)
                            break;
                    }
                }
            }
            if (chosen == -1)
                return true;
            array<unsigned int, 9> key{};
            for (int i = 0; i < B; ++i)
                key[i] = cur[i];
            if (failed.find(key) != failed.end())
                return false;
            unsigned int m = cur[chosen];
            while (m) {
                int sb = __builtin_ctz(m);
                m &= m - 1;
                vector<unsigned int> nxt = cur;
                nxt[chosen] = 0;
                bool ok = true;
                for (int j = 0; j < B; ++j) {
                    if (j == chosen || nxt[j] == 0)
                        continue;
                    unsigned int mj = nxt[j];
                    unsigned int nm = 0;
                    while (mj) {
                        int sj = __builtin_ctz(mj);
                        mj &= mj - 1;
                        if (compatible(chosen, sb, j, sj, limit, stones, blocks)) {
                            nm |= (1u << sj);
                        }
                    }
                    nxt[j] = nm;
                    if (nm == 0) {
                        ok = false;
                        break;
                    }
                }
                if (ok && dfs(nxt))
                    return true;
            }
            failed.insert(key);
            return false;
        };
    return dfs(dom);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int caseId = 1; caseId <= T; ++caseId) {
        int n;
        cin >> n;
        vector<long long> stones(n);
        for (long long& x : stones)
            cin >> x;
        sort(stones.begin(), stones.end());
        int m;
        cin >> m;
        vector<Range> nonSingleton;
        for (int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            --a;
            --b;
            // Drop singleton ranges first.
            if (a < b)
                nonSingleton.push_back({a, b});
        }
        // Preserve input order.
        // Delete range i only if some later range contains it.
        vector<Range> kept;
        for (int i = 0; i < (int)nonSingleton.size(); ++i) {
            bool containedByLater = false;
            for (int j = i + 1; j < (int)nonSingleton.size(); ++j) {
                if (nonSingleton[j].l <= nonSingleton[i].l &&
                    nonSingleton[j].r >= nonSingleton[i].r) {
                    containedByLater = true;
                    break;
                }
            }
            if (!containedByLater)
                kept.push_back(nonSingleton[i]);
        }
        int R = (int)kept.size();
        vector<int> holeMask(n, 0);
        for (int r = 0; r < R; ++r) {
            for (int pos = kept[r].l; pos <= kept[r].r; ++pos) {
                holeMask[pos] |= (1 << r);
            }
        }
        // Group adjacent holes having identical nonzero masks.
        vector<Block> blocks;
        int curMask = 0;
        int curSize = 0;
        for (int pos = 0; pos < n; ++pos) {
            int msk = holeMask[pos];
            if (msk == 0) {
                if (curSize > 0) {
                    blocks.push_back({curSize, curMask});
                    curSize = 0;
                    curMask = 0;
                }
            } else {
                if (curSize > 0 && msk == curMask) {
                    ++curSize;
                } else {
                    if (curSize > 0)
                        blocks.push_back({curSize, curMask});
                    curMask = msk;
                    curSize = 1;
                }
            }
        }
        if (curSize > 0)
            blocks.push_back({curSize, curMask});
        vector<long long> candidates;
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                candidates.push_back(stones[j] - stones[i]);
            }
        }
        sort(candidates.begin(), candidates.end());
        candidates.erase(
            unique(candidates.begin(), candidates.end()),
            candidates.end()
        );
        int lo = 0;
        int hi = (int)candidates.size() - 1;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (feasible(candidates[mid], stones, blocks))
                hi = mid;
            else
                lo = mid + 1;
        }
        cout << "Case " << caseId << ": " << candidates[lo] << '\n';
    }
    return 0;
}
