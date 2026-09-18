#include <bits/stdc++.h>
using namespace std;

using Real = long double;

struct Target {
    int x, y, id;
};

struct Group {
    int x, y;
    vector<int> ids;
};

struct Interval {
    Real low, high;
};

struct Motion {
    Real center, delta, minSpeed, maxSpeed;
};

using IntervalSet = vector<Interval>;

bool lessEqual(Real a, Real b) {
    if (a <= b) return true;
    if (!isfinite(a) || !isfinite(b)) return false;
    Real scale = max((Real)1, max(fabsl(a), fabsl(b)));
    return a - b <= 64 * numeric_limits<Real>::epsilon() * scale;
}

bool transferInterval(const Interval &src, const Motion &motion, Interval &dst) {
    Real left = max(src.low, motion.minSpeed), right = min(src.high, motion.maxSpeed);
    if (!lessEqual(left, right)) return false;
    if (left > right) left = right = (left + right) / 2;
    Real half = motion.delta / 2;
    Real lowRad = max((Real)0, motion.delta * (half - motion.center + right));
    Real highRad = max((Real)0, motion.delta * (half + motion.center - left));
    dst.low = right + motion.delta - 2 * sqrtl(lowRad);
    dst.high = left - motion.delta + 2 * sqrtl(highRad);
    if (dst.low > dst.high) dst.low = dst.high = (dst.low + dst.high) / 2;
    return true;
}

void mergeIntervals(IntervalSet &ranges) {
    if (ranges.empty()) return;
    sort(ranges.begin(), ranges.end(), [](const Interval &a, const Interval &b) {
        if (a.low != b.low) return a.low < b.low;
        return a.high > b.high;
    });
    int write = 0, rangeCount = (int)ranges.size();
    for (int i = 1; i < rangeCount; ++i) {
        if (lessEqual(ranges[i].low, ranges[write].high)) {
            ranges[write].high = max(ranges[write].high, ranges[i].high);
        } else {
            ++write;
            ranges[write] = ranges[i];
        }
    }
    ranges.resize(write + 1);
}

bool intersects(const IntervalSet &ranges, const Interval &query) {
    int left = 0, right = (int)ranges.size();
    while (left < right) {
        int mid = (left + right) / 2;
        if (lessEqual(query.low, ranges[mid].high)) right = mid;
        else left = mid + 1;
    }
    return left < (int)ranges.size() && lessEqual(ranges[left].low, query.high);
}

void printAnswer(const vector<int> &answer) {
    if (answer.empty()) {
        cout << "Cannot visit any targets\n";
        return;
    }
    for (int i = 0; i < (int)answer.size(); ++i) {
        if (i > 0) cout << ' ';
        cout << answer[i];
    }
    cout << '\n';
}

void solveCase(int vy, int maxAcc, const vector<Target> &targets) {
    vector<int> answer;
    if (vy == 0) {
        for (const Target &target : targets) if (target.y == 0 && (maxAcc > 0 || target.x == 0)) answer.push_back(target.id);
        printAnswer(answer);
        return;
    }
    vector<Target> valid;
    valid.reserve(targets.size());
    for (const Target &target : targets) {
        if (target.y < 0) continue;
        if (target.y == 0 && target.x != 0) continue;
        valid.push_back(target);
    }
    sort(valid.begin(), valid.end(), [](const Target &a, const Target &b) {
        if (a.y != b.y) return a.y < b.y;
        if (a.x != b.x) return a.x < b.x;
        return a.id < b.id;
    });
    if (maxAcc == 0) {
        for (const Target &target : valid) if (target.x == 0) answer.push_back(target.id);
        printAnswer(answer);
        return;
    }
    vector<Group> groups;
    groups.push_back({0, 0, {}});
    for (const Target &target : valid) {
        if (target.y == 0) {
            answer.push_back(target.id);
        } else {
            if (groups.back().x != target.x || groups.back().y != target.y) groups.push_back({target.x, target.y, {}});
            groups.back().ids.push_back(target.id);
        }
    }
    int groupCount = (int)groups.size();
    vector<int> weight(groupCount), suffixCount(groupCount + 1, 0);
    for (int i = 1; i < groupCount; ++i) weight[i] = (int)groups[i].ids.size();
    for (int i = groupCount - 1; i >= 0; --i) suffixCount[i] = suffixCount[i + 1] + weight[i];
    vector<vector<Motion>> motions(groupCount, vector<Motion>(groupCount));
    for (int i = 0; i < groupCount; ++i) {
        for (int j = i + 1; j < groupCount; ++j) {
            if (groups[j].y <= groups[i].y) continue;
            Real time = (Real)(groups[j].y - groups[i].y) / vy;
            Real center = ((Real)groups[j].x - groups[i].x) / time;
            Real delta = (Real)maxAcc * time;
            motions[i][j] = {center, delta, center - delta / 2, center + delta / 2};
        }
    }
    Real inf = numeric_limits<Real>::infinity();
    vector<vector<IntervalSet>> dp(groupCount);
    for (int i = groupCount - 1; i >= 0; --i) {
        int limit = suffixCount[i + 1];
        dp[i].resize(limit + 1);
        dp[i][0].push_back({-inf, inf});
        for (int count = 1; count <= limit; ++count) {
            IntervalSet &ranges = dp[i][count];
            for (int j = i + 1; j < groupCount; ++j) {
                if (groups[j].y <= groups[i].y || count < weight[j]) continue;
                int rest = count - weight[j];
                if (rest >= (int)dp[j].size() || dp[j][rest].empty()) continue;
                const Motion &motion = motions[i][j];
                for (const Interval &src : dp[j][rest]) {
                    Interval dst;
                    if (transferInterval(src, motion, dst)) ranges.push_back(dst);
                }
            }
            mergeIntervals(ranges);
        }
    }
    Interval current = {0, 0};
    int remain = suffixCount[1], currentId = 0;
    while (remain > 0 && !intersects(dp[0][remain], current)) --remain;
    vector<int> visitOrder;
    for (int i = 1; i < groupCount; ++i) visitOrder.push_back(i);
    sort(visitOrder.begin(), visitOrder.end(), [&](int a, int b) {
        return groups[a].ids[0] < groups[b].ids[0];
    });
    while (remain > 0) {
        int nextId = -1;
        Interval nextRange = {};
        for (int j : visitOrder) {
            if (groups[j].y <= groups[currentId].y || weight[j] > remain) continue;
            int rest = remain - weight[j];
            if (rest >= (int)dp[j].size() || dp[j][rest].empty()) continue;
            Interval candidate;
            if (!transferInterval(current, motions[currentId][j], candidate)) continue;
            if (!intersects(dp[j][rest], candidate)) continue;
            nextId = j;
            nextRange = candidate;
            break;
        }
        assert(nextId != -1);
        answer.insert(answer.end(), groups[nextId].ids.begin(), groups[nextId].ids.end());
        remain -= weight[nextId];
        currentId = nextId;
        current = nextRange;
    }
    printAnswer(answer);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, vy, maxAcc;
    while (cin >> n >> vy >> maxAcc) {
        vector<Target> targets(n);
        for (int i = 0; i < n; ++i) {
            cin >> targets[i].x >> targets[i].y;
            targets[i].id = i + 1;
        }
        solveCase(vy, maxAcc, targets);
    }
    return 0;
}
