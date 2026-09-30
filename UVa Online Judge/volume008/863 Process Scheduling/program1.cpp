// Process Scheduling
// UVa ID: 863
// Verdict: Accepted
// Submission Date: 2026-09-30
// UVa Run Time: 2.730s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct Slot {
    vector<int> process;
};

struct SearchFrame {
    int readyCount = 0;
    vector<int> ready, allocation, minAllocation, suffixMin, suffixCap;

    void resize(int processCount) {
        ready.assign(processCount, 0);
        allocation.assign(processCount, 0);
        minAllocation.assign(processCount, 0);
        suffixMin.assign(processCount + 1, 0);
        suffixCap.assign(processCount + 1, 0);
        readyCount = 0;
    }
};

int cpuNum, processNum;
vector<int> initialWork, remainWork;
vector<vector<int>> preList, nextList;
vector<int> topoOrder, symmetryClass;
vector<long long> chainWork;
vector<SearchFrame> frames;
vector<Slot> currentPlan, bestPlan;
unordered_map<string, int> failedState;

bool readNonEmptyLine(string &line) {
    while (getline(cin, line))
        if (line.find_first_not_of(" \t\r\n") != string::npos) return true;
    return false;
}

bool isReady(int id) {
    if (remainWork[id] == 0) return false;
    for (int predecessor : preList[id])
        if (remainWork[predecessor] > 0) return false;
    return true;
}

int getLowerBound() {
    long long totalWork = 0, lowerBound = 0;
    for (int index = static_cast<int>(topoOrder.size()) - 1; index >= 0; --index) {
        int id = topoOrder[index];
        if (remainWork[id] == 0) {
            chainWork[id] = 0;
            continue;
        }
        long long ownTime = (static_cast<long long>(remainWork[id]) + cpuNum - 1) / cpuNum;
        long long nextTime = 0;
        for (int nextId : nextList[id])
            nextTime = max(nextTime, chainWork[nextId]);
        chainWork[id] = ownTime + nextTime;
        lowerBound = max(lowerBound, chainWork[id]);
        totalWork += remainWork[id];
    }
    long long workBound = (totalWork + cpuNum - 1) / cpuNum;
    lowerBound = max(lowerBound, workBound);
    return static_cast<int>(lowerBound);
}

bool readyCompare(int a, int b) {
    if (chainWork[a] != chainWork[b]) return chainWork[a] > chainWork[b];
    if (remainWork[a] != remainWork[b]) return remainWork[a] < remainWork[b];
    if (symmetryClass[a] != symmetryClass[b]) return symmetryClass[a] < symmetryClass[b];
    return a < b;
}

vector<Slot> buildGreedySchedule() {
    vector<int> greedyRemain = initialWork;
    vector<Slot> schedule;
    while (true) {
        remainWork = greedyRemain;
        if (getLowerBound() == 0) break;
        vector<int> readyList;
        readyList.reserve(processNum);
        for (int id = 0; id < processNum; ++id)
            if (isReady(id)) readyList.push_back(id);
        sort(readyList.begin(), readyList.end(), readyCompare);
        vector<int> allocation(processNum, 0);
        int freeCpu = cpuNum;
        for (int id : readyList) {
            if (freeCpu == 0) break;
            int useCpu = min(remainWork[id], freeCpu);
            allocation[id] = useCpu;
            freeCpu -= useCpu;
        }
        Slot slot;
        slot.process.reserve(cpuNum);
        for (int id = 0; id < processNum; ++id) {
            greedyRemain[id] -= allocation[id];
            for (int count = 0; count < allocation[id]; ++count)
                slot.process.push_back(id + 1);
        }
        schedule.push_back(move(slot));
    }
    remainWork = initialWork;
    return schedule;
}

string makeStateKey() {
    string key;
    key.resize(processNum * sizeof(int));
    for (int i = 0; i < processNum; ++i) {
        int value = remainWork[i];
        for (int byte = 0; byte < static_cast<int>(sizeof(int)); ++byte)
            key[i * sizeof(int) + byte] = static_cast<char>((value >> (byte * 8)) & 255);
    }
    return key;
}

bool searchSchedule(int leftTime);

bool enumerateAllocation(int index, int target, int leftTime) {
    SearchFrame &frame = frames[currentPlan.size()];
    if (index == frame.readyCount) {
        if (target != 0) return false;
        Slot slot;
        slot.process.reserve(cpuNum);
        for (int i = 0; i < frame.readyCount; ++i) {
            int id = frame.ready[i], useCpu = frame.allocation[i];
            remainWork[id] -= useCpu;
            for (int count = 0; count < useCpu; ++count) slot.process.push_back(id + 1);
        }
        currentPlan.push_back(move(slot));
        if (searchSchedule(leftTime - 1)) return true;
        currentPlan.pop_back();
        for (int i = 0; i < frame.readyCount; ++i) remainWork[frame.ready[i]] += frame.allocation[i];
        return false;
    }
    int id = frame.ready[index], low = max(frame.minAllocation[index], target - frame.suffixCap[index + 1]), high = min(remainWork[id], target - frame.suffixMin[index + 1]);
    if (index > 0) {
        int previousId = frame.ready[index - 1];
        if (symmetryClass[id] == symmetryClass[previousId] && remainWork[id] == remainWork[previousId]) high = min(high, frame.allocation[index - 1]);
    }
    if (low > high) return false;
    for (int useCpu = high; useCpu >= low; --useCpu) {
        frame.allocation[index] = useCpu;
        if (enumerateAllocation(index + 1, target - useCpu, leftTime)) return true;
    }
    frame.allocation[index] = 0;
    return false;
}

bool searchSchedule(int leftTime) {
    int lowerBound = getLowerBound();
    if (lowerBound == 0) {
        bestPlan = currentPlan;
        return true;
    }
    if (leftTime == 0 || lowerBound > leftTime) return false;
    string stateKey = makeStateKey();
    auto found = failedState.find(stateKey);
    if (found != failedState.end() && found->second >= leftTime) return false;
    auto inserted = failedState.emplace(stateKey, leftTime);
    if (!inserted.second && inserted.first->second < leftTime) inserted.first->second = leftTime;
    SearchFrame &frame = frames[currentPlan.size()];
    frame.readyCount = 0;
    for (int id = 0; id < processNum; ++id)
        if (isReady(id)) frame.ready[frame.readyCount++] = id;
    sort(frame.ready.begin(), frame.ready.begin() + frame.readyCount, readyCompare);
    int readyWork = 0;
    for (int i = 0; i < frame.readyCount; ++i) readyWork += remainWork[frame.ready[i]];
    int target = min(cpuNum, readyWork);
    frame.suffixMin[frame.readyCount] = 0;
    frame.suffixCap[frame.readyCount] = 0;
    for (int i = frame.readyCount - 1; i >= 0; --i) {
        int id = frame.ready[i];
        long long ownTime = (static_cast<long long>(remainWork[id]) + cpuNum - 1) / cpuNum;
        long long tailTime = chainWork[id] - ownTime, deadline = static_cast<long long>(leftTime) - tailTime;
        long long need = static_cast<long long>(remainWork[id]) - static_cast<long long>(cpuNum) * (deadline - 1);
        need = max(0LL, need);
        need = min(need, static_cast<long long>(remainWork[id]));
        frame.minAllocation[i] = static_cast<int>(need);
        frame.suffixMin[i] = frame.suffixMin[i + 1] + frame.minAllocation[i];
        frame.suffixCap[i] = frame.suffixCap[i + 1] + remainWork[id];
    }
    if (frame.suffixMin[0] > target) return false;
    return enumerateAllocation(0, target, leftTime);
}

void buildTopology() {
    vector<int> degree(processNum, 0);
    queue<int> processQueue;
    topoOrder.clear();
    topoOrder.reserve(processNum);
    for (int id = 0; id < processNum; ++id) {
        degree[id] = static_cast<int>(preList[id].size());
        if (degree[id] == 0) processQueue.push(id);
    }
    while (!processQueue.empty()) {
        int id = processQueue.front();
        processQueue.pop();
        topoOrder.push_back(id);
        for (int nextId : nextList[id]) {
            --degree[nextId];
            if (degree[nextId] == 0) processQueue.push(nextId);
        }
    }
}

void buildSymmetryClass() {
    map<vector<int>, int> classMap;
    symmetryClass.assign(processNum, 0);
    int classCount = 0;
    for (int id = 0; id < processNum; ++id) {
        vector<int> successors = nextList[id];
        sort(successors.begin(), successors.end());
        auto found = classMap.find(successors);
        if (found == classMap.end()) {
            classMap.emplace(successors, classCount);
            symmetryClass[id] = classCount;
            ++classCount;
        } else {
            symmetryClass[id] = found->second;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    if (!readNonEmptyLine(line)) return 0;
    int caseCount = stoi(line);
    for (int caseId = 0; caseId < caseCount; ++caseId) {
        if (!readNonEmptyLine(line)) return 0;
        stringstream headerStream(line);
        headerStream >> cpuNum >> processNum;
        initialWork.assign(processNum, 0);
        remainWork.assign(processNum, 0);
        preList.assign(processNum, {});
        nextList.assign(processNum, {});
        chainWork.assign(processNum, 0);
        symmetryClass.assign(processNum, 0);
        for (int id = 0; id < processNum; ++id) {
            if (!readNonEmptyLine(line)) return 0;
            stringstream processStream(line);
            processStream >> initialWork[id];
            int predecessor;
            while (processStream >> predecessor) {
                --predecessor;
                if (predecessor < 0 || predecessor >= processNum) continue;
                preList[id].push_back(predecessor);
                nextList[predecessor].push_back(id);
            }
        }
        buildTopology();
        buildSymmetryClass();
        vector<Slot> greedyPlan = buildGreedySchedule();
        int lowerBound = getLowerBound(), upperBound = static_cast<int>(greedyPlan.size());
        bestPlan = greedyPlan;
        for (int depth = lowerBound; depth < upperBound; ++depth) {
            remainWork = initialWork;
            currentPlan.clear();
            currentPlan.reserve(depth);
            frames.assign(depth + 1, SearchFrame());
            for (SearchFrame &frame : frames) frame.resize(processNum);
            failedState.clear();
            failedState.reserve(200000);
            if (searchSchedule(depth)) break;
        }
        if (caseId > 0) cout << '\n';
        for (const Slot &slot : bestPlan) {
            for (int i = 0; i < static_cast<int>(slot.process.size()); ++i) {
                if (i > 0) cout << ' ';
                cout << setw(2) << slot.process[i];
            }
            cout << '\n';
        }
    }
    return 0;
}
