// Queuing at the Doctors
// UVa ID: 10588
// Verdict: Accepted
// Submission Date: 2026-01-07
// UVa Run Time: 0.350s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Patient {
    int id;
    int arriveTime;
    vector<int> offices;
    int currentPos;  // 在offices中的索引
    Patient(int i, int t, const vector<int>& off) : id(i), arriveTime(t), offices(off), currentPos(0) {}
};

struct Event {
    int time;
    int type;  // 0:到达事件，1:离开医生事件
    int patientId;
    int office;  // 对于type=1，表示离开的办公室
    bool operator>(const Event& other) const {
        if (time != other.time) return time > other.time;
        if (type != other.type) return type > other.type;
        return patientId > other.patientId;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int c;
    cin >> c;
    while (c--) {
        int n, m;
        cin >> n >> m;
        vector<Patient> patients;
        for (int i = 0; i < n; ++i) {
            int t, k;
            cin >> t >> k;
            vector<int> offices(k);
            for (int j = 0; j < k; ++j) cin >> offices[j];
            patients.emplace_back(i, t, offices);
        }
        // 每个办公室的队列，存储{到达时间, 病人ID}
        vector<vector<pair<int, int>>> queues(m + 1);
        // 医生是否空闲
        vector<bool> doctorAvailable(m + 1, true);
        // 事件优先队列
        priority_queue<Event, vector<Event>, greater<Event>> events;
        // 初始化所有到达事件
        for (int i = 0; i < n; ++i) events.push({patients[i].arriveTime, 0, i, -1});
        int finished = 0;
        int lastLeaveTime = 0;
        while (finished < n) {
            Event e = events.top();
            events.pop();
            int currentTime = e.time;
            // 处理当前时间的所有事件
            vector<Event> sameTimeEvents;
            sameTimeEvents.push_back(e);
            while (!events.empty() && events.top().time == currentTime) {
                sameTimeEvents.push_back(events.top());
                events.pop();
            }
            // 先处理到达事件
            for (const Event& ev : sameTimeEvents) {
                if (ev.type == 0) {  // 到达事件
                    Patient& p = patients[ev.patientId];
                    if (p.currentPos < (int)p.offices.size()) {
                        int office = p.offices[p.currentPos];
                        queues[office].push_back({currentTime, ev.patientId});
                    }
                }
            }
            // 再处理离开事件
            for (const Event& ev : sameTimeEvents) {
                if (ev.type == 1) {  // 离开医生事件
                    Patient& p = patients[ev.patientId];
                    p.currentPos++;
                    // 医生空闲
                    doctorAvailable[ev.office] = true;
                    if (p.currentPos >= (int)p.offices.size()) {
                        // 病人离开医院
                        finished++;
                        lastLeaveTime = currentTime;  // 在当前时间完成最后一次就诊
                    } else {
                        // 前往下一个办公室
                        int nextOffice = p.offices[p.currentPos];
                        queues[nextOffice].push_back({currentTime, ev.patientId});
                    }
                }
            }
            // 对每个办公室的队列排序：按到达时间，同时间按病人ID
            for (int office = 1; office <= m; ++office) {
                sort(queues[office].begin(), queues[office].end(), [](const pair<int, int>& a, const pair<int, int>& b) {
                    if (a.first != b.first) return a.first < b.first;
                    return a.second < b.second;
                });
            }
            // 医生开始处理病人
            for (int office = 1; office <= m; ++office) {
                if (doctorAvailable[office] && !queues[office].empty()) {
                    // 取出队列第一个病人
                    int patientId = queues[office][0].second;
                    queues[office].erase(queues[office].begin());
                    // 安排离开事件
                    events.push({currentTime + 1, 1, patientId, office});
                    doctorAvailable[office] = false;
                }
            }
        }
        
        // 病人离开发生在完成最后一次就诊后的下一个时间单位
        cout << lastLeaveTime << "\n";
    }
    
    return 0;
}
