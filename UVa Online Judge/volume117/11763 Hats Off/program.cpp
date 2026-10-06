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

因此，很有可能在线测试数据存在问题，导致难以通过，除非能够复现标准代码的行为，使得产生的输出与标准输出一致，但这样难度太大。
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
