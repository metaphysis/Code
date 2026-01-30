// Trains
// UVa ID: 10362
// Verdict: Accepted
// Submission Date: 2026-01-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MINUTES_PER_DAY = 1440;  // 每天的分钟数
const int INF = 0x3f3f3f3f;        // 无穷大值

// 将时间字符串 "hh:mm" 转换为分钟数
int toMinutes(const string& s) {
    int p = s.find(':');
    int hour = stoi(s.substr(0, p));
    int minute = stoi(s.substr(p + 1));
    return hour * 60 + minute;
}

// 将分钟数格式化为 "hh:mm"
string fmtTime(int minutes) {
    char buf[16];
    sprintf(buf, "%02d:%02d", minutes / 60, minutes % 60);
    return string(buf);
}

// 将分钟数格式化为旅行时间 "h:mm"
string fmtTravel(int minutes) {
    char buf[16];
    sprintf(buf, "%d:%02d", minutes / 60, minutes % 60);
    return string(buf);
}

int main() {
    int N; cin >> N;  // 测试用例数量
    bool firstCase = true;  // 标记是否为第一个测试用例
    
    while (N--) {
        // 输出用例间的空行（第一个除外）
        if (!firstCase) cout << '\n';
        firstCase = false;
        
        int T; cin >> T;  // 火车路线数量
        
        // 车站映射：名称 -> ID
        map<string, int> stationId;
        vector<string> stationNames;
        
        // 存储所有火车边
        struct TrainEdge { 
            int fromStation;   // 起点站ID
            int toStation;     // 终点站ID
            int departTime;    // 出发时间（0-1439）
            int travelTime;    // 旅行时间（分钟）
        };
        vector<TrainEdge> edges;
        
        // 读取所有路线
        for (int r = 0; r < T; r++) {
            int S; string s; 
            cin >> S >> s;  // 车站数量和路线出发时间
            int routeStartTime = toMinutes(s);  // 转换为分钟
            
            // 存储路线信息：(车站ID, 到达时间偏移)
            vector<pair<int, int>> routeInfo;
            
            string stationName; cin >> stationName;
            // 获取或创建车站ID
            if (!stationId.count(stationName)) {
                stationId[stationName] = stationNames.size();
                stationNames.push_back(stationName);
            }
            int station = stationId[stationName];
            routeInfo.push_back({station, 0});  // 第一个车站时间偏移为0
            
            int totalTime = 0;  // 累计旅行时间
            for (int i = 1; i < S; i++) {
                string nextStation;
                cin >> s >> nextStation;  // 旅行时间和下一站名
                
                int travelTime = toMinutes(s);  // 转换为分钟
                totalTime += travelTime;
                
                if (!stationId.count(nextStation)) {
                    stationId[nextStation] = stationNames.size();
                    stationNames.push_back(nextStation);
                }
                int nextId = stationId[nextStation];
                routeInfo.push_back({nextId, totalTime});
            }
            
            // 为相邻车站创建火车边
            for (int i = 0; i < S - 1; i++) {
                TrainEdge edge;
                edge.fromStation = routeInfo[i].first;
                edge.toStation = routeInfo[i + 1].first;
                // 出发时间 = 路线出发时间 + 当前车站时间偏移（模1440）
                edge.departTime = (routeStartTime + routeInfo[i].second) % MINUTES_PER_DAY;
                // 旅行时间 = 下一站时间偏移 - 当前站时间偏移
                edge.travelTime = routeInfo[i + 1].second - routeInfo[i].second;
                edges.push_back(edge);
            }
        }
        
        // 读取起点和终点
        string startName, endName; 
        cin >> startName >> endName;
        int startId = stationId[startName];
        int endId = stationId[endName];
        
        // 动态规划数组：travel[station][time] = 从起点到该车站在该时间所需的最短时间
        vector<vector<int>> travel(stationNames.size(), 
                                  vector<int>(MINUTES_PER_DAY, INF));
        
        // 初始化：起点站在所有时间都已经到达（时间为0）
        for (int t = 0; t < MINUTES_PER_DAY; t++) 
            travel[startId][t] = 0;
        
        // 动态规划：不断松弛直到没有更新
        bool updated = true;
        while (updated) {
            updated = false;
            
            for (const auto& edge : edges) {
                int from = edge.fromStation;
                int to = edge.toStation;
                int depart = edge.departTime;
                int travelTime = edge.travelTime;
                int arrive = (depart + travelTime) % MINUTES_PER_DAY;
                
                // 如果可以在depart时间从from站出发
                if (travel[from][depart] < INF) {
                    int newArrivalTime = travel[from][depart] + travelTime;
                    
                    // 更新到达时间及之后的所有时间
                    int currentTime = arrive;
                    int currentArrival = newArrivalTime;
                    
                    // 只要当前时间点的值大于新的到达时间，就更新
                    while (travel[to][currentTime] > currentArrival) {
                        updated = true;
                        travel[to][currentTime] = currentArrival;
                        
                        // 移动到下一个时间点（可以在车站等待）
                        currentTime = (currentTime + 1) % MINUTES_PER_DAY;
                        currentArrival++;
                    }
                }
            }
        }
        
        // 收集所有可能的连接
        vector<pair<int, int>> connections;  // (出发时间, 旅行时间)
        
        for (int arrivalTime = 0; arrivalTime < MINUTES_PER_DAY; arrivalTime++) {
            if (travel[endId][arrivalTime] < INF) {
                int travelTime = travel[endId][arrivalTime];
                // 出发时间 = 到达时间 - 旅行时间（模1440）
                int departTime = (arrivalTime - travelTime) % MINUTES_PER_DAY;
                if (departTime < 0) departTime += MINUTES_PER_DAY;
                
                connections.push_back({departTime, travelTime});
            }
        }
        
        // 按出发时间排序
        sort(connections.begin(), connections.end());
        
        // 输出结果：过滤帕累托前沿
        vector<pair<int, int>> result;
        for (size_t i = 0; i < connections.size(); i++) {
            // 相同出发时间只保留第一个（旅行时间最短的）
            if (i == 0 || connections[i].first != connections[i - 1].first) {
                result.push_back(connections[i]);
            }
        }
        
        // 输出最终结果
        for (auto r : result) {
            cout << fmtTime(r.first) << ' ' << fmtTravel(r.second) << '\n';
        }
    }
    
    return 0;
}
