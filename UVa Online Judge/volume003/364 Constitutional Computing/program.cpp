// Constitutional Computing
// UVa ID: 364
// Verdict: Accepted
// Submission Date: 2026-06-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct State {
    string name;
    long long pop;
};

// Hamilton 方法（最大余数法）
vector<int> hamilton(const vector<State>& states, int H) {
    int n = (int)states.size();
    long long total = 0;
    for (auto& s : states) total += s.pop;
    vector<int> reps(n);
    int sum = 0;
    vector<long long> rem(n);
    for (int i = 0; i < n; ++i) {
        long long prod = states[i].pop * H;
        long long q = prod / total;          // 整数部分
        rem[i] = prod % total;               // 余数（小数部分的分母固定为 total）
        reps[i] = (int)q;
        if (reps[i] < 1) reps[i] = 1;
        sum += reps[i];
    }
    int left = H - sum;
    vector<int> idx;
    for (int i = 0; i < n; ++i)
        if (states[i].pop * H >= total) idx.push_back(i);   // 真实配额 >= 1
    sort(idx.begin(), idx.end(), [&](int a, int b) {
        if (rem[a] != rem[b]) return rem[a] > rem[b];
        return a < b;
    });
    for (int i = 0; i < left && i < (int)idx.size(); ++i)
        reps[idx[i]]++;
    return reps;
}

// 通用除数法（优先队列模拟）
vector<int> divisorMethod(const vector<State>& states, int H, function<long long(int)> denom) {
    int n = (int)states.size();
    vector<int> reps(n, 1);
    if (H == n) return reps;
    priority_queue<pair<long double, int>> pq;
    for (int i = 0; i < n; ++i) {
        long double val = (long double)states[i].pop / denom(reps[i]);
        pq.push({val, i});
    }
    int remain = H - n;
    while (remain > 0) {
        while (true) {
            auto cur = pq.top(); pq.pop();
            int i = cur.second;
            long double curVal = (long double)states[i].pop / denom(reps[i]);
            if (fabsl(cur.first - curVal) < 1e-12L) {   // 有效元素
                reps[i]++;
                long double newVal = (long double)states[i].pop / denom(reps[i]);
                pq.push({newVal, i});
                remain--;
                break;
            }
            // 否则丢弃过时的旧值
        }
    }
    return reps;
}

// Jefferson：分母 = rep + 1
vector<int> jefferson(const vector<State>& states, int H) {
    return divisorMethod(states, H, [](int rep) { return rep + 1; });
}

// Adams：分母 = rep
vector<int> adams(const vector<State>& states, int H) {
    return divisorMethod(states, H, [](int rep) { return rep; });
}

// Webster：分母 = 2 * rep + 1
vector<int> webster(const vector<State>& states, int H) {
    return divisorMethod(states, H, [](int rep) { return 2LL * rep + 1; });
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int dataset = 1;
    int n;
    while (cin >> n && n != 0) {
        vector<State> states(n);
        for (int i = 0; i < n; ++i)
            cin >> states[i].name >> states[i].pop;

        cout << "Data set " << dataset << ":\n";
        int H;
        while (cin >> H && H != 0) {
            vector<int> h = hamilton(states, H);
            vector<int> j = jefferson(states, H);
            vector<int> a = adams(states, H);
            vector<int> w = webster(states, H);

            cout << "For " << H << " representatives:\n";
            for (int i = 0; i < n; ++i) {
                int vals[4] = {h[i], j[i], a[i], w[i]};
                int mx = vals[0], mn = vals[0];
                for (int k = 1; k < 4; ++k) {
                    if (vals[k] > mx) mx = vals[k];
                    if (vals[k] < mn) mn = vals[k];
                }
                vector<string> methods;
                if (mx != mn) {   // 存在某个方法严格大于其他方法
                    if (vals[0] == mx) methods.push_back("Hamilton");
                    if (vals[1] == mx) methods.push_back("Jefferson");
                    if (vals[2] == mx) methods.push_back("Adams");
                    if (vals[3] == mx) methods.push_back("Webster");
                }

                cout << states[i].name << " is favored by ";
                if (methods.empty()) {
                    cout << "no method.\n";
                } else {
                    for (size_t k = 0; k < methods.size(); ++k) {
                        if (k > 0) cout << " and ";
                        cout << methods[k];
                    }
                    cout << ".\n";
                }
            }
            cout << '\n';   // 每个代表数后空一行
        }
        dataset++;
    }
    return 0;
}
