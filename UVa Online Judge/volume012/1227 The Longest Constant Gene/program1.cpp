// The Longest Constant Gene
// UVa ID: 1227
// Verdict: Accepted
// Submission Date: 2025-10-25
// UVa Run Time: 5.500s

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 7000055;  // 最大字符串长度
 
// 全局数组定义
int sn[N];    // 数值化后的字符串
int sa[N];    // 后缀数组
int pos[N];   // 位置数组，pos[i] 表示后缀 i 在后缀数组中的排名
int c[N];     // 计数数组，用于基数排序
int lcp[N];   // 高度数组，lcp[i] 表示 sa[i] 和 sa[i+1] 的最长公共前缀
 
// 比较函数：比较两个数对 (a, b) 和 (c, d)
inline bool leq(int a, int b, int c, int d) {
    return a == c ? b <= d : a < c;
}
 
// 比较函数：比较两个三元组 (a, b, c) 和 (d, e, f)
inline bool leq(int a, int b, int c, int d, int e, int f) {
    return a == d ? leq(b, c, e, f) : a < d;
}
 
// 基数排序函数
inline void radixSort(int a[], int b[], int r[], int n, int K) {
    memset(c, 0, sizeof(int) * (K + 1));  // 清空计数数组
    // 第一遍：统计每个键值的出现次数
    for (int i = 0; i < n; i++) c[r[a[i]]]++;
    // 第二遍：计算前缀和，确定每个键值的起始位置
    for (int i = 0, sum = 0; i <= K; i++) {
        int t = c[i];
        c[i] = sum;
        sum += t;
    }
    // 第三遍：根据计数数组进行排序
    for (int i = 0; i < n; i++) b[c[r[a[i]]]++] = a[i];
}
 
// DC3 算法核心函数
void DC3algorithm(int s[], int sa[], int n, int K) {
    // 计算各类后缀的数量
    int nL = (n + 2) / 3;  // 模 3 余 1 的后缀数量
    int nM = (n + 1) / 3;  // 模 3 余 2 的后缀数量  
    int nR = n / 3;        // 模 3 余 0 的后缀数量
    int nLR = nL + nR;     // 非模 3 余 0 的后缀总数
 
    // 动态分配辅助数组
    int *sL = new int[nL], *saL = new int[nL];
    int *sMR = new int[nLR + 3], *saMR = new int[nLR + 3];  
 
    // 初始化辅助数组
    for (int i = 0; i < 3; i++)
        sMR[i] = saMR[i] = 0;
 
    // 收集所有非模 3 余 0 的后缀起始位置
    for (int i = 0, j = 0; i < n + nL - nM; i++)
        if (i % 3 != 0)
            sMR[j++] = i;
    
    // 三次基数排序：分别按第 3、2、1 个字符排序
    radixSort(sMR, saMR, s + 2, nLR, K);
    radixSort(saMR, sMR, s + 1, nLR, K);
    radixSort(sMR, saMR, s, nLR, K);
 
    // 为排序后的后缀分配新的名称（离散化）
    int name = 0;
    c[0] = c[1] = c[2] = -1;  // 初始化比较数组
    for (int i = 0; i < nLR; i++) {
        bool equal = true;
        // 检查当前后缀是否与上一个后缀相同
        for (int j = 0; j < 3; j++) {
            equal &= (c[j] == s[saMR[i] + j]);
            c[j] = s[saMR[i] + j];
        }
        if (!equal) name++;  // 如果不同，分配新的名称
        // 根据后缀类型存储名称
        if (saMR[i] % 3 == 1)
            sMR[saMR[i] / 3] = name;        // 模 3 余 1 的后缀
        else
            sMR[saMR[i] / 3 + nL] = name;   // 模 3 余 2 的后缀
    }
 
    // 递归处理：如果名称不唯一，递归排序
    if (name < nLR) {
        DC3algorithm(sMR, saMR, nLR, name);
        for (int i = 0; i < nLR; i++)
            sMR[saMR[i]] = i + 1;
    }
    else {
        // 如果名称唯一，直接构建后缀数组
        for (int i = 0; i < nLR; i++)
            saMR[sMR[i] - 1] = i;
    }
    
    // 收集模 3 余 0 的后缀
    for (int i = 0, j = 0; i < nLR; i++)
        if (saMR[i] < nL)
            sL[j++] = 3 * saMR[i];
    
    // 对模 3 余 0 的后缀进行基数排序
    radixSort(sL, saL, s, nL, K);
    
    // 合并三类后缀的排序结果
    for (int p = 0, t = nL - nM, k = 0; k < n; k++) {
        #define GI (saMR[t] < nL ? 3 * saMR[t] + 1 : 3 * (saMR[t] - nL) + 2)
        int i = GI;  // 获取非模 3 余 0 的后缀起始位置
        int j = saL[p];  // 获取模 3 余 0 的后缀起始位置
        
        // 比较两个后缀，选择较小的放入结果数组
        if (saMR[t] < nL ? 
            leq(s[i], sMR[saMR[t] + nL], s[j], sMR[j / 3]) :
            leq(s[i], s[i + 1], sMR[saMR[t] - nL + 1], s[j], s[j + 1], sMR[j / 3 + nL])
        ) {
            sa[k] = i;  // 选择非模 3 余 0 的后缀
            if (++t == nLR)  // 如果非模 3 余 0 的后缀已用完
                for (k++; p < nL; p++, k++)
                    sa[k] = saL[p];  // 填入剩余的模 3 余 0 的后缀
        }
        else {
            sa[k] = j;  // 选择模 3 余 0 的后缀
            if (++p == nL)  // 如果模 3 余 0 的后缀已用完
                for (k++; t < nLR; t++, k++)
                    sa[k] = GI;  // 填入剩余的非模 3 余 0 的后缀
        }
        #undef GI
    }
    // 释放动态分配的内存
    delete[] sL, saL, sMR, saMR;
}
 
// 构建后缀数组的主函数
void buildSA(char str[], int n) {
    char mn = 127, mx = 0;
    // 找到字符串中的最小和最大字符
    for (int i = 0; i < n; i++) {
        mn = min(mn, str[i]);
        mx = max(mx, str[i]);
    }
    // 将字符映射到 1 开始的整数
    for (int i = 0; i < n; i++)
        sn[i] = str[i] - mn + 1;
    sn[n] = sn[n + 1] = sn[n + 2] = 0;  // 填充 0
    // 调用 DC3 算法构建后缀数组
    DC3algorithm(sn, sa, n, mx - mn + 1);
    // 构建位置数组
    for (int i = 0; i < n; i++)
        pos[sa[i]] = i;
}
 
// 构建高度数组（LCP 数组）
void buildLCP(char s[], int n) {
    for (int i = 0, k = 0; i < n; ++i) {
        if (pos[i] != n - 1) {  // 如果不是最后一个后缀
            int j = sa[pos[i] + 1];  // 获取下一个后缀的起始位置
            // 计算最长公共前缀长度
            while (s[i + k] == s[j + k]) ++k;
            lcp[pos[i]] = k;  // 存储 LCP 值
            if (k) --k;  // 下一个后缀的 LCP 至少为 k-1
        }
        else lcp[pos[i]] = 0;  // 最后一个后缀的 LCP 为 0
    }
}

// 全局变量定义
char s[N];        // 合并后的字符串
bool mark[N];     // 标记数组，用于滑动窗口
int grp[N];       // 组别数组，记录每个位置属于哪个原字符串
int ptr[8];       // 指针数组，记录每个字符串在当前窗口中的位置
int t, m;         // t: 测试用例数, m: 字符串数量
int freq[N];      // 频率数组，用于维护滑动窗口中的 LCP 频率

int main() {
    scanf("%d", &t);  // 读入测试用例数
    while (t--) {
        scanf("%d", &m);  // 读入字符串数量
        char *S = s;      // 指向合并字符串的当前指针
        
        // 处理每个字符串
        for (int i = 0; i < m; ++i) {
            scanf("%s", S);  // 读入字符串
            int len = strlen(S);
            // 字符映射：G->B, T->D，减少字符集大小
            for (int j = 0; j < len; ++j)
                if (S[j] == 'G') S[j] = 'B';
                else if (S[j] == 'T') S[j] = 'D';
            // 记录每个位置所属的原字符串
            fill(grp + (S - s), grp + (S + len - s), i);
            S += len;
            grp[S - s] = -1;    // 分隔符位置标记为 -1
            S[0] = 'A' - 1;     // 添加分隔符（小于所有正常字符）
            S[1] = '\0';
            ++S;
            ptr[i] = -1;         // 初始化指针
        }
        
        int n = S - s;  // 计算合并后字符串的总长度
        buildSA(s, n);  // 构建后缀数组
        buildLCP(s, n); // 构建高度数组
        
        // 初始化滑动窗口
        int needed = m, R;
        // 找到包含所有 m 个字符串的最小窗口
        for (R = 0; R < n && needed > 0; ++R) {
            int g = grp[sa[R]];  // 获取当前后缀所属的原字符串
            if (~g && !~ptr[g]) {  // 如果该字符串还未在窗口中
                mark[R] = true;    // 标记该位置
                ptr[g] = R;        // 记录该字符串在窗口中的位置
                --needed;          // 减少需要的字符串数量
            }
        }
        --R;  // 调整右边界
        
        int L = *min_element(ptr, ptr + m);  // 找到窗口左边界
        memset(freq, 0, sizeof(int) * (n + 1));  // 初始化频率数组
        int mn = 2147483647;  // 当前窗口中的最小 LCP 值
        
        // 初始化窗口内的 LCP 频率
        for (int i = L; i < R; ++i) {
            ++freq[lcp[i]];
            mn = min(mn, lcp[i]);
        }
        int mx = mn;  // 记录全局最大最小 LCP 值
        
        // 滑动窗口过程
        while (true) {
            // 寻找下一个要移出窗口的字符串的右边界
            int march = L + 1;
            while (march < n && grp[sa[march]] != grp[sa[L]])
                ++march;
            if (march >= n) break;  // 如果找不到，结束
            
            int fmark = march;
            // 寻找实际要移动到的位置
            for (int i = march - 1; i > L; --i)
                if (mark[i])
                    fmark = i;
            
            // 更新标记
            mark[L] = 0;
            mark[march] = 1;
            
            // 扩展右边界
            while (march > R) {
                ++freq[lcp[R]];
                mn = min(mn, lcp[R++]);
            }
            
            // 收缩左边界
            while (L < fmark) {
                --freq[lcp[L++]];
                while (freq[mn] == 0) ++mn;  // 更新最小 LCP 值
            }
            
            mx = max(mx, mn);  // 更新全局最大值
        }
        
        printf("%d\n", mx);  // 输出结果
    }
    return 0;
}
