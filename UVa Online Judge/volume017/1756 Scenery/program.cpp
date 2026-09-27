#include <bits/stdc++.h>
using namespace std;

struct Photo {
    long long releaseTime, deadline;
};

class FenwickTree {
    vector<int> tree;

public:
    void init(int size) {
        tree.assign(size + 1, 0);
    }

    void add(int index) {
        for (++index; index < (int)tree.size(); index += index & -index)
            ++tree[index];
    }

    int query(int index) const {
        int result = 0;
        for (++index; index > 0; index -= index & -index)
            result += tree[index];
        return result;
    }
};

class Scheduler {
    long long duration;
    vector<Photo> photos;
    vector<long long> deadlines, weight, rootOffset;
    vector<int> parent, groupSize;
    map<long long, int> offsetGroups;
    map<long long, long long> forbiddenRegions;
    set<int> relevantDeadlines;
    FenwickTree loadTree;

    int findRoot(int node) {
        if (parent[node] == node)
            return node;
        int previous = parent[node];
        parent[node] = findRoot(previous);
        weight[node] += weight[previous];
        return parent[node];
    }

    long long getOffset(int index) {
        if (parent[index] == -1)
            return 0;
        int root = findRoot(index);
        return rootOffset[root] + weight[index];
    }

    long long residue(long long value) const {
        value %= duration;
        return value < 0 ? value + duration : value;
    }

    long long criticalTime(int index) {
        return deadlines[index] - 1LL * loadTree.query(index) * duration
             - getOffset(index);
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

        parent[index] = index;
        groupSize[index] = 1;
        weight[index] = rootOffset[index] = 0;

        auto entry = offsetGroups.emplace(residue(deadlines[index]), index);
        if (!entry.second)
            entry.first->second = mergeGroups(index, entry.first->second, 0);
    }

    void updatePseudoOffsets(long long left, long long right,
                             long long time, int &nextDeadline) {
        int limit = lower_bound(deadlines.begin(), deadlines.end(), time)
                  - deadlines.begin();
        while (nextDeadline >= limit)
            addDeadline(nextDeadline--);

        long long leftResidue = residue(left);
        long long rightResidue = residue(right);
        auto existing = offsetGroups.find(leftResidue);
        int target = existing == offsetGroups.end() ? -1 : existing->second;

        // 遍历时直接摘除受影响的余数组；两端都不属于受影响区间。
        auto consume = [&](map<long long, int>::iterator it,
                           map<long long, int>::iterator end) {
            while (it != end) {
                auto current = it++;
                long long value = current->first;
                int source = current->second;
                offsetGroups.erase(current);

                long long increase =
                    (value - leftResidue + duration) % duration;
                if (target == -1) {
                    target = source;
                    rootOffset[findRoot(target)] += increase;
                } else {
                    target = mergeGroups(source, target, increase);
                }
            }
        };

        if (leftResidue < rightResidue) {
            consume(offsetGroups.upper_bound(leftResidue),
                    offsetGroups.lower_bound(rightResidue));
        } else {
            consume(offsetGroups.upper_bound(leftResidue),
                    offsetGroups.end());
            consume(offsetGroups.begin(),
                    offsetGroups.lower_bound(rightResidue));
        }

        if (target != -1)
            offsetGroups[leftResidue] = target;
    }

    void addForbiddenRegion(long long left, long long right) {
        if (left >= right)
            return;

        auto it = forbiddenRegions.lower_bound(left);
        if (it != forbiddenRegions.begin()) {
            auto previous = prev(it);
            if (previous->second > left) {
                left = previous->first;
                right = max(right, previous->second);
                it = forbiddenRegions.erase(previous);
            }
        }
        while (it != forbiddenRegions.end() && it->first < right) {
            right = max(right, it->second);
            it = forbiddenRegions.erase(it);
        }
        forbiddenRegions[left] = right;
    }

    long long moveRight(long long time) const {
        auto it = forbiddenRegions.upper_bound(time);
        if (it == forbiddenRegions.begin())
            return time;
        --it;
        return it->first < time && time < it->second ? it->second : time;
    }

    bool buildForbiddenRegions() {
        deadlines.clear();
        for (const Photo &photo : photos)
            deadlines.push_back(photo.deadline);
        sort(deadlines.begin(), deadlines.end());
        deadlines.erase(unique(deadlines.begin(), deadlines.end()),
                        deadlines.end());

        int count = deadlines.size();
        loadTree.init(count);
        parent.assign(count, -1);
        groupSize.assign(count, 0);
        weight.assign(count, 0);
        rootOffset.assign(count, 0);
        offsetGroups.clear();
        forbiddenRegions.clear();
        relevantDeadlines.clear();
        for (int i = 0; i < count; ++i)
            relevantDeadlines.insert(i);

        sort(photos.begin(), photos.end(),
             [](const Photo &a, const Photo &b) {
                 if (a.releaseTime != b.releaseTime)
                     return a.releaseTime < b.releaseTime;
                 return a.deadline < b.deadline;
             });

        int nextDeadline = count - 1;
        int minimumIndex = count - 1;
        for (int i = (int)photos.size() - 1; i >= 0; --i) {
            int index = lower_bound(deadlines.begin(), deadlines.end(),
                                    photos[i].deadline) - deadlines.begin();
            loadTree.add(index);
            minimumIndex = min(minimumIndex, index);

            auto current = relevantDeadlines.lower_bound(index);
            long long time = criticalTime(*current);
            while (current != relevantDeadlines.begin()) {
                auto previous = prev(current);
                if (criticalTime(*previous) <= time)
                    break;
                relevantDeadlines.erase(previous);
            }

            if (i > 0 && photos[i - 1].releaseTime == photos[i].releaseTime)
                continue;

            time = criticalTime(*relevantDeadlines.lower_bound(minimumIndex));
            if (time < photos[i].releaseTime)
                return false;
            if (time < photos[i].releaseTime + duration) {
                long long left = time - duration;
                long long right = photos[i].releaseTime;
                addForbiddenRegion(left, right);
                updatePseudoOffsets(left, right, time, nextDeadline);
            }
        }
        return true;
    }

    bool generateSchedule() const {
        priority_queue<long long, vector<long long>, greater<long long>> ready;
        long long currentTime = 0;
        int nextPhoto = 0;

        while (nextPhoto < (int)photos.size() || !ready.empty()) {
            currentTime = moveRight(currentTime);
            while (nextPhoto < (int)photos.size() &&
                   photos[nextPhoto].releaseTime <= currentTime) {
                ready.push(photos[nextPhoto].deadline);
                ++nextPhoto;
            }
            if (ready.empty()) {
                currentTime = max(currentTime, photos[nextPhoto].releaseTime);
                continue;
            }
            if (currentTime + duration > ready.top())
                return false;
            ready.pop();
            currentTime += duration;
        }
        return true;
    }

public:
    bool solve(vector<Photo> inputPhotos, long long inputDuration) {
        photos = move(inputPhotos);
        duration = inputDuration;
        return buildForbiddenRegions() && generateSchedule();
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
}
