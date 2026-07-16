// Optimal Segments
// UVa ID: 11598
// Verdict: Accepted
// Submission Date: 2026-07-16
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int N, K;
vector<int> a;              // 普通格子的 V 值，特殊为 0
vector<int> pref;           // 普通 V 的前缀和
vector<int> specPref;       // 特殊格子的前缀和
vector<int> suffixSpec;     // 后缀特殊格子数
vector<string> cellStr;     // 原始字符串（用于输出）

int bestDiff;
vector<int> bestLengths;
vector<pair<int,int>> bestSegs;

// 回溯搜索
void dfs(int pos, int segs, int minExp, int maxExp,
         vector<int>& lengths, vector<pair<int,int>>& segsInfo) {
    if (segs == K - 1) { // 最后一段
        int end = N;
        if (specPref[N] - specPref[pos - 1] == 0) return;
        int curExp = pref[N] - pref[pos - 1];
        int newMin, newMax;
        if (segs == 0) {
            newMin = newMax = curExp;
        } else {
            newMin = min(minExp, curExp);
            newMax = max(maxExp, curExp);
        }
        int diff = newMax - newMin;

        vector<int> fullLengths = lengths;
        fullLengths.push_back(end - pos + 1);

        if (diff < bestDiff || (diff == bestDiff &&
            (bestLengths.empty() || fullLengths > bestLengths))) {
            bestDiff = diff;
            bestLengths = fullLengths;
            bestSegs = segsInfo;
            bestSegs.push_back({pos, end});
        }
        return;
    }

    int need = K - segs - 1;          // 剩余段数（不含当前段）
    int totalSpec = suffixSpec[pos];
    if (totalSpec < need + 1) return; // 当前段及剩余段至少各一个特殊

    for (int end = pos; end <= N - need; ++end) {
        // 当前段必须含特殊格子
        if (specPref[end] - specPref[pos - 1] == 0) continue;
        // 剩余部分必须含至少 need 个特殊格子
        if (suffixSpec[end + 1] < need) continue;

        int curExp = pref[end] - pref[pos - 1];
        int newMin, newMax;
        if (segs == 0) {
            newMin = newMax = curExp;
        } else {
            newMin = min(minExp, curExp);
            newMax = max(maxExp, curExp);
        }

        // 若当前差值已经大于当前最优差值，剪枝
        if (newMax - newMin > bestDiff) continue;

        lengths.push_back(end - pos + 1);
        segsInfo.push_back({pos, end});
        dfs(end + 1, segs + 1, newMin, newMax, lengths, segsInfo);
        lengths.pop_back();
        segsInfo.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        cin >> N >> K;
        a.assign(N + 1, 0);
        cellStr.assign(N + 1, "");
        specPref.assign(N + 1, 0);
        suffixSpec.assign(N + 2, 0);
        pref.assign(N + 1, 0);

        for (int i = 1; i <= N; ++i) {
            string s;
            cin >> s;
            cellStr[i] = s;
            if (s == "X") {
                a[i] = 0;
                specPref[i] = 1;
            } else {
                a[i] = stoi(s);
                specPref[i] = 0;
            }
        }

        // 前缀和
        for (int i = 1; i <= N; ++i) {
            pref[i] = pref[i - 1] + a[i];
            specPref[i] += specPref[i - 1];
        }

        // 后缀特殊格子数
        for (int i = N; i >= 1; --i)
            suffixSpec[i] = suffixSpec[i + 1] + (cellStr[i] == "X" ? 1 : 0);

        int specialCnt = specPref[N];

        if (specialCnt < K) {
            cout << "Case " << tc << ": not possible!\n";
            continue;
        }

        // 若全部是特殊格子，直接构造最优划分（第一段尽量长）
        if (specialCnt == N) {
            vector<pair<int,int>> segs;
            int start = 1;
            int len1 = N - K + 1;
            segs.push_back({start, start + len1 - 1});
            start += len1;
            for (int i = 2; i <= K; ++i) {
                segs.push_back({start, start});
                ++start;
            }
            cout << "Case " << tc << ": 1 ";
            for (auto &seg : segs) {
                cout << "(";
                for (int i = seg.first; i <= seg.second; ++i) {
                    if (i > seg.first) cout << " ";
                    cout << cellStr[i];
                }
                cout << ")";
            }
            cout << "\n";
            continue;
        }

        bestDiff = INF;
        bestLengths.clear();
        bestSegs.clear();

        vector<int> lengths;
        vector<pair<int,int>> segsInfo;
        dfs(1, 0, 0, 0, lengths, segsInfo);

        if (bestDiff >= 50) {
            cout << "Case " << tc << ": overflow\n";
        } else {
            long long ratio = 1LL << bestDiff;
            cout << "Case " << tc << ": " << ratio << " ";
            for (auto &seg : bestSegs) {
                cout << "(";
                for (int i = seg.first; i <= seg.second; ++i) {
                    if (i > seg.first) cout << " ";
                    cout << cellStr[i];
                }
                cout << ")";
            }
            cout << "\n";
        }
    }
    return 0;
}
