// Introspective Caching
// UVa ID: 11563
// Verdict: Accepted
// Submission Date: 2026-01-06
// UVa Run Time: 0.240s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9; // 表示未来不会再次访问

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int c, n, a;
    while (cin >> c >> n >> a) {
        vector<int> accesses(a);
        for (int i = 0; i < a; i++) cin >> accesses[i];

        // 预计算每个位置的下一次出现位置
        vector<int> nextPos(a, INF);
        unordered_map<int, int> lastPos; // 对象 -> 上一次出现的位置
        for (int i = a - 1; i >= 0; i--) {
            int obj = accesses[i];
            if (lastPos.count(obj)) nextPos[i] = lastPos[obj];
            lastPos[obj] = i;
        }

        unordered_set<int> cache;           // 当前缓存中的对象
        // 使用set而不是priority_queue，以便删除特定元素
        // 存储 (next_access_time, object)
        set<pair<int, int>> nextAccessSet;
        // 对象 -> 它在nextAccessSet中的迭代器（用于删除）
        unordered_map<int, set<pair<int, int>>::iterator> objToIterator;

        int missCount = 0;

        for (int i = 0; i < a; i++) {
            int obj = accesses[i];
            
            if (cache.find(obj) != cache.end()) {
                // 缓存命中，需要更新该对象的下一次访问位置
                auto it = objToIterator[obj];
                nextAccessSet.erase(it);
                
                int nextTime = (nextPos[i] == INF) ? INF : nextPos[i];
                auto newIt = nextAccessSet.insert({nextTime, obj}).first;
                objToIterator[obj] = newIt;
                continue;
            }

            // 缓存未命中
            missCount++;

            if (cache.size() < c) {
                // 缓存未满，直接加入
                cache.insert(obj);
                int nextTime = (nextPos[i] == INF) ? INF : nextPos[i];
                auto it = nextAccessSet.insert({nextTime, obj}).first;
                objToIterator[obj] = it;
            } else {
                // 缓存已满，需要替换
                // 选择未来最晚访问的对象（set中最大的，因为INF表示永不访问）
                auto lastIt = prev(nextAccessSet.end());
                int removeObj = lastIt->second;
                
                // 从缓存和set中移除
                cache.erase(removeObj);
                nextAccessSet.erase(lastIt);
                objToIterator.erase(removeObj);
                
                // 插入新对象
                cache.insert(obj);
                int nextTime = (nextPos[i] == INF) ? INF : nextPos[i];
                auto newIt = nextAccessSet.insert({nextTime, obj}).first;
                objToIterator[obj] = newIt;
            }
        }

        cout << missCount << "\n";
    }

    return 0;
}
