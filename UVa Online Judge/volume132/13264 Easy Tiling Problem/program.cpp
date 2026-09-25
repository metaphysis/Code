#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007, invTwo = 500000004;
using Matrix = vector<vector<int>>;

int modPow(int base, int exp) {
    int res = 1;
    while (exp > 0) {
        if (exp & 1) res = 1LL * res * base % mod;
        base = 1LL * base * base % mod;
        exp >>= 1;
    }
    return res;
}

Matrix mulMat(const Matrix &a, const Matrix &b) {
    int size = a.size();
    Matrix bt(size, vector<int>(size)), res(size, vector<int>(size));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) bt[j][i] = b[i][j];
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            long long sum = 0;
            for (int left = 0; left < size; left += 8) {
                int right = min(left + 8, size);
                for (int k = left; k < right; k++) sum += 1LL * a[i][k] * bt[j][k];
                sum %= mod;
            }
            res[i][j] = sum;
        }
    }
    return res;
}

vector<int> mulVec(const vector<int> &vec, const Matrix &mat) {
    int size = vec.size();
    vector<int> res(size);
    for (int j = 0; j < size; j++) {
        long long sum = 0;
        for (int left = 0; left < size; left += 8) {
            int right = min(left + 8, size);
            for (int i = left; i < right; i++) sum += 1LL * vec[i] * mat[i][j];
            sum %= mod;
        }
        res[j] = sum;
    }
    return res;
}

struct Solver {
    int height, stateCount;
    vector<vector<int>> states, cutTo, cutWeight, joinTo;
    vector<int> initVec, endWeight;
    vector<Matrix> matPowers;
    unordered_map<int, int> stateId;

    int encode(const vector<int> &labels) {
        int code = 0, nextId = 0;
        int remap[7];
        fill(remap, remap + 7, -1);
        for (int label : labels) {
            if (remap[label] == -1) remap[label] = nextId++;
            code = code * 8 + remap[label];
        }
        return code;
    }

    bool isValid(const vector<int> &labels) {
        for (int a = 0; a < height; a++) {
            for (int b = a + 1; b < height; b++) {
                if (labels[a] == labels[b]) continue;
                for (int c = b + 1; c < height; c++) {
                    if (labels[a] != labels[c]) continue;
                    for (int d = c + 1; d < height; d++) if (labels[b] == labels[d]) return false;
                }
            }
        }
        return true;
    }

    void genStates(int pos, int maxLabel, vector<int> &labels) {
        if (pos == height) {
            if (isValid(labels)) states.push_back(labels);
            return;
        }
        for (int label = 0; label <= maxLabel + 1; label++) {
            labels[pos] = label;
            genStates(pos + 1, max(maxLabel, label), labels);
        }
    }

    void buildStates() {
        vector<int> labels(height);
        genStates(0, -1, labels);
        stateCount = states.size();
        stateId.reserve(stateCount * 2);
        for (int s = 0; s < stateCount; s++) stateId[encode(states[s])] = s;
        cutTo.assign(stateCount, vector<int>(height));
        cutWeight.assign(stateCount, vector<int>(height));
        joinTo.assign(stateCount, vector<int>(height));
        endWeight.resize(stateCount);
        for (int s = 0; s < stateCount; s++) {
            int blockCount = *max_element(states[s].begin(), states[s].end()) + 1;
            endWeight[s] = modPow(4, blockCount);
            for (int pos = 0; pos < height; pos++) {
                labels = states[s];
                int oldLabel = labels[pos], count = 0;
                for (int label : labels) if (label == oldLabel) count++;
                cutWeight[s][pos] = count == 1 ? 4 : 1;
                labels[pos] = height;
                cutTo[s][pos] = stateId.at(encode(labels));
                if (pos == 0) {
                    joinTo[s][pos] = s;
                    continue;
                }
                labels = states[s];
                int fromLabel = labels[pos], toLabel = labels[pos - 1];
                for (int &label : labels) if (label == fromLabel) label = toLabel;
                joinTo[s][pos] = stateId.at(encode(labels));
            }
        }
    }

    vector<int> applyJoin(const vector<int> &vec, int pos) {
        vector<int> res = vec;
        for (int s = 0; s < stateCount; s++) {
            int to = joinTo[s][pos];
            res[to] = (res[to] + 2LL * vec[s]) % mod;
        }
        return res;
    }

    vector<int> applyReplace(const vector<int> &vec, int pos) {
        vector<int> res(stateCount);
        for (int s = 0; s < stateCount; s++) {
            int to = cutTo[s][pos];
            res[s] = (res[s] + 2LL * vec[s]) % mod;
            res[to] = (res[to] + 1LL * cutWeight[s][pos] * vec[s]) % mod;
        }
        return res;
    }

    void init(int newHeight, int maxWidth) {
        height = newHeight;
        buildStates();
        int norm = modPow(invTwo, height);
        vector<int> labels(height);
        iota(labels.begin(), labels.end(), 0);
        initVec.assign(stateCount, 0);
        initVec[stateId.at(encode(labels))] = norm;
        for (int pos = 1; pos < height; pos++) initVec = applyJoin(initVec, pos);
        if (maxWidth == 1) return;
        Matrix trans(stateCount, vector<int>(stateCount));
        for (int s = 0; s < stateCount; s++) {
            vector<int> vec(stateCount);
            vec[s] = 1;
            for (int pos = 0; pos < height; pos++) {
                vec = applyReplace(vec, pos);
                if (pos > 0) vec = applyJoin(vec, pos);
            }
            for (int to = 0; to < stateCount; to++) trans[s][to] = 1LL * vec[to] * norm % mod;
        }
        matPowers.push_back(move(trans));
        int exp = (maxWidth - 1) >> 1;
        while (exp > 0) {
            Matrix nextMat = mulMat(matPowers.back(), matPowers.back());
            matPowers.push_back(move(nextMat));
            exp >>= 1;
        }
    }

    int solve(int width) {
        vector<int> vec = initVec;
        int exp = width - 1, bit = 0, ans = 0;
        while (exp > 0) {
            if (exp & 1) vec = mulVec(vec, matPowers[bit]);
            exp >>= 1;
            bit++;
        }
        for (int s = 0; s < stateCount; s++) ans = (ans + 1LL * vec[s] * endWeight[s]) % mod;
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    vector<pair<int, int>> queries;
    vector<int> maxWidth(7, 0);
    while (cin >> n >> m) {
        int height = min(n, m) / 4, width = max(n, m) / 4;
        queries.emplace_back(height, width);
        maxWidth[height] = max(maxWidth[height], width);
    }
    vector<Solver> solvers(7);
    for (int height = 1; height <= 6; height++) if (maxWidth[height] > 0) solvers[height].init(height, maxWidth[height]);
    for (const auto &query : queries) cout << solvers[query.first].solve(query.second) << '\n';
    return 0;
}
