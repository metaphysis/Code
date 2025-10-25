// Advertisement
// UVa ID: 10148
// Verdict: Accepted
// Submission Date: 2025-10-25
// UVa Run Time: 0.980s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

// 定义慢跑者结构体，存储起始和结束广告牌编号
struct Jogger {
    int start, end;
};

// 比较函数：按右端点升序排序，右端点相同时按左端点升序
bool compareJogger(const Jogger& a, const Jogger& b) {
    if (a.end == b.end) return a.start < b.start;
    return a.end < b.end;
}

void solve() {
    int K, N;
    cin >> K >> N;
    
    vector<Jogger> joggers(N);
    for (int i = 0; i < N; i++) {
        int a, b;
        cin >> a >> b;
        // 确保区间有效（start <= end）
        if (a > b) swap(a, b);
        joggers[i] = {a, b};
    }
    
    // 按右端点排序
    sort(joggers.begin(), joggers.end(), compareJogger);
    
    // 使用集合存储已选择的广告牌位置
    set<int> advertisements;
    
    // 处理每个慢跑者的区间
    for (const auto& j : joggers) {
        int count = 0;
        // 统计当前区间内已有的广告数量
        for (int pos = j.start; pos <= j.end; pos++) {
            if (advertisements.find(pos) != advertisements.end()) {
                count++;
            }
        }
        
        // 计算还需要放置的广告数量
        int need = K - count;
        if (need > 0) {
            // 从右往左放置广告，最大化共享效果
            for (int pos = j.end; pos >= j.start && need > 0; pos--) {
                if (advertisements.find(pos) == advertisements.end()) {
                    advertisements.insert(pos);
                    need--;
                }
            }
        }
    }
    
    // 输出结果
    cout << advertisements.size() << endl;
    for (int pos : advertisements) {
        cout << pos << endl;
    }
}

int main() {
    int testCases;
    cin >> testCases;
    
    for (int t = 0; t < testCases; t++) {
        if (t > 0) cout << endl;  // 测试用例之间用空行分隔
        solve();
    }
    
    return 0;
}
