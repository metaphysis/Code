// Amphiphilic Carbon Molecules
// UVa ID: 1606
// Verdict: Accepted
// Submission Date: 2025-11-05
// UVa Run Time: 0.400s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-9;

struct Point {
    int x, y, type;
};

struct Event {
    double angle;
    int value;
    bool operator<(const Event& other) const {
        return angle < other.angle;
    }
};

int main() {
    int N;
    while (cin >> N && N != 0) {
        vector<Point> points(N);
        for (int i = 0; i < N; i++) {
            cin >> points[i].x >> points[i].y >> points[i].type;
        }

        int ans = 1; // 至少有一个点溶解（线上点）
        
        for (int i = 0; i < N; i++) {
            vector<Event> events;
            int online = 1; // 点 i 自己总是在线上

            for (int j = 0; j < N; j++) {
                if (i == j) continue;
                
                int dx = points[j].x - points[i].x;
                int dy = points[j].y - points[i].y;
                
                // 检查是否共线（线上点）
                if (dx == 0 && dy == 0) {
                    online++;
                    continue;
                }
                
                double angle = atan2(dy, dx);
                // 确保角度在 [0, 2PI) 范围
                if (angle < 0) angle += 2 * PI;
                
                if (points[j].type == 0) {
                    // 亲水点：在水侧时贡献
                    events.push_back({angle, 1});
                } else {
                    // 疏水点：在丙酮侧时贡献（水侧的对侧）
                    double opposite = angle + PI;
                    if (opposite >= 2 * PI) opposite -= 2 * PI;
                    events.push_back({opposite, 1});
                }
            }
            
            // 如果没有其他点，只有线上点
            if (events.empty()) {
                ans = max(ans, online);
                continue;
            }
            
            // 排序事件
            sort(events.begin(), events.end());
            
            // 扩展事件数组用于循环扫描
            int m = events.size();
            for (int k = 0; k < m; k++) {
                events.push_back({events[k].angle + 2 * PI, events[k].value});
            }
            
            // 滑动窗口求最大区间和（区间长度 ≤ PI）
            int sum = 0;
            int left = 0;
            for (int right = 0; right < events.size(); right++) {
                sum += events[right].value;
                
                // 收缩左边界，保持区间长度 ≤ PI
                while (left <= right && events[right].angle - events[left].angle > PI + EPS) {
                    sum -= events[left].value;
                    left++;
                }
                
                ans = max(ans, sum + online);
            }
        }
        
        cout << ans << endl;
    }
    return 0;
}
