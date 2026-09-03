#include <bits/stdc++.h>
using namespace std;

const int MaxN = 20;
const int MaxM = 100;
const int MaxCell = 400;
const int WordCnt = 7;
const int NegInf = -1000000000;

struct Mask {
    unsigned long long bit[WordCnt];
    bool operator == (const Mask &other) const {
        for (int i = 0; i < WordCnt; i++)
            if (bit[i] != other.bit[i])
                return false;
        return true;
    }
};

struct StateKey {
    int pos;
    Mask mask;
    bool operator == (const StateKey &other) const {
        return pos == other.pos && mask == other.mask;
    }
};

struct KeyHash {
    size_t operator () (const StateKey &key) const {
        size_t res = key.pos + 1009;
        for (int i = 0; i < WordCnt; i++)
            res = res * 1000003 + (size_t)(key.mask.bit[i] ^ (key.mask.bit[i] >> 32));
        return res;
    }
};

int n, m, rangeValue, startPos;
int heightValue[MaxCell], jewelValue[MaxCell];
Mask nearMask[MaxCell], farMask[MaxCell];
unordered_map<StateKey, vector<int>, KeyHash> memo;

Mask maskOr(const Mask &a, const Mask &b) {
    Mask res;
    for (int i = 0; i < WordCnt; i++)
        res.bit[i] = a.bit[i] | b.bit[i];
    return res;
}

Mask maskAnd(const Mask &a, const Mask &b) {
    Mask res;
    for (int i = 0; i < WordCnt; i++)
        res.bit[i] = a.bit[i] & b.bit[i];
    return res;
}

Mask maskAndNot(const Mask &a, const Mask &b) {
    Mask res;
    for (int i = 0; i < WordCnt; i++)
        res.bit[i] = a.bit[i] & (~b.bit[i]);
    return res;
}

vector<int> addMask(vector<int> dp, const Mask &mask) {
    for (int word = 0; word < WordCnt; word++) {
        unsigned long long value = mask.bit[word];
        while (value) {
            int offset = __builtin_ctzll(value);
            int id = word * 64 + offset;
            if (id < n * n && jewelValue[id] > 0) {
                for (int k = m; k >= 1; k--)
                    if (dp[k - 1] != NegInf)
                        dp[k] = max(dp[k], dp[k - 1] + jewelValue[id]);
            }
            value &= value - 1;
        }
    }
    return dp;
}

vector<int> mergeDp(const vector<int> &left, const vector<int> &right) {
    vector<int> res(m + 1, NegInf);
    for (int i = 0; i <= m; i++)
        if (left[i] != NegInf)
            for (int j = 0; i + j <= m; j++)
                if (right[j] != NegInf)
                    res[i + j] = max(res[i + j], left[i] + right[j]);
    return res;
}

vector<int> solve(int pos, const Mask &mask) {
    StateKey key;
    key.pos = pos;
    key.mask = mask;
    unordered_map<StateKey, vector<int>, KeyHash>::iterator it = memo.find(key);
    if (it != memo.end())
        return it->second;
    vector<int> result(m + 1, NegInf);
    result[0] = 0;
    int row = pos / n, col = pos % n;
    bool hasMove = false;
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};
    for (int d = 0; d < 4; d++) {
        int nextRow = row + dr[d], nextCol = col + dc[d];
        if (nextRow < 0 || nextRow >= n || nextCol < 0 || nextCol >= n)
            continue;
        int next = nextRow * n + nextCol;
        if (heightValue[next] >= heightValue[pos])
            continue;
        hasMove = true;
        Mask allMask = maskOr(mask, nearMask[next]);
        Mask nextMask = maskAnd(allMask, farMask[next]);
        Mask leavingMask = maskAndNot(mask, farMask[next]);
        vector<int> gain = addMask(solve(next, nextMask), leavingMask);
        for (int k = 0; k <= m; k++)
            result[k] = max(result[k], gain[k]);
    }
    if (!hasMove)
        result = addMask(result, mask);
    memo[key] = result;
    return result;
}

void initMasks() {
    for (int pos = 0; pos < n * n; pos++) {
        nearMask[pos] = Mask();
        farMask[pos] = Mask();
        int row = pos / n, col = pos % n;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                if (jewelValue[i * n + j] == 0)
                    continue;
                int distance = max(abs(i - row), abs(j - col));
                if (distance <= rangeValue)
                    nearMask[pos].bit[(i * n + j) / 64] |= 1ULL << ((i * n + j) % 64);
                if (distance <= 2 * rangeValue)
                    farMask[pos].bit[(i * n + j) / 64] |= 1ULL << ((i * n + j) % 64);
            }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int caseId = 1;
    while (cin >> n >> m >> rangeValue) {
        if (n == 0 && m == 0 && rangeValue == 0)
            break;
        int startRow, startCol;
        cin >> startRow >> startCol;
        startPos = (startRow - 1) * n + startCol - 1;
        for (int i = 0; i < n * n; i++)
            cin >> heightValue[i];
        for (int i = 0; i < n * n; i++)
            cin >> jewelValue[i];
        initMasks();
        memo.clear();
        Mask startMask = nearMask[startPos];
        vector<int> answer = solve(startPos, startMask);
        int best = 0;
        for (int k = 0; k <= m; k++)
            best = max(best, answer[k]);
        cout << "Case " << caseId++ << ": " << best << '\n';
    }
    return 0;
}
