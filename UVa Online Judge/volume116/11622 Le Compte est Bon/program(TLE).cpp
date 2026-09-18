#include <bits/stdc++.h>
using namespace std;

const int maxTarget = 8000;
const int stateCount = 38759;
const long long fiveLimit = 800000;
const long long valueLimit = 1000000000000LL;

struct State {
    array<int, 6> nums;
    int len;
    long long code;
    vector<long long> vals;
    bitset<maxTarget + 1> can;
};

int numVals[14] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 25, 50, 75, 100};
int fact[7] = {1, 1, 2, 6, 24, 120, 720}, answers[maxTarget + 1], targetCount;
long long codePow[14];
array<int, 6> curNums;
vector<State> states;
vector<int> targets;
unordered_map<long long, int> stateId;
bitset<maxTarget + 1> wanted;

void buildStates(int len, int pos, int start, long long code) {
    if (pos == len) {
        State cur;
        cur.nums = curNums;
        cur.len = len;
        cur.code = code;
        stateId.emplace(code, static_cast<int>(states.size()));
        states.push_back(move(cur));
        return;
    }
    for (int i = start; i < 14; ++i) {
        curNums[pos] = i;
        buildStates(len, pos + 1, i, code + codePow[i]);
    }
}

void addValue(State &cur, long long val, long long limit, int &leftCount) {
    if (val <= 0 || val > limit) return;
    if (cur.len < 6) {
        cur.vals.push_back(val);
    } else if (wanted[static_cast<size_t>(val)] && !cur.can[static_cast<size_t>(val)]) {
        cur.can.set(static_cast<size_t>(val));
        --leftCount;
    }
}

void combineVals(State &cur, const vector<long long> &leftVals, const vector<long long> &rightVals, long long limit, int &leftCount) {
    for (long long x : leftVals) {
        for (long long y : rightVals) {
            long long high = max(x, y), low = min(x, y);
            addValue(cur, x + y, limit, leftCount);
            addValue(cur, x * y, limit, leftCount);
            if (high > low) addValue(cur, high - low, limit, leftCount);
            if (high % low == 0) addValue(cur, high / low, limit, leftCount);
            if (cur.len == 6 && leftCount == 0) return;
        }
    }
}

void solveState(int id) {
    State &cur = states[id];
    if (cur.len == 1) {
        int val = numVals[cur.nums[0]];
        cur.vals.push_back(val);
        if (wanted[val]) cur.can.set(val);
        return;
    }
    for (int i = 0; i < cur.len; ++i) {
        if (i > 0 && cur.nums[i] == cur.nums[i - 1]) continue;
        int subId = stateId.find(cur.code - codePow[cur.nums[i]])->second;
        cur.can |= states[subId].can;
    }
    int leftCount = targetCount - static_cast<int>(cur.can.count()), fullMask = (1 << cur.len) - 1;
    long long limit = cur.len == 6 ? maxTarget : (cur.len == 5 ? fiveLimit : valueLimit);
    if (cur.len == 6 && leftCount == 0) return;
    for (int mask = 1; mask < fullMask; ++mask) {
        int subLen = __builtin_popcount(static_cast<unsigned int>(mask));
        long long leftCode = 0, rightCode;
        bool valid = true;
        if (subLen * 2 > cur.len) continue;
        for (int i = 0; i < cur.len; ++i) {
            if ((mask & (1 << i)) == 0) continue;
            if (i > 0 && cur.nums[i] == cur.nums[i - 1] && (mask & (1 << (i - 1))) == 0) {
                valid = false;
                break;
            }
            leftCode += codePow[cur.nums[i]];
        }
        if (!valid) continue;
        rightCode = cur.code - leftCode;
        if (subLen * 2 == cur.len && leftCode > rightCode) continue;
        int leftId = stateId.find(leftCode)->second, rightId = stateId.find(rightCode)->second;
        combineVals(cur, states[leftId].vals, states[rightId].vals, limit, leftCount);
        if (cur.len == 6 && leftCount == 0) return;
    }
    if (cur.len == 6) return;
    sort(cur.vals.begin(), cur.vals.end());
    cur.vals.erase(unique(cur.vals.begin(), cur.vals.end()), cur.vals.end());
    vector<long long>(cur.vals).swap(cur.vals);
    for (long long val : cur.vals) {
        if (val > maxTarget) break;
        if (wanted[static_cast<size_t>(val)]) cur.can.set(static_cast<size_t>(val));
    }
}

int getWeight(const State &cur) {
    int divisor = 1, repeatCount = 1;
    for (int i = 1; i < cur.len; ++i) {
        if (cur.nums[i] == cur.nums[i - 1]) {
            ++repeatCount;
        } else {
            divisor *= fact[repeatCount];
            repeatCount = 1;
        }
    }
    divisor *= fact[repeatCount];
    return fact[cur.len] / divisor;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseCount;
    cin >> caseCount;
    vector<int> queries(caseCount);
    for (int &target : queries) {
        cin >> target;
        if (target != 1 && !wanted[target]) {
            wanted.set(target);
            targets.push_back(target);
        }
    }
    answers[1] = 7529536;
    targetCount = static_cast<int>(targets.size());
    if (targetCount > 0) {
        codePow[0] = 1;
        for (int i = 1; i < 14; ++i) codePow[i] = codePow[i - 1] * 7;
        states.reserve(stateCount);
        stateId.max_load_factor(0.7f);
        stateId.reserve(stateCount);
        for (int len = 1; len <= 6; ++len) buildStates(len, 0, 0, 0);
        for (int id = 0; id < static_cast<int>(states.size()); ++id) {
            solveState(id);
            if (states[id].len != 6) continue;
            int weight = getWeight(states[id]);
            for (int target : targets) if (states[id].can[target]) answers[target] += weight;
        }
    }
    for (int target : queries) cout << answers[target] << '\n';
    return 0;
}
