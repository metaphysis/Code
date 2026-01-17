// Ransom Note
// UVa ID: 10580
// Verdict: Accepted
// Submission Date: 2026-01-12
// UVa Run Time: 0.050s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 140010;

// 计数排序，用于后缀数组构建
void countSort(int *s, int *ranks, int *sa, int n, int m) {
    static int cnt[MAXN];
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; i++) cnt[s[ranks[i]]]++;
    for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; i--) sa[--cnt[s[ranks[i]]]] = ranks[i];
}

// 构建后缀数组（倍增算法）
void buildSA(int *s, int *sa, int n, int m) {
    static int ranks[MAXN] = {}, higher[MAXN] = {}, lower[MAXN] = {};
    iota(ranks, ranks + MAXN, 0);
    countSort(s, ranks, sa, n, m);
    ranks[sa[0]] = 0;
    for (int i = 1; i < n; i++) {
        ranks[sa[i]] = ranks[sa[i - 1]];
        ranks[sa[i]] += (s[sa[i]] != s[sa[i - 1]]);
    }
    for (int i = 0; (1 << i) < n; i++) {
        for (int j = 0; j < n; j++) {
            higher[j] = ranks[j] + 1;
            lower[j] = (j + (1 << i) >= n) ? 0 : (ranks[j + (1 << i)] + 1);
            sa[j] = j;
        }
        countSort(lower, sa, ranks, n, n);
        countSort(higher, ranks, sa, n, n);
        ranks[sa[0]] = 0;
        for (int j = 1; j < n; j++) {
            ranks[sa[j]] = ranks[sa[j - 1]];
            ranks[sa[j]] += (higher[sa[j - 1]] != higher[sa[j]] ||
                lower[sa[j - 1]] != lower[sa[j]]);
        }
    }
}

// 构建高度数组（LCP数组）
void getHeight(int *s, int *sa, int *height, int n) {
    static int ranks[MAXN] = {};
    height[0] = 0;
    for (int i = 0; i < n; i++) ranks[sa[i]] = i;
    for (int i = 0, k = 0; i < n; i++, (k ? k-- : 0)) {
        if (ranks[i])
            while (s[i + k] == s[sa[ranks[i] - 1] + k]) k++;
        height[ranks[i]] = k;
    }
}

int main(int argc, char *argv[]) {
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    // 读入数据
    string note, paper, line;
    getline(cin, note);
    while (getline(cin, line)) paper += line + "\n";
    // 连接文本，标记来源
    // 格式：note + "$" + paper + "#"
    int s[MAXN], original[MAXN];
    int n = 0;
    // 1. 添加勒索信部分
    for (int i = 0; i < note.length(); i++) {
        s[i] = note[i];           // 勒索信保持原样（都是小写字母）
        original[i] = 0;          // 标记为勒索信部分
    }
    n = note.length();
    // 2. 添加分隔符'$'
    s[n] = '$';
    original[n] = 2;              // 标记为分隔符
    n++;
    // 3. 添加报纸部分（转换为小写以便匹配）
    for (int i = 0; i < paper.length(); i++) {
        s[n + i] = tolower(paper[i]);  // 转换为小写
        original[n + i] = 1;            // 标记为报纸部分
    }
    n += paper.length();
    // 4. 添加结束符'#'
    s[n] = '#';
    original[n] = 2;              // 标记为分隔符
    n++;
    // 构建后缀数组
    int sa[MAXN];
    buildSA(s, sa, n, 128);       // ASCII字符集大小为128
    // 构建高度数组
    int height[MAXN];
    getHeight(s, sa, height, n);
    // 计算每个后缀的排名（rank数组是sa的逆）
    int rank[MAXN];
    for (int i = 0; i < n; i++) rank[sa[i]] = i;
    // 贪心匹配
    vector<string> clips;
    int idx = 0;
    while (idx < note.length()) {
        // 跳过空格 - 空格通过剪贴边界实现
        if (note[idx] == ' ') {
            idx++;
            continue;
        }
        // 找到当前后缀在sa中的位置
        int notePos = idx;
        int suffixRank = rank[notePos];
        // 向前查找最近的报纸后缀
        int bestLen = 0;
        int bestPos = -1;
        int minLCP = INT_MAX;
        // 向前搜索
        for (int i = suffixRank - 1; i >= 0; i--) {
            // 更新最小LCP
            if (height[i + 1] < minLCP) minLCP = height[i + 1];
            if (minLCP == 0) break;
            // 检查是否是报纸后缀
            if (original[sa[i]] == 1) {
                if (minLCP > bestLen) {
                    bestLen = minLCP;
                    bestPos = sa[i];
                }
                // 根据高度数组的性质，找到来自报纸的匹配即可退出
                break;
            }
        }
        // 向后查找最近的报纸后缀
        minLCP = INT_MAX;
        for (int i = suffixRank; i < n - 1; i++) {
            // 更新最小LCP
            if (height[i + 1] < minLCP) minLCP = height[i + 1];
            if (minLCP == 0) break;
            // 检查是否是报纸后缀
            if (original[sa[i + 1]] == 1) {
                if (minLCP > bestLen) {
                    bestLen = minLCP;
                    bestPos = sa[i + 1];
                }
                // 根据高度数组的性质，找到来自报纸的匹配即可退出
                break;
            }
        }
        // 从bestPos提取bestLen个字符作为剪贴片段
        // 需要转换为原始报纸中的位置
        int paperPos = bestPos - (note.length() + 1);
        string clip = paper.substr(paperPos, bestLen);
        clips.push_back(clip);
        idx += bestLen;
    }
    // 输出结果
    cout << clips.size() << '\n';
    for (const string& clip : clips) cout << clip << '\n';
    return 0;
}
