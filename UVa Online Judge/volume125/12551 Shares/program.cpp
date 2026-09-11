// Shares
// UVa ID: 12551
// Verdict: Accepted
// Submission Date: 2026-07-31
// UVa Run Time: 0.120s

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Item {
    ll cost;
    ll profit;
};

// 按性价比降序排序（profit/cost）
bool cmpItem(const Item &a, const Item &b) {
    // 交叉相乘避免浮点误差，使用 long double 防止溢出
    return (long double)a.profit / a.cost > (long double)b.profit / b.cost;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll C;
    int N, P;
    bool firstCase = true;

    while (cin >> C) {
        cin >> N >> P;
        vector<ll> a(N + 1), t(N + 1);
        for (int i = 1; i <= N; ++i) {
            cin >> a[i] >> t[i];
        }

        vector<Item> items;
        items.reserve(P);

        for (int i = 0; i < P; ++i) {
            int R;
            cin >> R;
            ll cost = 0, profit = 0;
            for (int j = 0; j < R; ++j) {
                int s, q;
                cin >> s >> q;
                cost += a[s] * (ll)q;
                profit += (t[s] - a[s]) * (ll)q;
            }
            // 只保留正利润的包（负利润不会选，零利润不影响结果）
            if (profit > 0) {
                items.push_back({cost, profit});
            }
        }

        // 如果所有包利润非正，直接输出0
        if (items.empty()) {
            if (!firstCase) cout << '\n';
            cout << 0 << '\n';
            firstCase = false;
            continue;
        }

        // 按性价比排序，使状态扩展更有效
        sort(items.begin(), items.end(), cmpItem);

        // states 存储帕累托前沿，按 cost 升序，profit 严格升序
        vector<pair<ll, ll>> states;
        states.reserve(1);
        states.push_back({0, 0});   // 初始状态：成本0，利润0

        for (const auto &item : items) {
            // 生成新状态：在当前状态上加上当前物品
            vector<pair<ll, ll>> newStates;
            newStates.reserve(states.size());
            for (const auto &st : states) {
                ll newCost = st.first + item.cost;
                if (newCost <= C) {   // 超过容量的状态后续不可能再选，直接丢弃
                    newStates.push_back({newCost, st.second + item.profit});
                }
            }

            // 归并 states 和 newStates（二者均按 cost 升序）
            vector<pair<ll, ll>> merged;
            merged.reserve(states.size() + newStates.size());
            size_t i = 0, j = 0;
            while (i < states.size() && j < newStates.size()) {
                if (states[i].first <= newStates[j].first) {
                    merged.push_back(states[i]);
                    ++i;
                } else {
                    merged.push_back(newStates[j]);
                    ++j;
                }
            }
            while (i < states.size()) {
                merged.push_back(states[i]);
                ++i;
            }
            while (j < newStates.size()) {
                merged.push_back(newStates[j]);
                ++j;
            }

            // 过滤被支配状态：维护当前最大利润，只保留 profit 严格递增的状态
            states.clear();
            ll maxProfit = -1;   // 因为 profit 非负，所以 -1 足够
            for (const auto &st : merged) {
                if (st.second > maxProfit) {
                    states.push_back(st);
                    maxProfit = st.second;
                }
            }
            // 若 states 为空（不会发生，因为 (0,0) 始终存在），但以防万一
            if (states.empty()) {
                states.push_back({0, 0});
            }
        }

        // 最终 states 的最后一个状态具有最大利润（因为 profit 严格升序且 cost 升序）
        ll answer = states.back().second;

        if (!firstCase) cout << '\n';
        cout << answer << '\n';
        firstCase = false;
    }

    return 0;
}
