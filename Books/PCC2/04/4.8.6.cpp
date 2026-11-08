#include <bits/stdc++.h>
using namespace std;

class FractionalCascading {
private:
    struct Entry {
        // 当前增广元素的值；末尾虚拟位置的该字段不参与比较
        int value;
        // 原列表中第一个大于或等于 value 的元素序号，序号从 1 开始
        int answer;
        // 下一层中第一个大于或等于 value 的元素下标，下标从 0 开始
        int down;
    };
    vector<vector<Entry> > layers;
public:
    explicit FractionalCascading(const vector<vector<int>>& lists) {
        int k = lists.size();
        layers.resize(k);
        for (int i = k - 1; i >= 0; --i) {
            const vector<int>& original = lists[i];
            int n = original.size();
            int nextSize = i + 1 < k ? layers[i + 1].size() - 1 : 0;
            vector<Entry>& current = layers[i];
            current.reserve(n + nextSize / 2 + 1);
            int originalPosition = 0;
            int sampledPosition = 1;
            // 采用从 0 开始的下标，因此下标 1、3、5……就是从 1 开始编号时的偶数位置
            // 将当前原列表与下一层的采样元素归并，保留重复值
            while (originalPosition < n || sampledPosition < nextSize) {
                bool takeOriginal = sampledPosition >= nextSize;
                if (!takeOriginal && originalPosition < n)
                    takeOriginal = original[originalPosition] <= layers[i + 1][sampledPosition].value;
                if (takeOriginal) {
                    current.push_back({original[originalPosition], 0, 0});
                    ++originalPosition;
                } else {
                    current.push_back({layers[i + 1][sampledPosition].value, 0, 0});
                    sampledPosition += 2;
                }
            }
            int currentSize = current.size();
            int originalLowerBound = 0;
            int nextLowerBound = 0;
            // 当前层按升序排列，因此两个 lower_bound 位置都只会向右移动。
            // 整个循环的总时间为 O(|A_i| + |L_i| + |A_{i+1}|)，无需逐元素二分
            for (int p = 0; p < currentSize; ++p) {
                int value = current[p].value;
                while (originalLowerBound < n &&
                    original[originalLowerBound] < value) ++originalLowerBound;
                current[p].answer = originalLowerBound + 1;
                if (i + 1 < k) {
                    while (nextLowerBound < nextSize &&
                        layers[i + 1][nextLowerBound].value < value) ++nextLowerBound;
                    current[p].down = nextLowerBound;
                }
            }
            // 额外保存一个末尾虚拟位置，表示当前层不存在大于或等于查询值的元素
            // 它的答案为 n + 1，桥指针指向下一层的末尾虚拟位置
            // 这里的 value 仅用于占位，不会参与二分查找或修正比较
            current.push_back({0, n + 1, nextSize});
        }
    }

    vector<int> query(int x) const {
        int k = layers.size();
        vector<int> result(k);
        if (k == 0) return result;
        int left = 0;
        int right = layers[0].size() - 1;
        // 搜索区间只包含真实元素，right 的初值同时也是末尾虚拟位置的下标
        // 如果所有真实元素都小于 x，二分结果自然就是末尾虚拟位置
        while (left < right) {
            int middle = left + (right - left) / 2;
            if (layers[0][middle].value < x) left = middle + 1;
            else right = middle;
        }
        int position = left;
        for (int i = 0; i < k; ++i) {
            result[i] = layers[i][position].answer;
            if (i + 1 == k) break;
            int nextPosition = layers[i][position].down;
            // 桥指针指向下一层中第一个大于或等于当前元素值的位置。
            // 查询值与当前元素值之间不可能出现被采样的元素，否则当前层的二分位置会更靠前。
            // 下一层每隔一个元素就采样一次，因此桥指针之前最多只有一个元素需要检查。
            // 当前层位置为末尾虚拟位置时，同样最多遗漏下一层末尾的一个未采样元素。
            if (nextPosition > 0 && layers[i + 1][nextPosition - 1].value >= x) --nextPosition;
            position = nextPosition;
        }
        return result;
    }
};

// 朴素算法作为验证器：分别在每个原列表中执行一次标准库 lower_bound。
vector<int> bruteForce(const vector<vector<int> >& lists, int x) {
    vector<int> result(lists.size());
    for (size_t i = 0; i < lists.size(); ++i) result[i] = lower_bound(lists[i].begin(), lists[i].end(), x) - lists[i].begin() + 1;
    return result;
}

// 生成闭区间 [left, right] 中的随机整数，包括完整的 int 取值范围。
int randomInt(mt19937_64& engine, int left, int right) {
    uniform_int_distribution<int> distribution(left, right);
    return distribution(engine);
}

// 每次生成 k 个等长列表，长度均为 n；另外覆盖 k = 0 和 n = 0 的边界情况。
// 不同模式分别强调重复值、普通随机值、整数极值以及常量列表。
vector<vector<int> > generateLists(mt19937_64& engine, int caseNumber) {
    int k = randomInt(engine, 0, 20);
    int n = randomInt(engine, 0, 50);
    int mode = caseNumber % 5;
    int sharedValue = randomInt(engine, -3, 3);
    vector<vector<int> > lists(k, vector<int>(n));
    for (int i = 0; i < k; ++i) {
        int rowValue = randomInt(engine, -5, 5);
        for (int j = 0; j < n; ++j) {
            if (mode == 0) lists[i][j] = randomInt(engine, -3, 3);
            else if (mode == 1) lists[i][j] = randomInt(engine, -1000000, 1000000);
            else if (mode == 2) {
                int choice = randomInt(engine, 0, 3);
                if (choice == 0) lists[i][j] = numeric_limits<int>::min();
                else if (choice == 1) lists[i][j] = numeric_limits<int>::max();
                else lists[i][j] = randomInt(engine, -2, 2);
            } else if (mode == 3) lists[i][j] = sharedValue;
            else lists[i][j] = rowValue;
        }
        sort(lists[i].begin(), lists[i].end());
    }
    return lists;
}

void printVector(const vector<int>& values) {
    cout << "[";
    for (size_t i = 0; i < values.size(); ++i) {
        if (i != 0) cout << ", ";
        cout << values[i];
    }
    cout << "]";
}

// 对同一个查询同时运行两种算法；发现差异时输出完整输入，方便直接复现。
bool verifyQuery(const FractionalCascading& structure, const vector<vector<int> >& lists, int x, uint64_t seed, int caseNumber) {
    vector<int> actual = structure.query(x);
    vector<int> expected = bruteForce(lists, x);
    if (actual == expected) return true;
    cout << "验证失败\n";
    cout << "随机种子：" << seed << "\n";
    cout << "测试编号：" << caseNumber << "\n";
    cout << "查询值：" << x << "\n";
    for (size_t i = 0; i < lists.size(); ++i) {
        cout << "L" << i + 1 << " = ";
        printVector(lists[i]);
        cout << "\n";
    }
    cout << "分散层叠结果：";
    printVector(actual);
    cout << "\n";
    cout << "朴素算法结果：";
    printVector(expected);
    cout << "\n";
    return false;
}

int main(int argc, char* argv[]) {
    uint64_t seed = static_cast<uint64_t>(chrono::high_resolution_clock::now().time_since_epoch().count());
    int rounds = 3000;
    // 可选命令行参数：第一个参数为随机种子，第二个参数为随机测试轮数。
    if (argc >= 2) seed = static_cast<uint64_t>(strtoull(argv[1], nullptr, 10));
    if (argc >= 3) rounds = atoi(argv[2]);
    if (rounds < 0) rounds = 0;
    mt19937_64 engine(seed);
    cout << "随机种子：" << seed << "\n";
    vector<vector<int> > example = {
        {1, 4, 4, 10},
        {2, 4, 8, 12},
        {0, 5, 5, 9}
    };
    FractionalCascading exampleStructure(example);
    vector<int> exampleQueries = {4, 5, 13};
    for (size_t i = 0; i < exampleQueries.size(); ++i) {
        int x = exampleQueries[i];
        if (!verifyQuery(exampleStructure, example, x, seed, -1)) return 1;
        cout << "示例查询 x = " << x << "，结果为 ";
        printVector(exampleStructure.query(x));
        cout << "\n";
    }
    long long queryCount = 0;
    for (int caseNumber = 0; caseNumber < rounds; ++caseNumber) {
        vector<vector<int> > lists = generateLists(engine, caseNumber);
        FractionalCascading structure(lists);
        vector<int> queries;
        queries.push_back(numeric_limits<int>::min());
        queries.push_back(numeric_limits<int>::max());
        // 穷举一个小区间，重点验证重复值，以及恰好位于相邻值之间的查询。
        for (int x = -8; x <= 8; ++x) queries.push_back(x);
        // 检查所有原始元素及其相邻整数，覆盖每个 lower_bound 跳变位置。
        // 先判断边界，再执行加减，避免有符号整数溢出。
        for (size_t i = 0; i < lists.size(); ++i) {
            for (size_t j = 0; j < lists[i].size(); ++j) {
                int value = lists[i][j];
                queries.push_back(value);
                if (value > numeric_limits<int>::min()) queries.push_back(value - 1);
                if (value < numeric_limits<int>::max()) queries.push_back(value + 1);
            }
        }
        // 补充覆盖整个 int 取值范围的随机查询。
        for (int i = 0; i < 100; ++i) queries.push_back(randomInt(engine, numeric_limits<int>::min(), numeric_limits<int>::max()));
        sort(queries.begin(), queries.end());
        queries.erase(unique(queries.begin(), queries.end()), queries.end());
        for (size_t i = 0; i < queries.size(); ++i) {
            if (!verifyQuery(structure, lists, queries[i], seed, caseNumber)) return 1;
            ++queryCount;
        }
    }
    cout << "全部验证通过，共测试 " << rounds << " 组随机数据、" << queryCount << " 次随机数据查询。\n";
    return 0;
}
