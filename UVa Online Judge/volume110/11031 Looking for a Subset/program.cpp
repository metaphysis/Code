// Looking for a Subset
// UVa ID: 11031
// Verdict: Accepted
// Submission Date: 2025-12-28
// UVa Run Time: 0.060s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;
int n, q, a[MAXN], lds[MAXN], bit[MAXN];

inline int lowbit(int x) { return x & -x; }

void modify(int x, int val, int n) {
    while (x <= n) bit[x] = max(bit[x], val), x += lowbit(x);
}

int query(int x) {
    int ret = 0;
    while (x) ret = max(ret, bit[x]), x -= lowbit(x);
    return ret;
}

int main() {
    int caseNo = 1;
    while (scanf("%d %d", &n, &q) == 2 && (n || q)) {
        // 读入并离散化
        vector<int> vec;
        for (int i = 0; i < n; ++i) scanf("%d", &a[i]), vec.push_back(a[i]);
        sort(vec.begin(), vec.end());
        vec.erase(unique(vec.begin(), vec.end()), vec.end());
        map<int, int> mp;
        for (size_t i = 0; i < vec.size(); ++i) mp[vec[i]] = vec.size() - i; // 反向映射
        
        // 计算LDS（从后往前的最长递减子序列）
        memset(bit, 0, sizeof(bit));
        int maxLen = 0;
        for (int i = n - 1; i >= 0; --i) {
            int pos = mp[a[i]];
            lds[i] = query(pos - 1) + 1;  // 查询比当前值大的位置
            modify(pos, lds[i], vec.size());
            maxLen = max(maxLen, lds[i]);
        }
        
        printf("Set %d:\n", caseNo++);
        for (int queryNo = 1; queryNo <= q; ++queryNo) {
            int m; scanf("%d", &m);
            printf("    Subset %d:\n", queryNo);
            if (m > maxLen) { printf("    Impossible\n"); continue; }
            
            // 贪心构造字典序最小的序列
            printf("    ");
            int last = INT_MIN, first = 1;
            for (int i = 0; i < n && m; ++i) {
                if (lds[i] >= m && a[i] > last) {
                    if (!first) printf(" ");
                    printf("%d", a[i]);
                    last = a[i];
                    --m;
                    first = 0;
                }
            }
            printf("\n");
        }
    }
    return 0;
}
