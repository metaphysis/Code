#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;

int n, m, blockSize;
vector<int> data;          // 1-based 压缩值
int bit[MAXN];             // 树状数组
long long currentAnswer;
long long answers[MAXN];

struct Query {
    int l, r, id;
    bool operator<(const Query& o) const {
        int ba = l / blockSize, bb = o.l / blockSize;
        if (ba != bb) return ba < bb;
        return (ba & 1) ? r > o.r : r < o.r;   // 奇偶优化
    }
} queries[MAXN];

void updateBit(int idx, int delta) {
    for (; idx <= n; idx += idx & -idx)
        bit[idx] += delta;
}

int queryBit(int idx) {
    int sum = 0;
    for (; idx > 0; idx -= idx & -idx)
        sum += bit[idx];
    return sum;
}

// 右端点扩展：新元素 a[pos] 的逆序对贡献 = 已有元素中严格大于 a[pos] 的个数
void addRight(int pos) {
    int val = data[pos];
    currentAnswer += queryBit(n) - queryBit(val);
    updateBit(val, 1);
}

// 左端点扩展：新元素 a[pos] 的逆序对贡献 = 已有元素中严格小于 a[pos] 的个数
void addLeft(int pos) {
    int val = data[pos];
    currentAnswer += queryBit(val - 1);
    updateBit(val, 1);
}

// 右端点收缩：先移除 a[pos]，再统计剩余元素中严格大于 a[pos] 的个数
void removeRight(int pos) {
    int val = data[pos];
    updateBit(val, -1);
    currentAnswer -= queryBit(n) - queryBit(val);
}

// 左端点收缩：先移除 a[pos]，再统计剩余元素中严格小于 a[pos] 的个数
void removeLeft(int pos) {
    int val = data[pos];
    updateBit(val, -1);
    currentAnswer -= queryBit(val - 1);
}

void solve(int cnt_queries) {
    sort(queries, queries + cnt_queries);
    fill(bit, bit + n + 2, 0);
    currentAnswer = 0;

    int curL = 0, curR = -1;   // 空区间
    for (int i = 0; i < cnt_queries; ++i) {
        auto& q = queries[i];
        // 左端点变化
        while (curL > q.l) addLeft(--curL);
        while (curL < q.l) removeLeft(curL++);
        // 右端点变化
        while (curR < q.r) addRight(++curR);
        while (curR > q.r) removeRight(curR--);
        answers[q.id] = currentAnswer;
    }
}

// ==================== 暴力验证 ====================
long long bruteForce(int l, int r) {
    long long cnt = 0;
    for (int i = l; i <= r; ++i)
        for (int j = i + 1; j <= r; ++j)
            if (data[i] > data[j]) ++cnt;
    return cnt;
}

bool runTests() {
    mt19937 rng((unsigned int)time(NULL));
    const int TC = 2000;

    for (int tc = 1; tc <= TC; ++tc) {
        n = (int)(rng() % 100) + 1;
        m = (int)(rng() % 100) + 1;

        vector<int> a(n);
        for (int i = 0; i < n; ++i)
            a[i] = (int)(rng() % 21) - 10;   // 含负数，测试离散化

        // 坐标压缩，1-based 供 bit 使用
        vector<int> cs = a;
        sort(cs.begin(), cs.end());
        cs.erase(unique(cs.begin(), cs.end()), cs.end());
        data.assign(n, 0);
        for (int i = 0; i < n; ++i)
            data[i] = lower_bound(cs.begin(), cs.end(), a[i]) - cs.begin() + 1;

        blockSize = max(1, (int)sqrt(n));

        vector<int> qL(m), qR(m);
        vector<long long> expected(m);
        for (int i = 0; i < m; ++i) {
            int l = (int)(rng() % n);
            int r = (int)(rng() % n);
            if (l > r) swap(l, r);
            qL[i] = l; qR[i] = r;
            queries[i] = {l, r, i};
            expected[i] = bruteForce(l, r);
        }

        solve(m);

        for (int i = 0; i < m; ++i) {
            if (answers[i] != expected[i]) {
                cerr << "Test failed tc=" << tc << "\n";
                cerr << "n=" << n << " m=" << m << "\n";
                cerr << "arr: ";
                for (auto x : a) cerr << x << " ";
                cerr << "\n";
                cerr << "q[" << i << "] l=" << qL[i] << " r=" << qR[i]
                     << " expected=" << expected[i]
                     << " got=" << answers[i] << "\n";
                return false;
            }
        }
    }

    cout << "All " << TC << " random tests passed.\n";
    return true;
}

#define DEBUG

int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    #ifdef DEBUG
        return runTests() ? 0 : 1;
    #endif

    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    // 坐标压缩
    vector<int> cs = a;
    sort(cs.begin(), cs.end());
    cs.erase(unique(cs.begin(), cs.end()), cs.end());
    data.assign(n, 0);
    for (int i = 0; i < n; ++i)
        data[i] = lower_bound(cs.begin(), cs.end(), a[i]) - cs.begin() + 1;

    blockSize = max(1, (int)sqrt(n));

    for (int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        // 假设查询输入为 1-based，转 0-based
        queries[i] = {l - 1, r - 1, i};
    }

    solve(m);

    for (int i = 0; i < m; ++i) cout << answers[i] << "\n";
    return 0;
}
