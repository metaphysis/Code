#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using Node = pair<ll, int>;

struct Hedgehog {
    ll leftPos, rightPos, food;
    int group;
    bool picked;
};

struct Solver {
    vector<Hedgehog> hogs;
    multiset<Node> chosen[3], other[3];
    ll baseSum, slopeSum;

    ll getBase(int id) const {
        const Hedgehog &hog = hogs[id];
        if (hog.group == 0) return hog.food + hog.leftPos;
        if (hog.group == 1) return hog.food;
        return hog.food - hog.rightPos;
    }

    void setPicked(int id, bool picked) {
        Hedgehog &hog = hogs[id];
        int group = hog.group, delta = picked ? 1 : -1;
        ll base = getBase(id);
        Node node = {base, id};
        if (picked) {
            other[group].erase(other[group].find(node));
            chosen[group].insert(node);
        } else {
            chosen[group].erase(chosen[group].find(node));
            other[group].insert(node);
        }
        hog.picked = picked;
        baseSum += delta * base;
        slopeSum += delta * (group - 1);
    }

    void moveGroup(int id) {
        Hedgehog &hog = hogs[id];
        int group = hog.group;
        ll oldBase = getBase(id);
        multiset<Node> &src = hog.picked ? chosen[group] : other[group];
        src.erase(src.find({oldBase, id}));
        hog.group++;
        ll newBase = getBase(id);
        multiset<Node> &dst = hog.picked ? chosen[hog.group] : other[hog.group];
        dst.insert({newBase, id});
        if (hog.picked) {
            baseSum += newBase - oldBase;
            slopeSum++;
        }
    }

    void balance(ll pos) {
        while (true) {
            ll maxVal = LLONG_MIN, minVal = LLONG_MAX;
            int maxId = -1, minId = -1;
            for (int group = 0; group < 3; group++) {
                ll offset = (group - 1) * pos;
                if (!chosen[group].empty()) {
                    auto it = chosen[group].rbegin();
                    ll val = it->first + offset;
                    if (val > maxVal) {
                        maxVal = val;
                        maxId = it->second;
                    }
                }
                if (!other[group].empty()) {
                    auto it = other[group].begin();
                    ll val = it->first + offset;
                    if (val < minVal) {
                        minVal = val;
                        minId = it->second;
                    }
                }
            }
            if (minId == -1 || maxVal <= minVal) break;
            setPicked(maxId, false);
            setPicked(minId, true);
        }
    }

    ll solve(int k) {
        int n = hogs.size();
        ll totalFood = 0, best = LLONG_MAX;
        vector<Node> events;
        events.reserve(2 * n);
        baseSum = 0;
        slopeSum = 0;
        for (int i = 0; i < n; i++) {
            Hedgehog &hog = hogs[i];
            hog.group = 0;
            hog.picked = false;
            totalFood += hog.food;
            other[0].insert({hog.food + hog.leftPos, i});
            events.push_back({hog.leftPos, i});
            events.push_back({hog.rightPos, i});
        }
        for (int i = 0; i < k; i++) setPicked(other[0].begin()->second, true);
        sort(events.begin(), events.end());
        int idx = 0, eventCount = events.size();
        while (idx < eventCount) {
            ll pos = events[idx].first;
            balance(pos);
            best = min(best, baseSum + pos * slopeSum);
            while (idx < eventCount && events[idx].first == pos) {
                moveGroup(events[idx].second);
                idx++;
            }
        }
        return best - totalFood;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    while (cin >> n >> k) {
        Solver solver;
        solver.hogs.resize(n);
        for (int i = 0; i < n; i++) {
            ll pos, ability, food;
            cin >> pos >> ability >> food;
            solver.hogs[i] = {pos - ability, pos + ability, food, 0, false};
        }
        cout << solver.solve(k) << '\n';
    }
    return 0;
}
