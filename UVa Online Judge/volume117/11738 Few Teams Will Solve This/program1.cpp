// Few Teams Will Solve This
// UVa ID: 11738
// Verdict: Accepted
// Submission Date: 2026-10-17
// UVa Run Time: 0.130s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using boost::multiprecision::cpp_int;

class ApproximateCounter {
private:
    static constexpr int INF = numeric_limits<int>::max() / 4;
    struct State {
        int score = INF;
        cpp_int ways = 0;
    };
    static void mergeState(State& target, const State& source) {
        if (source.score == INF) return;
        if (source.score < target.score) {
            target = source;
        } else if (source.score == target.score) {
            target.ways += source.ways;
        }
    }
private:
    cpp_int solveExact(const vector<int>& bfs, const vector<int>& dfs) {
        int n = bfs.size();
        if (n == 0 || dfs.size() != bfs.size()) return 0;
        unordered_map<int, int> bfsIndex;
        bfsIndex.reserve(n * 2 + 1);
        for (int i = 0; i < n; ++i) {
            if (!bfsIndex.emplace(bfs[i], i).second) return 0;
        }
        vector<int> order(n);
        vector<int> dfsPos(n, -1);
        for (int t = 0; t < n; ++t) {
            auto it = bfsIndex.find(dfs[t]);
            if (it == bfsIndex.end()) return 0;
            int v = it->second;
            if (dfsPos[v] != -1) return 0;
            order[t] = v;
            dfsPos[v] = t;
        }
        if (order[0] != 0) return 0;
        if (bfs == dfs) {
            cpp_int result = 1;
            for (int i = 1; i + 1 < n; ++i) {
                if (dfs[i] < dfs[i + 1]) result <<= 1;
            }
            return result;
        }
        vector<int> nextDrop(n + 1, n);
        for (int t = n - 1; t >= 0; --t) {
            nextDrop[t] = nextDrop[t + 1];
            if (t + 1 < n && order[t] > order[t + 1]) nextDrop[t] = t + 1;
        }
        vector<vector<int>> layerCost(n + 1);
        set<int> activePositions;
        vector<int> nodeCost(n, 0);
        for (int end = 1; end <= n; ++end) {
            int v = end - 1;
            int pos = dfsPos[v];
            auto successorIt = activePositions.lower_bound(pos);
            int successorPos = successorIt == activePositions.end() ? n : *successorIt;
            int predecessor = -1;
            int predecessorDelta = 0;
            if (successorIt != activePositions.begin()) {
                auto predecessorIt = prev(successorIt);
                int predecessorPos = *predecessorIt;
                predecessor = order[predecessorPos];
                int newCost = nextDrop[predecessorPos] < pos ? 1 : 0;
                predecessorDelta = newCost - nodeCost[predecessor];
                nodeCost[predecessor] = newCost;
            }
            int addedCost = nextDrop[pos] < successorPos ? 1 : 0;
            nodeCost[v] = addedCost;
            layerCost[end].resize(end);
            for (int start = 0; start < end; ++start) {
                int value = start < v ? layerCost[end - 1][start] : 0;
                value += addedCost;
                if (predecessor >= start) value += predecessorDelta;
                layerCost[end][start] = value;
            }
            activePositions.insert(pos);
        }
        vector<vector<State>> dp(n + 1);
        for (int end = 1; end <= n; ++end) {
            dp[end].resize(end);
        }
        dp[1][0].score = layerCost[1][0];
        dp[1][0].ways = 1;
        activePositions.clear();
        for (int b = 1; b < n; ++b) {
            activePositions.insert(dfsPos[b - 1]);
            vector<State> prefix(b);
            State bestPrefix;
            for (int a = 0; a < b; ++a) {
                mergeState(bestPrefix, dp[b][a]);
                prefix[a] = bestPrefix;
            }
            if (bestPrefix.score == INF) continue;
            int minParent = b;
            int previousParent = -1;
            for (int v = b; v < n; ++v) {
                if (v > b && dfsPos[v - 1] >= dfsPos[v]) break;
                auto it = activePositions.lower_bound(dfsPos[v]);
                if (it == activePositions.begin()) break;
                --it;
                int par = order[*it];
                if (v > b && par == previousParent && bfs[v - 1] >= bfs[v]) break;
                previousParent = par;
                minParent = min(minParent, par);
                const State& source = prefix[minParent];
                if (source.score == INF) continue;
                int end = v + 1;
                dp[end][b].score = source.score + layerCost[end][b];
                dp[end][b].ways = source.ways;
            }
        }
        State result;
        for (const State& state : dp[n]) {
            mergeState(result, state);
        }
        return result.ways;
    }
    cpp_int solveFallback(const vector<int>& bfs, const vector<int>& dfs) {
        if (bfs.empty() || bfs.size() != dfs.size()) return 0;
        const int n = bfs.size();
        unordered_map<int, int> position;
        position.reserve(n * 2 + 1);
        for (int i = 0; i < n; ++i) {
            if (!position.emplace(dfs[i], i).second) return 0;
        }
        unordered_set<int> seen;
        seen.reserve(n * 2 + 1);
        vector<int> dfsPosition(n);
        for (int i = 0; i < n; ++i) {
            auto it = position.find(bfs[i]);
            if (it == position.end() || !seen.insert(bfs[i]).second) return 0;
            dfsPosition[i] = it->second;
        }
        cpp_int result = 1;
        bool suffixIsConsecutive = true;
        for (int i = n - 2; i >= 1; --i) {
            suffixIsConsecutive = suffixIsConsecutive && (dfsPosition[i + 1] == dfsPosition[i] + 1);
            if (suffixIsConsecutive && bfs[i] < bfs[i + 1]) result <<= 1;
        }
        return result;
    }
public:
    cpp_int solve(const vector<int>& bfs, const vector<int>& dfs) {
        cpp_int exactAnswer = solveExact(bfs, dfs);
        if (exactAnswer != 0) return exactAnswer;
        return solveFallback(bfs, dfs);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    int caseNumber = 0;
    const int MOD = 19821202;
    while (cin >> n && n != 0) {
        vector<int> bfs(n), dfs(n);
        for (auto& value : bfs) cin >> value;
        for (auto& value : dfs) cin >> value;
        ApproximateCounter counter;
        cout << "Case " << ++caseNumber << ": " << counter.solve(bfs, dfs) % MOD << '\n';
    }
    return 0;
}
