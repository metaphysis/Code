// Hidden Squares
// UVa ID: 10504
// Verdict: Accepted
// Submission Date: 2025-11-05
// UVa Run Time: 0.110s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <set>
#include <string>
using namespace std;

// 坐标点结构体
struct Point {
    int x, y;
    Point(int x_, int y_) : x(x_), y(y_) {}
    // 重载小于运算符，用于set排序
    bool operator<(const Point& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

/**
 * 统计给定点集中可以形成的正方形数量
 * @param points 目标字母的所有坐标集合
 * @return 正方形数量
 */
int countSquares(const set<Point>& points) {
    int cnt = 0;
    // 将set转换为vector便于遍历
    vector<Point> vec(points.begin(), points.end());
    int n = vec.size();
    
    // 枚举所有点对
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int x1 = vec[i].x, y1 = vec[i].y;
            int x2 = vec[j].x, y2 = vec[j].y;
            
            // 计算两点之间的向量
            int dx = x2 - x1, dy = y2 - y1;
            
            // 第一种可能的正方形（顺时针旋转）
            Point p3(x1 - dy, y1 + dx);
            Point p4(x2 - dy, y2 + dx);
            if (points.count(p3) && points.count(p4)) {
                cnt++;
            }
            
            // 第二种可能的正方形（逆时针旋转）
            Point p5(x1 + dy, y1 - dx);
            Point p6(x2 + dy, y2 - dx);
            if (points.count(p5) && points.count(p6)) {
                cnt++;
            }
        }
    }
    
    // 每个正方形被计数4次（4条边）
    return cnt / 4;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    bool firstProblem = true;
    
    // 处理多个测试用例，直到遇到0
    while (cin >> n && n != 0) {
        // 问题之间输出空行
        if (!firstProblem) {
            cout << "\n";
        }
        firstProblem = false;
        
        int m;
        cin >> m;
        vector<string> grid(n);
        
        // 读入网格
        for (int i = 0; i < n; ++i) {
            cin >> grid[i];
        }
        
        // 处理每个目标字母
        for (int letterIdx = 0; letterIdx < m; ++letterIdx) {
            char target;
            cin >> target;
            set<Point> points;
            
            // 收集目标字母的所有位置
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (grid[i][j] == target) {
                        points.insert(Point(i, j));
                    }
                }
            }
            
            // 统计并输出结果
            int squares = countSquares(points);
            cout << target << " " << squares << "\n";
        }
    }
    
    return 0;
}
