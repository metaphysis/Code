#include <bits/stdc++.h>
using namespace std;

// 回滚莫队：解决“容易添加、难以删除”的区间查询问题
class RollbackMo {
private:
    struct Query {
        int l, r, id;
        Query(int _l = 0, int _r = 0, int _id = 0) : l(_l), r(_r), id(_id) {}
    };

    int n, q, blockSize;
    vector<int> data;          // 离散化后的数组
    vector<Query> queries;     // 所有查询
    vector<int> answers;       // 每个查询的答案

    // 当前状态：右指针扩展后维护的信息
    vector<int> cnt;           // 每个离散化值的出现次数
    int currentMax;            // 当前右指针区间内的最大出现次数

    // 临时状态：左指针在块内移动时使用，查询后回滚
    vector<pair<int, int>> tempChanges; // (值, 修改前的计数)
    int tempMax;               // 加入临时部分后的最大出现次数

    // 永久添加：用于右指针单调右移
    void addElement(int pos) {
        int val = data[pos];
        ++cnt[val];
        currentMax = max(currentMax, cnt[val]);
    }

    // 临时添加：记录旧计数，便于回滚
    void addElementTemp(int pos) {
        int val = data[pos];
        tempChanges.emplace_back(val, cnt[val]);
        ++cnt[val];
        tempMax = max(tempMax, cnt[val]);
    }

    // 回滚临时修改，并恢复当前最大值为基准最大值
    void rollbackTemp(int baseMax) {
        // 注意：必须逆序恢复。同一个值可能被临时增加多次。
        for (int i = (int)tempChanges.size() - 1; i >= 0; --i) {
            int val = tempChanges[i].first;
            int oldCnt = tempChanges[i].second;
            cnt[val] = oldCnt;
        }
        tempChanges.clear();
        currentMax = baseMax;
    }

    // 短查询暴力计算：长度不超过一个块大小
    int bruteForce(int l, int r) const {
        if (l > r) return 0;
        unordered_map<int, int> freq;
        int mx = 0;
        for (int i = l; i <= r; ++i) {
            int val = data[i];
            int c = ++freq[val];
            mx = max(mx, c);
        }
        return mx;
    }

public:
    RollbackMo(int _n, int _q) : n(_n), q(_q) {
        data.resize(n);
        queries.resize(q);
        answers.resize(q);
        blockSize = max(1, (int)sqrt(n) + 1);
    }

    // 设置数组，并进行离散化
    void setArray(const vector<int>& input) {
        data = input;
        // 离散化
        vector<int> sorted = data;
        sort(sorted.begin(), sorted.end());
        sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
        for (int i = 0; i < n; ++i) 
            data[i] = lower_bound(sorted.begin(), sorted.end(), input[i]) - sorted.begin();
        // 计数数组大小为不同值的个数
        cnt.assign(sorted.size(), 0);
    }

    // 添加查询，查询下标从 0 开始，区间为 [l, r]
    void addQuery(int l, int r, int id) { queries[id] = Query(l, r, id); }

    void solve() {
        // 按左端点所在块排序；同一块内按右端点升序
        sort(queries.begin(), queries.end(), [&](const Query& a, const Query& b) {
            int blockA = a.l / blockSize;
            int blockB = b.l / blockSize;
            if (blockA != blockB) return blockA < blockB;
            return a.r < b.r;
        });
        currentMax = 0;
        int currentRight = -1;
        int currentBlock = -1;
        for (const auto& qu : queries) {
            int block = qu.l / blockSize;
            // 进入新的块，重置状态
            if (block != currentBlock) {
                fill(cnt.begin(), cnt.end(), 0);
                currentMax = 0;
                currentBlock = block;
                // 当前块的右端点
                int blockEnd = min(n, (block + 1) * blockSize) - 1;
                currentRight = blockEnd;
            }
            int blockEnd = min(n, (block + 1) * blockSize) - 1;
            // 如果查询右端点小于块右端点，无法利用右指针单调右移，
            // 直接暴力计算。长度不超过 blockSize。
            if (qu.r < blockEnd) {
                answers[qu.id] = bruteForce(qu.l, qu.r);
                continue;
            }
            // 右指针单调向右扩展，只增不删
            while (currentRight < qu.r) {
                ++currentRight;
                addElement(currentRight);
            }
            // 保存右指针扩展后的基准最大值
            int baseMax = currentMax;
            // 临时加入左指针到块右端点之间的元素
            tempMax = baseMax;
            tempChanges.clear();
            int leftPtr = blockEnd;
            while (leftPtr >= qu.l) {
                addElementTemp(leftPtr);
                --leftPtr;
            }
            // 此时 tempMax 就是区间 [qu.l, qu.r] 的答案
            answers[qu.id] = tempMax;
            // 回滚左指针造成的临时修改
            rollbackTemp(baseMax);
        }
    }

    vector<int> getAnswers() const { return answers; }
};

// 随机对拍测试：与暴力程序比较答案
bool runTests() {
    mt19937 rng(time(NULL));
    const int TEST_CASES = 3000;
    for (int tc = 1; tc <= TEST_CASES; ++tc) {
        int n = (int)(rng() % 40) + 1;
        int q = (int)(rng() % 40) + 1;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            a[i] = (int)(rng() % 21) - 10; // 包含负数，顺便测试离散化
        }
        RollbackMo mo(n, q);
        mo.setArray(a);
        vector<int> expected(q);
        vector<int> L(q), R(q);
        for (int i = 0; i < q; ++i) {
            int l = (int)(rng() % n);
            int r = (int)(rng() % n);
            if (l > r) swap(l, r);
            L[i] = l;
            R[i] = r;
            mo.addQuery(l, r, i);
            // 暴力计算答案
            unordered_map<int, int> freq;
            int mx = 0;
            for (int j = l; j <= r; ++j) {
                int c = ++freq[a[j]];
                mx = max(mx, c);
            }
            expected[i] = mx;
        }
        mo.solve();
        vector<int> got = mo.getAnswers();
        for (int i = 0; i < q; ++i) {
            if (got[i] != expected[i]) {
                cerr << "Test failed!\n";
                cerr << "tc = " << tc << ", n = " << n << ", q = " << q << "\n";
                cerr << "query id = " << i << ", L = " << L[i] << ", R = " << R[i] << "\n";
                cerr << "array = ";
                for (int x : a) cerr << x << " ";
                cerr << "\n";
                cerr << "expected = " << expected[i] << ", got = " << got[i] << "\n";
                return false;
            }
        }
    }
    cout << "All random tests passed.\n";
    return true;
}

#define DEBUG

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    #ifdef DEBUG
        return runTests() ? 0 : 1;
    #endif
    int n, q;
    if (!(cin >> n >> q)) return 0;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) cin >> arr[i];
    RollbackMo mo(n, q);
    mo.setArray(arr);
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        // 输入通常是 1-based，转换为 0-based
        mo.addQuery(l - 1, r - 1, i);
    }
    mo.solve();
    vector<int> answers = mo.getAnswers();
    for (int i = 0; i < q; ++i) cout << answers[i] << "\n";
    return 0;
}
