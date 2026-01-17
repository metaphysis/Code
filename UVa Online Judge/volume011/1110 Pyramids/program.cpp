// Pyramids
// UVa ID: 1110
// Verdict: Accepted
// Submission Date: 2026-01-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Pyramid {
    int cubes, base;
    char type;
    Pyramid(int c = 0, int b = 0, char t = 'H') : cubes(c), base(b), type(t) {}
    bool operator<(const Pyramid& other) const { return cubes > other.cubes; }
};

vector<Pyramid> allPyramids;
const int MAXC = 1000000, INF = 0x3f3f3f3f;
vector<Pyramid> best;
int minCount;

int highPyramidCubes(int base) { return base * (base + 1) * (2 * base + 1) / 6; }
int lowPyramidCubes(int base) { return base * (base + 1) * (base + 2) / 6; }

void initialize() {
    for (int base = 2; ; base++) {
        int cubesH = highPyramidCubes(base);
        if (cubesH <= MAXC) allPyramids.push_back(Pyramid(cubesH, base, 'H'));
        if (base >= 3) {
            int cubesL = lowPyramidCubes(base);
            if (cubesL > MAXC) break;
            allPyramids.push_back(Pyramid(cubesL, base, 'L'));
        }
    }
    sort(allPyramids.begin(), allPyramids.end());
}

// 比较两个序列的优劣
bool isBetter(const vector<Pyramid>& a, const vector<Pyramid>& b) {
    if (a.size() != b.size()) return a.size() < b.size();
    for (size_t i = 0; i < a.size(); i++)
        if (a[i].cubes != b[i].cubes)
            return a[i].cubes > b[i].cubes;
    return false;
}

// DFS搜索，带剪枝
void dfs(int remain, int startIdx, int depth, vector<Pyramid>& current) {
    // 剪枝1：当前序列已超过最优解的金字塔数量
    if (depth >= minCount) return;
    // 剪枝2：剩余立方体为0，找到可行解
    if (remain == 0) {
        if (depth < minCount || (depth == minCount && isBetter(current, best))) {
            minCount = depth;
            best = current;
            sort(best.begin(), best.end()); // 保持降序
        }
        return;
    }
    // 剪枝3：剩余立方体太小，无法用剩余金字塔填充
    if (startIdx >= allPyramids.size()) return;
    // 剪枝4：当前最大金字塔太大，直接跳过
    while (startIdx < allPyramids.size() && allPyramids[startIdx].cubes > remain)
        startIdx++;
    if (startIdx >= allPyramids.size()) return;
    // 剪枝5：即使使用最小的金字塔也无法在最小数量内填满
    // 估算最小可能金字塔数：使用当前最大的金字塔
    int maxCubes = allPyramids[startIdx].cubes;
    int minPossible = (remain + maxCubes - 1) / maxCubes; // 向上取整
    if (depth + minPossible >= minCount) return;
    // 尝试从startIdx开始选择金字塔
    for (int i = startIdx; i < allPyramids.size(); i++) {
        int cubes = allPyramids[i].cubes;
        if (cubes > remain) continue;
        // 剪枝6：避免重复选择相同底座和类型的金字塔
        bool duplicate = false;
        for (const Pyramid& p : current) {
            if (p.base == allPyramids[i].base && p.type == allPyramids[i].type) {
                duplicate = true;
                break;
            }
        }
        if (duplicate) continue;
        current.push_back(allPyramids[i]);
        dfs(remain - cubes, i + 1, depth + 1, current);
        current.pop_back();
        // 剪枝7：如果已经找到最优解，可以提前退出
        if (minCount == 1) return; // 单金字塔最优解
    }
}

int main() {
    initialize();
    int c, caseNo = 1;
    while (cin >> c && c) {
        cout << "Case " << caseNo++ << ": ";
        minCount = INF;
        best.clear();
        vector<Pyramid> current;
        // 使用DFS搜索更优解
        dfs(c, 0, 0, current);
        if (best.empty()) cout << "impossible\n";
        else {
            for (size_t i = 0; i < best.size(); i++) {
                if (i > 0) cout << ' ';
                cout << best[i].base << best[i].type;
            }
            cout << '\n';
        }
    }
    return 0;
}
