// L-Gap Substrings
// UVa ID: 10829
// Verdict: Accepted
// Submission Date: 2025-12-05
// UVa Run Time: 0.040s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int N = 500050;

char s[N];

// 后缀数组结构体，用于构建后缀数组、高度数组和RMQ查询
struct SuffixArray {
    int sa[N];       // 后缀数组，sa[i]表示排第i名的后缀的起始下标
    int t1[N], t2[N], c[N];  // 临时数组和计数数组，用于基数排序
    int height[N];   // 高度数组，height[i] = LCP(sa[i-1], sa[i])
    int rnk[N];      // 排名数组，rnk[i]表示起始位置为i的后缀的排名
    int lg[N], st[30][N]; // RMQ所需：lg数组用于快速计算log，st为稀疏表

    // 构建后缀数组，n为字符串长度+1（包含末尾的0），m为字符集大小
    void buildSA(int n, int m) {
        int i, *x = t1, *y = t2;
        // 第一轮基数排序：按第一个字符排序
        for (i = 0; i < m; i++) c[i] = 0;
        for (i = 0; i < n; i++) c[x[i] = s[i]]++;
        for (i = 1; i < m; i++) c[i] += c[i - 1];
        for (i = n - 1; i >= 0; i--) sa[--c[x[i]]] = i;
        
        // 倍增算法，k为当前比较的步长
        for (int k = 1; k <= n; k <<= 1) {
            int p = 0;
            // 对第二关键字排序：没有第二关键字的排在最前面
            for (i = n - k; i < n; i++) y[p++] = i;
            // 根据上一轮的sa数组确定第二关键字顺序
            for (i = 0; i < n; i++)
                if (sa[i] >= k) y[p++] = sa[i] - k;
            
            // 对第一关键字排序
            for (i = 0; i < m; i++) c[i] = 0;
            for (i = 0; i < n; i++) c[x[y[i]]]++;
            for (i = 1; i < m; i++) c[i] += c[i - 1];
            for (i = n - 1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];
            
            // 生成新的rank数组
            swap(x, y);
            p = 1;
            x[sa[0]] = 0;
            for (i = 1; i < n; i++)
                // 如果当前后缀和前一个后缀的两个关键字都相同，则排名相同
                x[sa[i]] = (y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k]) ? p - 1 : p++;
            
            // 如果所有后缀的排名都已不同，则提前结束
            if (p >= n) break;
            m = p; // 更新字符集大小
        }
    }
    
    // 计算高度数组（LCP数组）
    void getHeight(int n) {
        int k = 0;
        // 计算rank数组
        for (int i = 1; i <= n; i++) rnk[sa[i]] = i;
        
        // 计算每个后缀与它前一名的后缀的LCP
        for (int i = 0; i < n; i++) {
            if (k) k--; // height[rank[i]] >= height[rank[i-1]] - 1
            int j = sa[rnk[i] - 1]; // 排名在i之前一位的后缀起始位置
            while (s[i + k] == s[j + k]) k++; // 扩展匹配
            height[rnk[i]] = k;
        }
    }
    
    // 初始化RMQ稀疏表，用于快速查询任意两个后缀的LCP
    void initilizeRMQ(int n) {
        // 预处理log数组，用于RMQ查询时快速计算分段长度
        lg[0] = -1;
        for (int i = 1; i <= n; i++)
            lg[i] = lg[i >> 1] + 1;
        
        // 初始化ST表第一层
        for (int i = 1; i <= n; i++)
            st[0][i] = height[i];
        
        // 构建ST表，st[j][i]表示区间[i, i+2^j-1]的最小值
        for (int j = 1; (1 << j) <= n; j++)
            for (int i = 1; i + (1 << j) - 1 <= n; i++)
                st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
    }
    
    // 查询两个后缀的最长公共前缀（LCP）
    int RMQ(int L, int R) {
        // 将字符串位置转换为排名
        L = rnk[L]; R = rnk[R];
        if (L > R) swap(L, R); // 确保L <= R
        L++; // height数组从1开始，表示排名相邻后缀的LCP
        // 使用RMQ查询区间[L, R]的最小值
        int k = lg[R - L + 1];
        return min(st[k][L], st[k][R - (1 << k) + 1]);
    }
};

SuffixArray suf, rev; // 正向和反向后缀数组

int main() {
    int T, cases = 0;
    scanf("%d", &T);
    while (T--) {
        int g;
        scanf("%d%s", &g, s);
        int n = strlen(s);
        
        // 构建正向后缀数组（用于计算两个子串的最长公共前缀LCP）
        suf.buildSA(n + 1, 128); // n+1是为了包含字符串结束符
        suf.getHeight(n);
        suf.initilizeRMQ(n);
        
        // 构建反向后缀数组（用于计算两个子串的最长公共后缀LCS）
        // 通过反转字符串，将LCS问题转化为LCP问题
        for (int i = 0; i < n / 2; i++) swap(s[i], s[n - 1 - i]);
        rev.buildSA(n + 1, 128);
        rev.getHeight(n);
        rev.initilizeRMQ(n);
        
        long long sum = 0;
        
        // 枚举U的长度len
        for (int len = 1; len <= n / 2; len++) {
            // 枚举第一个U的起始位置i，这里使用了跳跃枚举优化
            // 由于我们只关心相距len+g的位置对，所以可以按len步长跳跃
            for (int i = 0; i < n; i += len) {
                int L = i, R = i + g + len; // 第二个U的起始位置
                if (R >= n) break; // 第二个U超出字符串范围
                
                // 计算LCP：从L和R开始的最长公共前缀
                // 限制不超过U的长度len
                int lcp = min(len, suf.RMQ(L, R));
                
                // 计算LCS：到L-1和R-1结束的最长公共后缀
                // 通过反向字符串的LCP计算
                L = n - L - 1; // 转换为反向字符串中的位置
                R = n - R - 1;
                int lcs = min(len, rev.RMQ(L, R));
                
                // 有效的匹配长度计算：
                // 考虑重叠情况：总匹配长度 = lcp + lcs - len
                // 这是因为两个U的长度为len，而lcp和lcs可能重叠
                int cnt = lcp + lcs - len;
                sum += max(cnt, 0); // 只累加非负值
            }
        }
        
        printf("Case %d: %lld\n", ++cases, sum);
    }
    return 0;
}
