// Queue and A
// UVa ID: 822
// Verdict: Accepted
// Submission Date: 2025-11-06
// UVa Run Time: 0.020s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Staff {
    int id;
    int availableTime;
    vector<int> topics;
};

bool compareStaff(const Staff& a, const Staff& b) {
    if (a.availableTime != b.availableTime) {
        return a.availableTime < b.availableTime;
    }
    return a.id < b.id;
}

int main() {
    int scenarioNum = 1;
    int numTopics;
    
    while (cin >> numTopics && numTopics != 0) {
        vector<vector<int> > allRequests;
        
        // 生成所有请求
        for (int i = 0; i < numTopics; i++) {
            int topicId, numRequests, firstTime, serviceTime, interval;
            cin >> topicId >> numRequests >> firstTime >> serviceTime >> interval;
            
            for (int j = 0; j < numRequests; j++) {
                vector<int> request;
                request.push_back(topicId);
                request.push_back(firstTime + j * interval);
                request.push_back(serviceTime);
                allRequests.push_back(request);
            }
        }
        
        // 按到达时间排序请求
        sort(allRequests.begin(), allRequests.end(), 
             [](const vector<int>& a, const vector<int>& b) {
                 return a[1] < b[1];
             });
        
        int numStaff;
        cin >> numStaff;
        vector<Staff> staff(numStaff);
        
        // 初始化员工
        for (int i = 0; i < numStaff; i++) {
            int numTopics;
            cin >> staff[i].id >> numTopics;
            staff[i].availableTime = 0;
            staff[i].topics.resize(numTopics);
            for (int j = 0; j < numTopics; j++) {
                cin >> staff[i].topics[j];
            }
        }
        
        // 处理每个请求
        for (size_t i = 0; i < allRequests.size(); i++) {
            int topicId = allRequests[i][0];
            int arrivalTime = allRequests[i][1];
            int serviceTime = allRequests[i][2];
            
            // 排序员工
            sort(staff.begin(), staff.end(), compareStaff);
            
            // 分配请求
            for (size_t j = 0; j < staff.size(); j++) {
                bool canHandle = false;
                for (size_t k = 0; k < staff[j].topics.size(); k++) {
                    if (staff[j].topics[k] == topicId) {
                        canHandle = true;
                        break;
                    }
                }
                
                if (canHandle) {
                    staff[j].availableTime = max(staff[j].availableTime, arrivalTime) + serviceTime;
                    break;
                }
            }
        }
        
        // 计算最大完成时间
        int maxTime = 0;
        for (size_t i = 0; i < staff.size(); i++) {
            if (staff[i].availableTime > maxTime) {
                maxTime = staff[i].availableTime;
            }
        }
        
        cout << "Scenario " << scenarioNum++ 
             << ": All requests are serviced within " << maxTime << " minutes." << endl;
    }
    
    return 0;
}
