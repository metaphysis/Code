// Process Scheduling
// UVa ID: 863
// Verdict: Accepted
// Submission Date: 2026-09-30
// UVa Run Time: 3.260s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int cpuNum, processNum;
vector<int> initialWork, remainWork, topoOrder, symClass;
vector<vector<int>> preList, nextList, currentPlan, bestPlan;
unordered_map<string, int> failedState;

bool readNonEmptyLine(istream &input, string &line) {
    while (getline(input, line))
        if (line.find_first_not_of(" \t\r") != string::npos) return true;
    return false;
}

string makeStateKey() {
    string key(processNum * sizeof(int), '\0');
    memcpy(&key[0], remainWork.data(), processNum * sizeof(int));
    return key;
}

bool isReady(int id, const vector<int> &remain) {
    if (remain[id] == 0) return false;
    for (int preId : preList[id])
        if (remain[preId] > 0) return false;
    return true;
}

long long getLowerBound(const vector<int> &remain, vector<int> &chain) {
    long long totalWork = 0, lowerBound = 0;
    chain.assign(processNum, 0);
    for (int index = processNum - 1; index >= 0; index--) {
        int id = topoOrder[index];
        if (remain[id] == 0) continue;
        int ownTime = (remain[id] + cpuNum - 1) / cpuNum, nextTime = 0;
        for (int nextId : nextList[id])
            nextTime = max(nextTime, chain[nextId]);
        chain[id] = ownTime + nextTime;
        lowerBound = max(lowerBound, (long long)chain[id]);
        totalWork += remain[id];
    }
    lowerBound = max(lowerBound, (totalWork + cpuNum - 1) / cpuNum);
    return lowerBound;
}

vector<vector<int>> buildGreedySchedule() {
    vector<int> remain = initialWork;
    vector<vector<int>> schedule;
    while (true) {
        vector<int> chain, readyList, allocation(processNum, 0), slot;
        if (getLowerBound(remain, chain) == 0) break;
        for (int id = 0; id < processNum; id++)
            if (isReady(id, remain)) readyList.push_back(id);
        sort(readyList.begin(), readyList.end(), [&](int a, int b) {
            if (chain[a] != chain[b]) return chain[a] > chain[b];
            if (remain[a] != remain[b]) return remain[a] < remain[b];
            return a < b;
        });
        int freeCpu = cpuNum;
        for (int id : readyList) {
            int useCpu = min(remain[id], freeCpu);
            allocation[id] = useCpu;
            freeCpu -= useCpu;
            if (freeCpu == 0) break;
        }
        for (int id = 0; id < processNum; id++) {
            remain[id] -= allocation[id];
            for (int count = 0; count < allocation[id]; count++)
                slot.push_back(id + 1);
        }
        schedule.push_back(slot);
    }
    return schedule;
}

bool searchSchedule(int leftTime);

bool enumerateAllocation(int index, int target, int leftTime, const vector<int> &readyList, const vector<int> &minAllocation, const vector<int> &suffixMin, const vector<int> &suffixCap, vector<int> &allocation) {
    int readyCount = readyList.size();
    if (index == readyCount) {
        if (target != 0) return false;
        vector<int> slot;
        for (int i = 0; i < readyCount; i++) {
            int id = readyList[i];
            remainWork[id] -= allocation[i];
            for (int count = 0; count < allocation[i]; count++)
                slot.push_back(id + 1);
        }
        sort(slot.begin(), slot.end());
        currentPlan.push_back(slot);
        if (searchSchedule(leftTime - 1)) return true;
        currentPlan.pop_back();
        for (int i = 0; i < readyCount; i++)
            remainWork[readyList[i]] += allocation[i];
        return false;
    }
    int id = readyList[index];
    int low = max(minAllocation[index], target - suffixCap[index + 1]);
    int high = min(remainWork[id], target - suffixMin[index + 1]);
    if (index > 0) {
        int preId = readyList[index - 1];
        if (symClass[id] == symClass[preId] && remainWork[id] == remainWork[preId])
            high = min(high, allocation[index - 1]);
    }
    if (low > high) return false;
    for (int useCpu = high; useCpu >= low; useCpu--) {
        allocation[index] = useCpu;
        if (enumerateAllocation(index + 1, target - useCpu, leftTime, readyList, minAllocation, suffixMin, suffixCap, allocation)) return true;
    }
    allocation[index] = 0;
    return false;
}

bool searchSchedule(int leftTime) {
    vector<int> chain;
    long long lowerBound = getLowerBound(remainWork, chain);
    if (lowerBound == 0) {
        bestPlan = currentPlan;
        return true;
    }
    if (leftTime == 0 || lowerBound > leftTime) return false;
    string key = makeStateKey();
    auto stateIt = failedState.find(key);
    if (stateIt != failedState.end() && stateIt->second >= leftTime) return false;
    failedState[key] = leftTime;
    vector<int> readyList;
    for (int id = 0; id < processNum; id++)
        if (isReady(id, remainWork)) readyList.push_back(id);
    sort(readyList.begin(), readyList.end(), [&](int a, int b) {
        if (chain[a] != chain[b]) return chain[a] > chain[b];
        if (remainWork[a] != remainWork[b]) return remainWork[a] < remainWork[b];
        if (symClass[a] != symClass[b]) return symClass[a] < symClass[b];
        return a < b;
    });
    int readyCount = readyList.size(), readyWork = 0;
    for (int id : readyList)
        readyWork += remainWork[id];
    int target = min(cpuNum, readyWork);
    vector<int> minAllocation(readyCount, 0), suffixMin(readyCount + 1, 0);
    vector<int> suffixCap(readyCount + 1, 0), allocation(readyCount, 0);
    for (int i = 0; i < readyCount; i++) {
        int id = readyList[i];
        int ownTime = (remainWork[id] + cpuNum - 1) / cpuNum;
        int tailTime = chain[id] - ownTime;
        int deadline = leftTime - tailTime;
        minAllocation[i] = max(0, remainWork[id] - cpuNum * (deadline - 1));
    }
    for (int i = readyCount - 1; i >= 0; i--) {
        suffixMin[i] = suffixMin[i + 1] + minAllocation[i];
        suffixCap[i] = suffixCap[i + 1] + remainWork[readyList[i]];
    }
    if (suffixMin[0] > target) return false;
    return enumerateAllocation(0, target, leftTime, readyList, minAllocation, suffixMin, suffixCap, allocation);
}

void buildTopology() {
    vector<int> degree(processNum, 0);
    queue<int> processQueue;
    topoOrder.clear();
    for (int id = 0; id < processNum; id++) {
        degree[id] = preList[id].size();
        if (degree[id] == 0) processQueue.push(id);
    }
    while (!processQueue.empty()) {
        int id = processQueue.front();
        processQueue.pop();
        topoOrder.push_back(id);
        for (int nextId : nextList[id]) {
            degree[nextId]--;
            if (degree[nextId] == 0) processQueue.push(nextId);
        }
    }
}

void buildSymmetryClass() {
    map<vector<int>, int> classMap;
    symClass.resize(processNum);
    int classCount = 0;
    for (int id = 0; id < processNum; id++) {
        vector<int> next = nextList[id];
        sort(next.begin(), next.end());
        auto classIt = classMap.find(next);
        if (classIt == classMap.end()) {
            classMap[next] = classCount;
            symClass[id] = classCount;
            classCount++;
        } else {
            symClass[id] = classIt->second;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    if (!readNonEmptyLine(cin, line)) return 0;
    int caseNum = stoi(line);
    for (int caseId = 0; caseId < caseNum; caseId++) {
        readNonEmptyLine(cin, line);
        stringstream headerStream(line);
        headerStream >> cpuNum >> processNum;
        initialWork.assign(processNum, 0);
        preList.assign(processNum, {});
        nextList.assign(processNum, {});
        for (int id = 0; id < processNum; id++) {
            readNonEmptyLine(cin, line);
            stringstream processStream(line);
            processStream >> initialWork[id];
            int preId;
            while (processStream >> preId) {
                preId--;
                preList[id].push_back(preId);
                nextList[preId].push_back(id);
            }
        }
        buildTopology();
        buildSymmetryClass();
        vector<vector<int>> greedyPlan = buildGreedySchedule();
        vector<int> initialChain;
        int lowerBound = getLowerBound(initialWork, initialChain);
        int upperBound = greedyPlan.size();
        bestPlan = greedyPlan;
        for (int depth = lowerBound; depth < upperBound; depth++) {
            remainWork = initialWork;
            currentPlan.clear();
            failedState.clear();
            if (searchSchedule(depth)) break;
        }
        if (caseId > 0) cout << '\n';
        for (const vector<int> &slot : bestPlan) {
            for (int i = 0; i < (int)slot.size(); i++) {
                if (i > 0) cout << ' ';
                cout << setw(2) << slot[i];
            }
            cout << '\n';
        }
    }
    return 0;
}
