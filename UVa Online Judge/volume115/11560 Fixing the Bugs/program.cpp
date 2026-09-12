#include <bits/stdc++.h>
using namespace std;

struct TryInfo {
    double prob;
    double gain;
    int id;
};

int bugCnt;
int hourCnt;
double failFac;
vector<TryInfo> tries;
unordered_map<unsigned long long, double> memo;

unsigned long long getKey(int mask, int rest, int cur) {
    return static_cast<unsigned long long>(mask) |
           (static_cast<unsigned long long>(rest) << 10) |
           (static_cast<unsigned long long>(cur) << 17);
}

double dfs(int mask, int rest, int cur) {
    if (rest == 0 || cur == static_cast<int>(tries.size())) return 0.0;
    unsigned long long key = getKey(mask, rest, cur);
    auto it = memo.find(key);
    if (it != memo.end()) return it->second;
    const TryInfo& now = tries[cur];
    int bit = 1 << now.id;
    if ((mask & bit) != 0) {
        double ans = dfs(mask, rest, cur + 1);
        memo[key] = ans;
        return ans;
    }
    double ans = now.gain + now.prob * dfs(mask | bit, rest - 1, cur + 1) +
                 (1.0 - now.prob) * dfs(mask, rest - 1, cur + 1);
    memo[key] = ans;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> bugCnt >> hourCnt >> failFac) {
        tries.clear();
        for (int i = 0; i < bugCnt; i++) {
            double initProb;
            int severity;
            cin >> initProb >> severity;
            double curProb = initProb;
            for (int j = 0; j < hourCnt; j++) {
                if (curProb > 0.0 && severity > 0) {
                    tries.push_back({curProb, curProb * severity, i});
                }
                curProb *= failFac;
            }
        }
        sort(tries.begin(), tries.end(), [](const TryInfo& a, const TryInfo& b) {
            return a.gain > b.gain;
        });
        memo.clear();
        memo.reserve(1 << 20);
        cout << fixed << setprecision(15) << dfs(0, hourCnt, 0) << '\n';
    }
    return 0;
}
