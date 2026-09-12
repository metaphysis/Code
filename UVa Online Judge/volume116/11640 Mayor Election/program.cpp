#include <bits/stdc++.h>
using namespace std;

const int mod = 786433;
const int primitiveRoot = 10;

int powerMod(int a, int b) {
    long long result = 1, base = a;
    while (b > 0) {
        if (b & 1) result = result * base % mod;
        base = base * base % mod;
        b >>= 1;
    }
    return (int)result;
}

void ntt(vector<int> &a, bool invert) {
    int n = (int)a.size(), i, j, len;
    for (i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        while (j & bit) {
            j ^= bit;
            bit >>= 1;
        }
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (len = 2; len <= n; len <<= 1) {
        int root = powerMod(primitiveRoot, (mod - 1) / len);
        if (invert) root = powerMod(root, mod - 2);
        for (i = 0; i < n; i += len) {
            long long currentRoot = 1;
            for (j = 0; j < len / 2; j++) {
                int u = a[i + j], v = (int)(a[i + j + len / 2] * currentRoot % mod);
                a[i + j] = u + v;
                if (a[i + j] >= mod) a[i + j] -= mod;
                a[i + j + len / 2] = u - v;
                if (a[i + j + len / 2] < 0) a[i + j + len / 2] += mod;
                currentRoot = currentRoot * root % mod;
            }
        }
    }
    if (invert) {
        int inverseN = powerMod(n, mod - 2);
        for (i = 0; i < n; i++) a[i] = (int)((long long)a[i] * inverseN % mod);
    }
}

vector<int> multiplyPoly(const vector<int> &a, const vector<int> &b, int maxLen) {
    if (a.empty() || b.empty()) return {};
    int fullSize = (int)a.size() + (int)b.size() - 1, needSize = min(maxLen + 1, fullSize), n = 1;
    while (n < fullSize) n <<= 1;
    vector<int> fa = a, fb = b;
    fa.resize(n);
    fb.resize(n);
    ntt(fa, false);
    ntt(fb, false);
    for (int i = 0; i < n; i++) fa[i] = (int)((long long)fa[i] * fb[i] % mod);
    ntt(fa, true);
    fa.resize(needSize);
    return fa;
}

vector<int> buildCandidatePoly(int posterCount, int lowerBound, int upperBound, const vector<int> &caps, int maxLen) {
    int upper = min(upperBound, maxLen);
    vector<int> result(upper + 1, 0);
    result[0] = 1;
    if (upper == 0 || posterCount == 0) return result;
    vector<vector<int>> current(posterCount);
    for (int i = 0; i < posterCount; i++) {
        current[i].assign(caps[i] + 1, 0);
        current[i][1] = 1;
    }
    for (int length = 1; length <= upper; length++) {
        long long total = 0;
        for (int i = 0; i < posterCount; i++)
            for (int run = 1; run <= caps[i]; run++)
                total += current[i][run];
        result[length] = (int)(total % mod);
        if (length == upper) break;
        vector<vector<int>> next(posterCount);
        for (int i = 0; i < posterCount; i++) next[i].assign(caps[i] + 1, 0);
        for (int i = 0; i < posterCount; i++) {
            for (int run = 1; run <= caps[i]; run++) {
                int value = current[i][run];
                if (value == 0) continue;
                if (run < caps[i]) {
                    next[i][run + 1] += value;
                    if (next[i][run + 1] >= mod) next[i][run + 1] -= mod;
                }
                for (int j = 0; j < posterCount; j++) {
                    if (i == j) continue;
                    next[j][1] += value;
                    if (next[j][1] >= mod) next[j][1] -= mod;
                }
            }
        }
        current.swap(next);
    }
    for (int i = 0; i < min(lowerBound, maxLen + 1); i++) result[i] = 0;
    if (lowerBound > maxLen) fill(result.begin(), result.end(), 0);
    return result;
}

struct PolyCompare {
    bool operator()(const vector<int> &a, const vector<int> &b) const {
        return a.size() > b.size();
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int testCase = 1; testCase <= testCount; testCase++) {
        int candidateCount;
        cin >> candidateCount;
        vector<int> posterCounts(candidateCount), lowerBounds(candidateCount), upperBounds(candidateCount);
        vector<vector<int>> allCaps(candidateCount);
        for (int i = 0; i < candidateCount; i++) {
            cin >> posterCounts[i] >> lowerBounds[i] >> upperBounds[i];
            allCaps[i].resize(posterCounts[i]);
            for (int j = 0; j < posterCounts[i]; j++) cin >> allCaps[i][j];
        }
        int queryCount;
        cin >> queryCount;
        vector<int> queries(queryCount);
        int maxQuery = 0;
        for (int i = 0; i < queryCount; i++) {
            cin >> queries[i];
            maxQuery = max(maxQuery, queries[i]);
        }
        priority_queue<vector<int>, vector<vector<int>>, PolyCompare> polyQueue;
        for (int i = 0; i < candidateCount; i++)
            polyQueue.push(buildCandidatePoly(posterCounts[i], lowerBounds[i], upperBounds[i], allCaps[i], maxQuery));
        while (polyQueue.size() > 1) {
            vector<int> first = polyQueue.top();
            polyQueue.pop();
            vector<int> second = polyQueue.top();
            polyQueue.pop();
            polyQueue.push(multiplyPoly(first, second, maxQuery));
        }
        vector<int> answer = polyQueue.top();
        cout << "Case #" << testCase << ":\n";
        for (int i = 0; i < queryCount; i++) {
            int value = queries[i] < (int)answer.size() ? answer[queries[i]] : 0;
            cout << "Query " << i + 1 << ": " << value << "\n";
        }
        cout << "\n";
    }
    return 0;
}
