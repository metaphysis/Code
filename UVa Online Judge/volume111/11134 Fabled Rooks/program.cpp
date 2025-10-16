// Fabled Rooks
// UVa ID: 11134
// Verdict: Accepted
// Submission Date: 2025-10-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

// 区间结构体：l左边界，r右边界，id在输入中的序号
struct Interval {
    int l, r, id;
    // 按右端点升序排序，右端点相同时按左端点升序
    bool operator<(const Interval& other) const {
        return r < other.r || (r == other.r && l < other.l);
    }
};

// 贪心分配函数：为每个区间分配一个唯一的位置
bool assign(vector<Interval>& intervals, int n, int result[]) {
    sort(intervals.begin(), intervals.end());  // 按右端点排序
    bool used[5005] = {false};  // 标记位置是否已被使用
    
    for (const auto& iv : intervals) {
        bool found = false;
        // 从左边界开始找到第一个可用的位置
        for (int pos = iv.l; pos <= iv.r; pos++) {
            if (!used[pos]) {
                used[pos] = true;      // 标记为已使用
                result[iv.id] = pos;   // 记录分配结果
                found = true;
                break;
            }
        }
        if (!found) return false;  // 如果找不到可用位置，分配失败
    }
    return true;
}

int main() {
    int n;
    while (cin >> n && n) {
        vector<Interval> rows(n), cols(n);
        
        // 读取输入数据
        for (int i = 0; i < n; i++) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            // 分别存储行区间和列区间
            rows[i] = {x1, x2, i};
            cols[i] = {y1, y2, i};
        }
        
        int row_pos[5005], col_pos[5005];  // 存储分配结果
        
        // 分别对行和列进行分配
        if (assign(rows, n, row_pos) && assign(cols, n, col_pos)) {
            // 输出每个车的最终位置
            for (int i = 0; i < n; i++) {
                cout << row_pos[i] << " " << col_pos[i] << "\n";
            }
        } else {
            cout << "IMPOSSIBLE\n";
        }
    }
    return 0;
}

