// Shuffle
// UVa ID: 12174
// Verdict: Accepted
// Submission Date: 2025-10-28
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) {
        int s, n; cin >> s >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        // 预处理：标记所有长度为s的区间是否是排列
        vector<bool> fullPerm(n, false);
        vector<int> cnt(s + 1, 0);
        int dup = 0;
        for (int i = 0; i < n; i++) {
            if (cnt[a[i]] == 1) dup++;
            cnt[a[i]]++;
            if (i >= s) {
                cnt[a[i - s]]--;
                if (cnt[a[i - s]] == 1) dup--;
            }
            if (i >= s - 1 && dup == 0) fullPerm[i] = true;
        }
        // 预处理：前缀和后缀无重复
        vector<int> lastPos(s + 1, -1), prefixDup(n, -1);
        int maxDup = -1;
        for (int i = 0; i < n; i++) {
            if (lastPos[a[i]] > maxDup) maxDup = lastPos[a[i]];
            lastPos[a[i]] = i;
            prefixDup[i] = maxDup;
        }
        fill(lastPos.begin(), lastPos.end(), n);
        vector<int> suffixDup(n, n);
        int minDup = n;
        for (int i = n - 1; i >= 0; i--) {
            if (lastPos[a[i]] < minDup) minDup = lastPos[a[i]];
            lastPos[a[i]] = i;
            suffixDup[i] = minDup;
        }
        // 检查每个起始偏移量
        unordered_set<int> answer;
        for (int k = 0; k < s; k++) {
            int valid = true, pos = 0;
            // 第一个区间
            int firstLen = min(s - k, n);
            if (firstLen > 0 && prefixDup[firstLen - 1] >= 0) valid = false;
            pos += firstLen;
            // 完整区间
            while (valid && pos + s <= n) {
                if (!fullPerm[pos + s - 1]) valid = false;
                pos += s;
            }
            // 最后一个区间
            if (valid && pos < n && suffixDup[pos] < n) valid = false;
            if (valid) answer.insert((n - k) % s);
        }
        cout << answer.size() << "\n";
    }
    return 0;
}
