#include <bits/stdc++.h>
using namespace std;

struct Photo {
    long long releaseTime, deadline;
};

class FenwickTree {
private:
    int size;
    vector<int> tree;

public:
    void init(int count) {
        size = count;
        tree.assign(size + 1, 0);
    }

    void add(int index, int value) {
        for (++index; index <= size; index += index & -index)
            tree[index] += value;
    }

    int query(int index) {
        int result = 0;
        for (++index; index > 0; index -= index & -index)
            result += tree[index];
        return result;
    }

    void addSuffix(int index) {
        add(index, 1);
    }
};

class Scheduler {
private:
    long long duration;
    vector<long long> deadlines, weight, rootOffset;
    vector<int> parent, groupSize;
    vector<Photo> photos;
    map<long long, int> offsetGroups;
    map<long long, long long> forbiddenRegions;
    set<int> relevantDeadlines;
    FenwickTree loadTree;

    int findRoot(int node) {
        if (parent[node] == node)
            return node;
        int oldParent = parent[node];
        parent[node] = findRoot(oldParent);
        weight[node] += weight[oldParent];
        return parent[node];
    }

    long long getOffset(int index) {
        if (parent[index] == -1)
            return 0;
        int root = findRoot(index);
        return rootOffset[root] + weight[index];
    }

    long long getResidue(long long value) {
        long long residue = value % duration;
        if (residue < 0)
            residue += duration;
        return residue;
    }

    long long getCriticalTime(int index) {
        return deadlines[index] - 1LL * loadTree.query(index) * duration - getOffset(index);
    }

    int mergeGroups(int source, int target, long long increase) {
        source = findRoot(source);
        target = findRoot(target);
        if (source == target)
            return target;
        if (groupSize[source] <= groupSize[target]) {
            parent[source] = target;
            weight[source] = rootOffset[source] + increase - rootOffset[target];
            groupSize[target] += groupSize[source];
            return target;
        }
        long long oldTargetOffset = rootOffset[target];
        rootOffset[source] += increase;
        parent[target] = source;
        weight[target] = oldTargetOffset - rootOffset[source];
        groupSize[source] += groupSize[target];
        return source;
    }

    void addDeadline(int index) {
        if (parent[index] != -1)
            return;
        long long residue = getResidue(deadlines[index]);
        parent[index] = index;
        groupSize[index] = 1;
        weight[index] = 0;
        rootOffset[index] = 0;
        auto it = offsetGroups.find(residue);
        if (it == offsetGroups.end()) {
            offsetGroups[residue] = index;
        } else {
            it->second = mergeGroups(index, it->second, 0);
        }
    }

    void collectResidues(long long lower, long long upper, vector<long long> &affected) {
        auto it = offsetGroups.upper_bound(lower);
        auto endIt = offsetGroups.lower_bound(upper);
        while (it != endIt) {
            affected.push_back(it->first);
            ++it;
        }
    }

    void updatePseudoOffsets(long long left, long long right, long long criticalTime, int &nextDeadline) {
        int limit = lower_bound(deadlines.begin(), deadlines.end(), criticalTime) - deadlines.begin();
        while (nextDeadline >= limit) {
            addDeadline(nextDeadline);
            --nextDeadline;
        }
        long long leftResidue = getResidue(left);
        long long rightResidue = getResidue(right);
        vector<long long> affected;
        if (leftResidue < rightResidue) {
            collectResidues(leftResidue, rightResidue, affected);
        } else {
            auto it = offsetGroups.upper_bound(leftResidue);
            while (it != offsetGroups.end()) {
                affected.push_back(it->first);
                ++it;
            }
            it = offsetGroups.begin();
            auto endIt = offsetGroups.lower_bound(rightResidue);
            while (it != endIt) {
                affected.push_back(it->first);
                ++it;
            }
        }
        if (affected.empty())
            return;
        int target;
        auto targetIt = offsetGroups.find(leftResidue);
        if (targetIt != offsetGroups.end()) {
            target = targetIt->second;
        } else {
            long long residue = affected.front();
            target = offsetGroups[residue];
            offsetGroups.erase(residue);
            long long increase = (residue - leftResidue + duration) % duration;
            rootOffset[findRoot(target)] += increase;
        }
        for (long long residue : affected) {
            auto it = offsetGroups.find(residue);
            if (it == offsetGroups.end())
                continue;
            int source = it->second;
            offsetGroups.erase(it);
            long long increase = (residue - leftResidue + duration) % duration;
            target = mergeGroups(source, target, increase);
        }
        offsetGroups[leftResidue] = target;
    }

    void addForbiddenRegion(long long left, long long right) {
        if (left >= right)
            return;
        auto it = forbiddenRegions.lower_bound(left);
        if (it != forbiddenRegions.begin()) {
            auto previousIt = prev(it);
            if (previousIt->second > left) {
                left = previousIt->first;
                right = max(right, previousIt->second);
                it = forbiddenRegions.erase(previousIt);
            }
        }
        while (it != forbiddenRegions.end() && it->first < right) {
            right = max(right, it->second);
            it = forbiddenRegions.erase(it);
        }
        forbiddenRegions[left] = right;
    }

    long long moveRight(long long time) {
        auto it = forbiddenRegions.upper_bound(time);
        if (it == forbiddenRegions.begin())
            return time;
        --it;
        if (it->first < time && time < it->second)
            return it->second;
        return time;
    }

    bool buildForbiddenRegions() {
        deadlines.clear();
        for (const Photo &photo : photos)
            deadlines.push_back(photo.deadline);
        sort(deadlines.begin(), deadlines.end());
        deadlines.erase(unique(deadlines.begin(), deadlines.end()), deadlines.end());
        int deadlineCount = deadlines.size();
        loadTree.init(deadlineCount);
        parent.assign(deadlineCount, -1);
        groupSize.assign(deadlineCount, 0);
        weight.assign(deadlineCount, 0);
        rootOffset.assign(deadlineCount, 0);
        offsetGroups.clear();
        forbiddenRegions.clear();
        relevantDeadlines.clear();
        for (int i = 0; i < deadlineCount; ++i)
            relevantDeadlines.insert(i);
        sort(photos.begin(), photos.end(), [](const Photo &first, const Photo &second) {
            if (first.releaseTime != second.releaseTime)
                return first.releaseTime < second.releaseTime;
            return first.deadline < second.deadline;
        });
        int nextDeadline = deadlineCount - 1;
        long long minimumDeadline = LLONG_MAX;
        for (int i = (int)photos.size() - 1; i >= 0; --i) {
            int deadlineIndex = lower_bound(deadlines.begin(), deadlines.end(), photos[i].deadline) - deadlines.begin();
            loadTree.addSuffix(deadlineIndex);
            minimumDeadline = min(minimumDeadline, photos[i].deadline);
            auto currentIt = relevantDeadlines.lower_bound(deadlineIndex);
            int currentIndex = *currentIt;
            long long currentTime = getCriticalTime(currentIndex);
            while (currentIt != relevantDeadlines.begin()) {
                auto previousIt = prev(currentIt);
                if (getCriticalTime(*previousIt) <= currentTime)
                    break;
                relevantDeadlines.erase(previousIt);
            }
            if (i == 0 || photos[i - 1].releaseTime < photos[i].releaseTime) {
                int minimumIndex = lower_bound(deadlines.begin(), deadlines.end(), minimumDeadline) - deadlines.begin();
                auto criticalIt = relevantDeadlines.lower_bound(minimumIndex);
                long long criticalTime = getCriticalTime(*criticalIt);
                if (criticalTime < photos[i].releaseTime)
                    return false;
                if (criticalTime < photos[i].releaseTime + duration) {
                    long long left = criticalTime - duration;
                    long long right = photos[i].releaseTime;
                    addForbiddenRegion(left, right);
                    updatePseudoOffsets(left, right, criticalTime, nextDeadline);
                }
            }
        }
        return true;
    }

    bool generateSchedule() {
        priority_queue<long long, vector<long long>, greater<long long>> ready;
        long long currentTime = 0;
        int nextPhoto = 0;
        int completed = 0;
        while (completed < (int)photos.size()) {
            currentTime = moveRight(currentTime);
            while (nextPhoto < (int)photos.size() && photos[nextPhoto].releaseTime <= currentTime) {
                ready.push(photos[nextPhoto].deadline);
                ++nextPhoto;
            }
            if (ready.empty()) {
                if (nextPhoto == (int)photos.size())
                    return false;
                currentTime = max(currentTime, photos[nextPhoto].releaseTime);
                continue;
            }
            long long deadline = ready.top();
            ready.pop();
            if (currentTime + duration > deadline)
                return false;
            currentTime += duration;
            ++completed;
        }
        return true;
    }

public:
    bool solve(vector<Photo> inputPhotos, long long inputDuration) {
        photos = move(inputPhotos);
        duration = inputDuration;
        if (!buildForbiddenRegions())
            return false;
        return generateSchedule();
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long t;
    while (cin >> n >> t) {
        vector<Photo> photos(n);
        for (Photo &photo : photos)
            cin >> photo.releaseTime >> photo.deadline;
        Scheduler scheduler;
        cout << (scheduler.solve(move(photos), t) ? "yes" : "no") << '\n';
    }
    return 0;
}
