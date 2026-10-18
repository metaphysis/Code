// Machine Repair Simulation
// UVa ID: 749
// Verdict: Accepted
// Submission Date: 2026-10-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

/*
这道题目我尝试了很多次，都无法通过，最终发现原来是输入数据格式的问题，题目描述中提到（无意中看到这一句才注意）：

The input file is composed of three parts each separated by a header record.

实际上，在线测试数据的输入格式类似这样：

Machine running times (10 five column fields per record)  
7.0 4.5 13.0 10.5 3.0 12.0 8.2 4.8 8.7 12.0  
7.9 2.0 7.1 1.7 5.6 10.5 8.5 7.4 4.2 12.5  
14.1 3.3 6.3 4.5 4.0 6.6 2.7 9.7 1.0 4.0  
7.9 2.7 10.6 13.8 1.1 14.2 12.6 10.2 14.2 10.9  
4.3 12.8 11.5 9.2 13.8 5.4 15.0 3.9 11.8 6.8  
Machine repair times (10 five column fields per record)  
9.5 2.5 4.5 12.0 5.7 1.5 2.1 8.5 2.4 7.6  
3.7 8.1 7.4 9.8 7.5 2.9 2.9 8.7 8.1 6.6  
5.3 6.7 4.6 2.0 4.3 5.9 3.4 5.5 3.2 5.5  
4.8 6.9 2.9 6.5 2.4 6.0 6.3 1.0 5.9 3.1  
7.8 8.5 2.6 1.7 4.7 8.0 2.8 6.3 3.6 2.2  
Cases (2 five column fields per record)  
20.0 1  
20.0 3  
0.0 0

正确处理输入就可以通过了。
*/
#include <bits/stdc++.h>
using namespace std;

struct Result {
    double machUtil, repUtil;
};

vector<double> readSectionValues(istream &in, int need) {
    vector<double> values;
    string line;
    getline(in, line);
    while (values.size() < need && getline(in, line)) {
        stringstream ss(line);
        double value;
        while (ss >> value)
            values.push_back(value);
    }
    return values;
}

void startRepair(double now, int machine, bool &repairBusy, double &repairEnd, int &repairPos, const vector<double> &repairTimes) {
    repairBusy = true;
    repairEnd = now + repairTimes[repairPos++];
}

Result simulate(double horizon, int machineCount, const vector<double> &runTimes, const vector<double> &repairTimes) {
    const double eps = 1e-9;
    vector<double> failTime(machineCount);
    vector<int> state(machineCount, 0);
    queue<int> repairQueue;
    double now = 0.0, workArea = 0.0, repairArea = 0.0, repairEnd = 0.0;
    int runPos = machineCount, repairPos = 0, workingCount = machineCount;
    bool repairBusy = false;
    for (int i = 0; i < machineCount; i++)
        failTime[i] = runTimes[i];
    while (now < horizon - eps) {
        double nextFail = numeric_limits<double>::infinity();
        for (int i = 0; i < machineCount; i++)
            if (state[i] == 0)
                nextFail = min(nextFail, failTime[i]);
        double nextRepair = repairBusy ? repairEnd : numeric_limits<double>::infinity();
        double eventTime = min(horizon, min(nextFail, nextRepair));
        workArea += workingCount * (eventTime - now);
        repairArea += (repairBusy ? 1.0 : 0.0) * (eventTime - now);
        now = eventTime;
        if (now >= horizon - eps)
            break;
        if (repairBusy && repairEnd <= now + eps) {
            int machine = -1;
            for (int i = 0; i < machineCount; i++)
                if (state[i] == 2) {
                    machine = i;
                    break;
                }
            if (machine != -1) {
                state[machine] = 0;
                workingCount++;
                failTime[machine] = now + runTimes[runPos++];
            }
            repairBusy = false;
            if (!repairQueue.empty()) {
                machine = repairQueue.front();
                repairQueue.pop();
                state[machine] = 2;
                startRepair(now, machine, repairBusy, repairEnd, repairPos, repairTimes);
            }
        }
        for (int i = 0; i < machineCount; i++) {
            if (state[i] == 0 && failTime[i] <= now + eps) {
                state[i] = 1;
                workingCount--;
                if (!repairBusy) {
                    state[i] = 2;
                    startRepair(now, i, repairBusy, repairEnd, repairPos, repairTimes);
                } else
                    repairQueue.push(i);
            }
        }
    }
    Result result;
    result.machUtil = workArea / (machineCount * horizon);
    result.repUtil = repairArea / horizon;
    return result;
}

string formatValue(double value) {
    ostringstream out;
    out << fixed << setprecision(3) << value;
    string result = out.str();
    if (result[0] == '0')
        result.erase(result.begin());
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<double> runTimes = readSectionValues(cin, 50);
    vector<double> repairTimes = readSectionValues(cin, 50);
    string line;
    getline(cin, line);
    cout << "       No of     Utilization\n";
    cout << "Case Machines Machine Repairman\n\n";
    int caseNo = 1;
    while (getline(cin, line)) {
        if (line.empty())
            continue;
        stringstream ss(line);
        double horizon;
        int machineCount;
        if (!(ss >> horizon >> machineCount))
            continue;
        if (horizon == 0.0 && machineCount == 0)
            break;
        Result result = simulate(horizon, machineCount, runTimes, repairTimes);
        cout << setw(2) << caseNo;
        cout << setw(8) << machineCount;
        cout << setw(11) << formatValue(result.machUtil);
        cout << setw(7) << formatValue(result.repUtil) << '\n';
        caseNo++;
    }
    return 0;
}
