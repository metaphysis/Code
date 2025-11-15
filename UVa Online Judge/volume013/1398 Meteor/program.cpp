// Meteor
// UVa ID: 1398
// Verdict: Accepted
// Submission Date: 2025-11-01
// UVa Run Time: 0.030s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net


#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9; // 精度控制

// 事件结构体
struct Event {
    double time; // 事件发生时间
    int type;    // 事件类型：+1 表示进入，-1 表示离开
    
    Event(double t, int tp) : time(t), type(tp) {}
    
    // 排序规则：时间相同则离开事件优先
    bool operator<(const Event& other) const {
        if (fabs(time - other.time) < EPS) return type < other.type;
        return time < other.time;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int testCaseCount;
    cin >> testCaseCount;
    
    while (testCaseCount--) {
        int width, height;
        cin >> width >> height;
        int meteorCount;
        cin >> meteorCount;
        
        vector<Event> events;
        
        for (int i = 0; i < meteorCount; ++i) {
            int startX, startY, velX, velY;
            cin >> startX >> startY >> velX >> velY;
            
            // 计算 X 方向的时间区间
            double xStartTime, xEndTime;
            if (velX > 0) {
                xStartTime = max(0.0, (-startX + EPS) / velX);
                xEndTime = (width - startX - EPS) / velX;
            } else if (velX < 0) {
                xStartTime = max(0.0, (width - startX + EPS) / velX);
                xEndTime = (-startX - EPS) / velX;
            } else { // velX == 0
                if (startX > 0 && startX < width) {
                    xStartTime = 0.0;
                    xEndTime = 1e20; // 表示无穷大
                } else {
                    xStartTime = 1.0;
                    xEndTime = 0.0; // 空区间
                }
            }
            
            // 计算 Y 方向的时间区间
            double yStartTime, yEndTime;
            if (velY > 0) {
                yStartTime = max(0.0, (-startY + EPS) / velY);
                yEndTime = (height - startY - EPS) / velY;
            } else if (velY < 0) {
                yStartTime = max(0.0, (height - startY + EPS) / velY);
                yEndTime = (-startY - EPS) / velY;
            } else { // velY == 0
                if (startY > 0 && startY < height) {
                    yStartTime = 0.0;
                    yEndTime = 1e20; // 表示无穷大
                } else {
                    yStartTime = 1.0;
                    yEndTime = 0.0; // 空区间
                }
            }
            
            // 取 X 和 Y 方向的交集
            double startTime = max(xStartTime, yStartTime);
            double endTime = min(xEndTime, yEndTime);
            
            // 如果区间有效，创建事件
            if (startTime < endTime - EPS) {
                events.emplace_back(startTime, 1);   // 进入事件
                events.emplace_back(endTime, -1);    // 离开事件
            }
        }
        
        // 按时间排序事件
        sort(events.begin(), events.end());
        
        int currentCount = 0;
        int maxCount = 0;
        
        // 扫描事件
        for (const auto& event : events) {
            currentCount += event.type;
            if (currentCount > maxCount) {
                maxCount = currentCount;
            }
        }
        
        cout << maxCount << "\n";
    }
    
    return 0;
}
