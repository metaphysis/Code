#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using ld = long double;

ld countSc(int n, const vector<pair<int, int>> &edges, const vector<bool> &must) {
    int stateCnt = 1 << n, m = edges.size();
    vector<ull> nodeOutFree(n), nodeInFree(n), nodeOutMust(n), nodeInMust(n), outFree(stateCnt), inFree(stateCnt), outMust(stateCnt), inMust(stateCnt);
    vector<int> freeCnt(stateCnt);
    vector<ld> sc(stateCnt), signedCnt(stateCnt), powTwo(m + 1);
    powTwo[0] = 1;
    for (int i = 1; i <= m; i++) powTwo[i] = powTwo[i - 1] * 2;
    for (int i = 0; i < m; i++) {
        int u = edges[i].first, v = edges[i].second;
        ull edgeBit = 1ULL << i;
        if (must[i]) {
            nodeOutMust[u] |= edgeBit;
            nodeInMust[v] |= edgeBit;
        } else {
            nodeOutFree[u] |= edgeBit;
            nodeInFree[v] |= edgeBit;
        }
    }
    for (int s = 1; s < stateCnt; s++) {
        int lowBit = s & -s, v = __builtin_ctz(lowBit), rest = s ^ lowBit;
        outFree[s] = outFree[rest] | nodeOutFree[v];
        inFree[s] = inFree[rest] | nodeInFree[v];
        outMust[s] = outMust[rest] | nodeOutMust[v];
        inMust[s] = inMust[rest] | nodeInMust[v];
        freeCnt[s] = __builtin_popcountll(outFree[s] & inFree[s]);
    }
    signedCnt[0] = 1;
    for (int s = 1; s < stateCnt; s++) {
        int lowBit = s & -s;
        ld partSum = 0, sourceSum = 0;
        for (int sub = (s - 1) & s; sub; sub = (sub - 1) & s) {
            int rest = s ^ sub;
            ull intoSub = outMust[rest] & inMust[sub], intoRest = outMust[sub] & inMust[rest];
            // 固定最小顶点所在的块，统计至少两个块的贡献
            if ((sub & lowBit) && !intoSub && !intoRest) partSum -= sc[sub] * signedCnt[rest];
            if (!intoSub) {
                int freeNum = freeCnt[rest] + __builtin_popcountll(outFree[sub] & inFree[rest]);
                sourceSum += signedCnt[sub] * powTwo[freeNum];
            }
        }
        signedCnt[s] = -powTwo[freeCnt[s]] - sourceSum;
        sc[s] = partSum - signedCnt[s];
    }
    return sc[stateCnt - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, caseId = 0;
    cout << fixed << setprecision(4);
    while (cin >> n >> m) {
        vector<pair<int, int>> edges(m);
        vector<bool> must(m, false);
        for (int i = 0; i < m; i++) {
            cin >> edges[i].first >> edges[i].second;
            edges[i].first--;
            edges[i].second--;
        }
        int k, edgeId;
        cin >> k;
        ld total = countSc(n, edges, must);
        for (int i = 0; i < k; i++) {
            cin >> edgeId;
            must[edgeId - 1] = true;
        }
        ld good = countSc(n, edges, must), answer = good / total;
        cout << "Case " << ++caseId << ": " << answer << '\n';
    }
    return 0;
}
