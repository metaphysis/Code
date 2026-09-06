#include <bits/stdc++.h>
using namespace std;

struct Group {
    vector<int> leftIds, rightIds;
    int leftPos = 0, rightPos = 0;
    int prevId = -1, nextId = -1;
    bool active = true;
};

struct Candidate {
    int diff, sum, leftId, rightId;
    bool operator < (const Candidate &other) const {
        if (diff != other.diff) return diff < other.diff;
        if (sum != other.sum) return sum > other.sum;
        if (leftId != other.leftId) return leftId < other.leftId;
        return rightId < other.rightId;
    }
};

class RobotHands {
private:
    int n, groupCount;
    vector<int> leftVal, rightVal, leftGroup, rightGroup, values;
    vector<Group> groups;
    set<Candidate> candidates;

    bool isMixed(int groupId) {
        Group &group = groups[groupId];
        return group.leftPos < static_cast<int>(group.leftIds.size()) && group.rightPos < static_cast<int>(group.rightIds.size());
    }

    bool isLeftOnly(int groupId) {
        Group &group = groups[groupId];
        return group.leftPos < static_cast<int>(group.leftIds.size()) && group.rightPos == static_cast<int>(group.rightIds.size());
    }

    bool isRightOnly(int groupId) {
        Group &group = groups[groupId];
        return group.leftPos == static_cast<int>(group.leftIds.size()) && group.rightPos < static_cast<int>(group.rightIds.size());
    }

    bool canEdge(int firstId, int secondId) {
        if (!groups[firstId].active || !groups[secondId].active) return false;
        if (isLeftOnly(firstId) && isRightOnly(secondId)) return true;
        if (isRightOnly(firstId) && isLeftOnly(secondId)) return true;
        return false;
    }

    Candidate makeInner(int groupId) {
        Group &group = groups[groupId];
        int leftId = group.leftIds[group.leftPos];
        int rightId = group.rightIds[group.rightPos];
        return {0, values[groupId] * 2, leftId, rightId};
    }

    Candidate makeEdge(int firstId, int secondId) {
        Group &firstGroup = groups[firstId];
        Group &secondGroup = groups[secondId];
        int leftId, rightId;
        if (isLeftOnly(firstId)) {
            leftId = firstGroup.leftIds[firstGroup.leftPos];
            rightId = secondGroup.rightIds[secondGroup.rightPos];
        } else {
            leftId = secondGroup.leftIds[secondGroup.leftPos];
            rightId = firstGroup.rightIds[firstGroup.rightPos];
        }
        return {values[secondId] - values[firstId], values[firstId] + values[secondId], leftId, rightId};
    }

    void clearNode(int groupId) {
        if (!groups[groupId].active) return;
        if (isMixed(groupId)) candidates.erase(makeInner(groupId));
        int prevId = groups[groupId].prevId, nextId = groups[groupId].nextId;
        if (prevId != -1 && canEdge(prevId, groupId)) candidates.erase(makeEdge(prevId, groupId));
        if (nextId != -1 && canEdge(groupId, nextId)) candidates.erase(makeEdge(groupId, nextId));
    }

    void addNode(int groupId) {
        if (!groups[groupId].active) return;
        if (isMixed(groupId)) candidates.insert(makeInner(groupId));
        int prevId = groups[groupId].prevId, nextId = groups[groupId].nextId;
        if (prevId != -1 && canEdge(prevId, groupId)) candidates.insert(makeEdge(prevId, groupId));
        if (nextId != -1 && canEdge(groupId, nextId)) candidates.insert(makeEdge(groupId, nextId));
    }

    void collectAround(int groupId, set<int> &touched) {
        if (groupId == -1 || !groups[groupId].active) return;
        touched.insert(groupId);
        if (groups[groupId].prevId != -1) touched.insert(groups[groupId].prevId);
        if (groups[groupId].nextId != -1) touched.insert(groups[groupId].nextId);
    }

    void removeGroup(int groupId) {
        int prevId = groups[groupId].prevId, nextId = groups[groupId].nextId;
        if (prevId != -1) groups[prevId].nextId = nextId;
        if (nextId != -1) groups[nextId].prevId = prevId;
        groups[groupId].active = false;
    }

    void removePair(int leftId, int rightId) {
        int leftGroupId = leftGroup[leftId], rightGroupId = rightGroup[rightId];
        set<int> touched;
        collectAround(leftGroupId, touched);
        collectAround(rightGroupId, touched);
        clearNode(leftGroupId);
        if (rightGroupId != leftGroupId) clearNode(rightGroupId);
        ++groups[leftGroupId].leftPos;
        ++groups[rightGroupId].rightPos;
        if (groups[leftGroupId].leftPos == static_cast<int>(groups[leftGroupId].leftIds.size()) && groups[leftGroupId].rightPos == static_cast<int>(groups[leftGroupId].rightIds.size())) removeGroup(leftGroupId);
        if (rightGroupId != leftGroupId && groups[rightGroupId].leftPos == static_cast<int>(groups[rightGroupId].leftIds.size()) && groups[rightGroupId].rightPos == static_cast<int>(groups[rightGroupId].rightIds.size())) removeGroup(rightGroupId);
        for (int groupId : touched)
            if (groups[groupId].active) addNode(groupId);
    }

    void buildGroups() {
        sort(values.begin(), values.end());
        values.erase(unique(values.begin(), values.end()), values.end());
        groupCount = values.size();
        groups.assign(groupCount, Group());
        for (int i = 1; i <= n; ++i) {
            leftGroup[i] = lower_bound(values.begin(), values.end(), leftVal[i]) - values.begin();
            rightGroup[i] = lower_bound(values.begin(), values.end(), rightVal[i]) - values.begin();
            groups[leftGroup[i]].leftIds.push_back(i);
            groups[rightGroup[i]].rightIds.push_back(i);
        }
        for (int i = 0; i < groupCount; ++i) {
            groups[i].prevId = i == 0 ? -1 : i - 1;
            groups[i].nextId = i + 1 == groupCount ? -1 : i + 1;
        }
    }

public:
    void solveCase(int caseId) {
        cin >> n;
        leftVal.assign(n + 1, 0);
        rightVal.assign(n + 1, 0);
        leftGroup.assign(n + 1, 0);
        rightGroup.assign(n + 1, 0);
        values.clear();
        values.reserve(2 * n);
        for (int i = 1; i <= n; ++i) {
            cin >> leftVal[i];
            values.push_back(leftVal[i]);
        }
        for (int i = 1; i <= n; ++i) {
            cin >> rightVal[i];
            values.push_back(rightVal[i]);
        }
        buildGroups();
        candidates.clear();
        for (int i = 0; i < groupCount; ++i) addNode(i);
        cout << "Case #" << caseId << ":\n";
        for (int i = 1; i <= n; ++i) {
            Candidate best = *candidates.begin();
            cout << best.leftId << ' ' << best.rightId << '\n';
            removePair(best.leftId, best.rightId);
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    RobotHands solver;
    for (int caseId = 1; caseId <= t; ++caseId) solver.solveCase(caseId);
    return 0;
}
