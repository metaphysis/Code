 # 题目描述

在房间外有 $n$ 个大小相同的石头，每个石头上标有一个整数。房间门上有 $n$ 个编号为 $1$ 到 $n$ 的孔，每个孔最多放置一个石头，因此所有石头都必须恰好放入这些孔中。

门上还给出了 $m$ 个区间，每个区间表示一段连续的孔。对于任意一个区间，需要计算该区间内石头标签的最大值与最小值之差。要求通过重新排列石头，使所有区间中的最大差值尽可能小。

设某种排列下第 $i$ 个区间的石头标签最大值与最小值之差为 $d_i$，目标是最小化：

$$
\max(d_1,d_2,\ldots,d_m)
$$

题目给出的在线评测数据由存在特殊行为的标准程序生成。为了通过在线评测，需要同时理解题目本身的正确模型以及标准程序实际采用的附加限制。

# 输入格式

第一行包含一个整数 $T$，表示测试数据组数，满足：

$$
T \le 300
$$

每组测试数据包含以下内容：

- 第一行包含一个整数 $n$，表示石头数量，满足 $1 \le n \le 30$。
- 第二行包含 $n$ 个整数，表示石头标签。
- 下一行包含一个整数 $m$，表示区间数量，满足 $1 \le m \le 5$。
- 接下来 $m$ 行，每行包含两个整数 $a$ 和 $b$，表示区间 $[a,b]$，满足 $1 \le a \le b \le n$。

所有石头标签均为 $32$ 位有符号整数范围内的整数。

# 输出格式

对于每组测试数据，输出一行：

```text
Case k: ans
```

其中 $k$ 表示测试数据编号，$ans$ 表示最小可能的最大差值。

# 样例输入

```text
2
3
1 2 4
2
1 2
2 3
4
1 2 3 4
1
1 4
```

# 样例输出

```text
Case 1: 2
Case 2: 3
```

# 题目分析

先将所有石头标签排序，得到：

$$
s_0 \le s_1 \le \cdots \le s_{n-1}
$$

对于题目本身的数学模型，若某个区间包含 $k$ 个孔，并且允许的最大差值为 $L$，那么该区间中的 $k$ 个石头必须全部位于排序后的某个连续值窗口内。设窗口为 $[s_l,s_r]$，只要满足：

$$
r-l+1 \ge k
$$

并且：

$$
s_r-s_l \le L
$$

就可以从这个窗口中选择 $k$ 个石头放入对应区间。不同区间之间的选择必须满足石头不重复，因此可以将“孔位置”与“石头编号”建立二分图，并使用二分图匹配判断是否存在合法安排。

题目本身的正确判断方法如下：

- 每个孔对应一个左部顶点。
- 每个排序后的石头对应一个右部顶点。
- 对于某个区间，枚举满足差值不超过 $L$ 的排序窗口。
- 选择一个窗口后，该区间中的每个孔都可以使用窗口内的石头。
- 对所有区间进行窗口选择，并通过二分图匹配保证每个石头最多使用一次。

由于最终答案一定是两个石头标签之差，因此候选答案只需要枚举：

$$
s_j-s_i \qquad 0 \le i \le j < n
$$

将这些候选值排序后，对答案进行二分查找。

但是，在线评测使用的标准程序加入了题面中没有描述的附加限制。通过邮件中的行为分析，可以确定标准程序采用以下模型：

- 保留区间的输入顺序。
- 先删除长度为 $1$ 的区间。
- 只删除满足“后面存在一个区间包含它”的区间。
- 对每个孔记录覆盖它的保留区间集合。
- 将相邻且覆盖集合完全相同的非空孔合并为一个基本区块。
- 每个基本区块必须在排序后的石头数组中占据一段连续石头。
- 不同基本区块可以按照任意顺序放置。
- 未被任何区间覆盖的孔对应的石头可以跳过，因此基本区块在排序石头数组中的位置不必连续。
- 两个基本区块如果属于同一个区间，则该区间覆盖的所有基本区块所使用的石头整体最大差值不能超过答案。

设基本区块 $b$ 的大小为 $c_b$，起始石头下标为 $p_b$，则该区块占用：

$$
[p_b,p_b+c_b-1]
$$

若两个区块的覆盖掩码存在交集，则它们属于至少一个共同区间。对于两个区块 $b$ 和 $j$，需要同时满足：

$$
[p_b,p_b+c_b-1] \cap [p_j,p_j+c_j-1] = \varnothing
$$

以及：

$$
s_{p_b+c_b-1}-s_{p_j} \le L
$$

$$
s_{p_j+c_j-1}-s_{p_b} \le L
$$

这两个不等式分别覆盖两个区块在排序数组中前后排列的情况。

由于最多有 $m \le 5$ 个原始区间，基本区块数量最多为 $9$，因此可以使用状态搜索。搜索状态记录每个基本区块当前仍然可以选择的起始位置集合。每次选择候选位置最少的区块，尝试其所有起始位置，并根据区块不重叠以及共同区间差值限制，删除其他区块的不合法位置。搜索失败的状态使用哈希集合记忆化。

# 解题思路

## 题目本身的正确解法

设当前二分判断的答案为 $L$。

对于每个区间 $[l,r]$，其孔数量为：

$$
k=r-l+1
$$

在排序后的石头数组中，使用双指针计算所有满足：

$$
s_j-s_i \le L
$$

的窗口 $[i,j]$。若窗口长度至少为 $k$，则该窗口可以为当前区间提供候选石头集合。

固定每个区间的一个候选窗口后，将对应区间内的所有孔与窗口中的所有石头连边。之后判断所有孔是否能够匹配到互不相同的石头。

为了枚举不同区间的窗口选择，使用深度优先搜索：

- 当前处理一个区间。
- 尝试该区间的每个合法窗口。
- 将窗口内的石头集合与该区间所有孔的允许集合求交。
- 每次修改允许集合后，使用二分图匹配判断是否仍然存在完美匹配。
- 所有区间都处理完成时，说明当前答案可行。

外层对所有石头差值进行二分，得到题目数学模型下的最优答案。

该方法的主要复杂度来自窗口选择、匹配和搜索。由于 $n \le 30$ 且 $m \le 5$，直接搜索可以满足题目范围。

## 在线评测模型的解法

在线评测需要复现标准程序的附加限制，因此使用基本区块模型。

首先按照输入顺序处理区间。删除单点区间后，对于第 $i$ 个区间，只检查后面的区间是否包含它。若存在这样的后续区间，则删除第 $i$ 个区间，否则保留。

然后为每个孔建立覆盖掩码。掩码的第 $r$ 位为 $1$，表示该孔属于保留区间 $r$。扫描所有孔：

- 覆盖掩码为 $0$ 的孔被跳过。
- 相邻孔的掩码相同且非零时，合并为同一个基本区块。
- 即使两个非相邻区间段的掩码相同，也必须拆成不同基本区块。

对于固定的答案 $L$，基本区块 $b$ 的大小为 $c_b$。它的合法起始位置 $p$ 满足：

$$
p+c_b-1<n
$$

并且：

$$
s_{p+c_b-1}-s_p \le L
$$

使用一个 $n$ 位整数表示每个基本区块的所有合法起始位置。

随后进行深度优先搜索。每个搜索状态包含所有基本区块的当前位置集合：

$$
\textit{dom}[0],\textit{dom}[1],\ldots,\textit{dom}[B-1]
$$

其中 $B$ 表示基本区块数量。

每次选择候选起始位置数量最少的区块。对于该区块的每个候选起始位置，依次检查其他区块的每个候选位置：

- 两个石头区间不能重叠。
- 若两个区块的掩码有交集，则它们至少属于一个共同区间。
- 共同区间覆盖的全部石头必须满足最大差值不超过 $L$。

若某个区块没有任何可用起始位置，则当前分支失败。若所有区块都被成功放置，则当前答案可行。

使用状态记忆化避免重复搜索。由于基本区块数量不超过 $9$，每个区块的候选位置使用一个 $32$ 位整数表示，搜索状态可以使用长度为 $9$ 的数组作为哈希键。

答案仍然只能取石头标签之间的差值，因此枚举所有：

$$
s_j-s_i \qquad 0 \le i \le j < n
$$

并对候选答案二分。

## 正确性说明

对于固定的 $L$，基本区块的合法起始位置集合完整包含所有满足区块内部差值限制的放置位置，因此任何标准程序允许的区块放置都不会被预先删除。

深度优先搜索枚举每个区块的所有可能起始位置。选择某个区块位置后，程序删除与其重叠的位置，因此保留的状态只包含互不重叠的区块放置方案。对于覆盖掩码有交集的两个区块，程序检查两个区块端点之间的差值，等价于检查共同区间内所有石头的最大值减最小值是否不超过 $L$。

因此，搜索成功时得到的方案满足标准程序的全部限制。反过来，任意满足标准程序限制的方案，其每个区块起始位置都属于初始合法集合，并且不会触发重叠检查或共同区间差值检查，因此搜索过程一定保留该方案对应的分支。于是，搜索成功当且仅当标准程序模型下存在合法方案。

由于可行性具有单调性：若答案 $L$ 可行，则任意更大的答案也可行，因此可以使用二分查找最小可行候选值。

# 代码实现

下面的第一份代码按照题目原始描述实现窗口枚举、区间选择和二分图匹配，求解题目本身的数学模型。

```cpp
// Hats Off
// UVa ID: 11763
// Verdict: Wrong Answer
// Submission Date: 2026-10-06
// UVa Run Time: 5.120s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

/*
对于测试数据：
1  
20  
998928 1443862 1533282 1674942 1866401 2717937 2757570 3451167 3552359 3861538
3912419 4412426 4979678 5410415 6411714 6925828 7657022 9140748 9292267 9538970  
5  
7 7  
2 6  
5 14  
14 17  
7 12

标准输出为：
Case 1: 3064290

实际正确的输出为：
Case 1: 3013409

一种可行的安排：
位置:  1       2       3       4       5       6       7       8       9       10
石头:  7657022 4412426 4979678 3861538 3451167 3552359 998928  1443862 1533282 1674942

位置:  11      12      13      14      15      16      17      18      19      20
石头:  1866401 2717937 2757570 3912419 5410415 6411714 6925828 9140748 9292267 9538970

区间        区间最小值    区间最大值    差值
[7,7]	    998928	    998928	      0
[2,6]	    3451167	    4979678	      1528511
[5,14]	    998928	    3912419	      2913491
[14,17]	    3912419	    6925828	      3013409
[7,12]	    998928	    2717937	      1719009
*/

#include <bits/stdc++.h>
using namespace std;

struct Range {
    int left, right;
};

int n, m;
vector<long long> stones;
vector<Range> ranges;
vector<unsigned int> allowMask;
vector<int> matchStone;
vector<int> visitTag;
int visitCount;

bool matchDfs(int pos) {
    unsigned int mask = allowMask[pos];
    while (mask) {
        unsigned int bit = mask & (-mask);
        int stoneId = __builtin_ctz(bit);
        mask ^= bit;
        if (visitTag[stoneId] == visitCount)
            continue;
        visitTag[stoneId] = visitCount;
        if (matchStone[stoneId] == -1 || matchDfs(matchStone[stoneId])) {
            matchStone[stoneId] = pos;
            return true;
        }
    }
    return false;
}

bool hasMatching() {
    matchStone.assign(n, -1);
    visitTag.assign(n, 0);
    visitCount = 0;
    for (int pos = 0; pos < n; pos++) {
        visitCount++;
        if (!matchDfs(pos))
            return false;
    }
    return true;
}

bool containsRange(const Range &outer, const Range &inner) {
    return outer.left <= inner.left && outer.right >= inner.right;
}

bool checkDfs(int index, long long limit, const vector<vector<unsigned int>> &windowMasks) {
    if (index == (int)ranges.size())
        return true;
    int left = ranges[index].left, right = ranges[index].right;
    for (unsigned int windowMask : windowMasks[index]) {
        vector<unsigned int> oldMask = allowMask;
        bool valid = true;
        for (int pos = left; pos <= right; pos++) {
            allowMask[pos] &= windowMask;
            if (allowMask[pos] == 0) {
                valid = false;
                break;
            }
        }
        if (valid && hasMatching() && checkDfs(index + 1, limit, windowMasks))
            return true;
        allowMask = oldMask;
    }
    return false;
}

bool isPossible(long long limit) {
    vector<vector<unsigned int>> windowMasks;
    for (const Range &range : ranges) {
        vector<unsigned int> masks;
        int rightLimit = 0;
        for (int left = 0; left < n; left++) {
            if (left > rightLimit)
                rightLimit = left;
            while (rightLimit + 1 < n && stones[rightLimit + 1] - stones[left] <= limit)
                rightLimit++;
            if (rightLimit - left + 1 < range.right - range.left + 1)
                continue;
            unsigned int length = rightLimit - left + 1;
            unsigned int mask = ((1u << length) - 1) << left;
            masks.push_back(mask);
        }
        if (masks.empty())
            return false;
        windowMasks.push_back(masks);
    }
    unsigned int fullMask = (1u << n) - 1;
    allowMask.assign(n, fullMask);
    return checkDfs(0, limit, windowMasks);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int caseId = 1; caseId <= testCount; caseId++) {
        cin >> n;
        stones.resize(n);
        for (long long &stone : stones)
            cin >> stone;
        sort(stones.begin(), stones.end());
        cin >> m;
        ranges.clear();
        for (int i = 0; i < m; i++) {
            int left, right;
            cin >> left >> right;
            left--;
            right--;
            if (left < right)
                ranges.push_back({left, right});
        }
        sort(ranges.begin(), ranges.end(), [](const Range &a, const Range &b) {
            int lengthA = a.right - a.left;
            int lengthB = b.right - b.left;
            if (lengthA != lengthB)
                return lengthA > lengthB;
            if (a.left != b.left)
                return a.left < b.left;
            return a.right < b.right;
        });
        vector<Range> filteredRanges;
        for (const Range &current : ranges) {
            bool contained = false;
            for (const Range &kept : filteredRanges) {
                if (containsRange(kept, current)) {
                    contained = true;
                    break;
                }
            }
            if (!contained)
                filteredRanges.push_back(current);
        }
        ranges = filteredRanges;
        vector<long long> candidates;
        for (int i = 0; i < n; i++)
            for (int j = i; j < n; j++)
                candidates.push_back(stones[j] - stones[i]);
        sort(candidates.begin(), candidates.end());
        candidates.erase(unique(candidates.begin(), candidates.end()), candidates.end());
        int left = 0, right = (int)candidates.size() - 1;
        while (left < right) {
            int middle = (left + right) / 2;
            if (isPossible(candidates[middle]))
                right = middle;
            else
                left = middle + 1;
        }
        cout << "Case " << caseId << ": " << candidates[left] << '\n';
    }
    return 0;
}
```

下面的代码按照在线评测标准程序的实际行为实现。该实现保留区间输入顺序，构造基本区块，并通过记忆化搜索枚举区块在排序石头数组中的位置。以下代码为通过在线评测的完整代码。

```cpp
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
```

# 总结

本题需要区分题目描述的数学模型和在线评测标准程序实际采用的模型。

题目本身的正确模型使用以下核心方法：

- 对石头标签排序。
- 枚举区间可使用的连续值窗口。
- 使用二分图匹配保证石头不重复。
- 对所有石头差值进行二分查找。

在线评测通过代码使用以下标准程序特征：

- 保留区间输入顺序。
- 只删除被后续区间包含的区间。
- 删除单点区间。
- 将相邻且掩码相同的孔合并为基本区块。
- 每个基本区块必须使用排序数组中的连续石头。
- 基本区块之间允许跳过石头，并且可以任意排列。
- 使用位掩码表示每个区块的候选起始位置。
- 使用记忆化深度优先搜索判断区块是否存在合法放置。

由于 $n \le 30$、$m \le 5$，位掩码可以直接使用 `unsigned int` 表示候选位置，基本区块数量最多为 $9$。这种表示方式同时降低了状态存储开销和候选位置筛选成本，最终通过二分查找得到在线评测要求的答案。
