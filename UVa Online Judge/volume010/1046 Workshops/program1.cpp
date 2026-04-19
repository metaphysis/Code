// Workshops
// UVa ID: 1046
// Verdict: Accepted
// Submission Date: 2026-02-27
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int trial = 0;
    int w, r;
    
    while (cin >> w, w) {
        trial++;
        
        // 存储工作坊：first = 人数, second = 时长
        vector<pair<int, int>> workshops(w + 1);
        for (int i = 1; i <= w; i++)
            cin >> workshops[i].first >> workshops[i].second;
        
        cin >> r;
        // 存储房间：first = 可用时间, second = 容量
        vector<pair<int, int>> rooms(r + 1);
        for (int i = 1; i <= r; i++) {
            int seats, hh, mm;
            char colon;
            cin >> seats >> hh >> colon >> mm;
            rooms[i].first = (hh - 14) * 60 + mm;  // 可用时间
            rooms[i].second = seats;                // 容量
        }
        
        // 关键步骤1：工作坊按人数升序排序
        sort(workshops.begin() + 1, workshops.end());
        // 关键步骤2：房间按可用时间升序排序
        sort(rooms.begin() + 1, rooms.end());
        
        vector<bool> used(w + 1, false);
        int matched = 0;
        int totalParticipants = 0;
        
        // 关键步骤3：对每个房间，从大到小找可行的工作坊
        for (int i = 1; i <= r; i++) {
            int roomTime = rooms[i].first;
            int roomCap = rooms[i].second;
            
            // 从人数最大的工作坊开始找
            for (int j = w; j >= 1; j--) {
                if (!used[j] && 
                    workshops[j].first <= roomCap &&  // 人数够
                    workshops[j].second <= roomTime) { // 时间够
                    used[j] = true;
                    matched++;
                    totalParticipants += workshops[j].first;
                    break;
                }
            }
        }
        
        // 计算总人数
        int sumAll = 0;
        for (int i = 1; i <= w; i++)
            sumAll += workshops[i].first;
        
        int tentWorkshops = w - matched;
        int tentParticipants = sumAll - totalParticipants;
        
        cout << "Trial " << trial << ": " << tentWorkshops << " " << tentParticipants << "\n\n";
    }
    
    return 0;
}
