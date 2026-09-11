// Strange Research
// UVa ID: 12055
// Verdict: Accepted
// Submission Date: 2026-07-31
// UVa Run Time: 0.230s

#include <bits/stdc++.h>
using namespace std;

struct Info {
    int count;
    string mn, mx;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    unordered_map<string, Info> mp;
    mp.reserve(N * 2);
    for (int i = 0; i < N; ++i) {
        string w;
        cin >> w;
        int len = (int)w.size();
        string mid = (len > 2) ? w.substr(1, len - 2) : "";
        sort(mid.begin(), mid.end());
        string key = to_string(len) + w[0] + w[len - 1] + mid;
        auto it = mp.find(key);
        if (it == mp.end()) {
            Info info;
            info.count = 1;
            info.mn = w;
            info.mx = w;
            mp.emplace(key, info);
        } else {
            ++it->second.count;
            if (w < it->second.mn) it->second.mn = w;
            if (w > it->second.mx) it->second.mx = w;
        }
    }
    int Q;
    cin >> Q;
    for (int i = 0; i < Q; ++i) {
        string q;
        cin >> q;
        int len = (int)q.size();
        string mid = (len > 2) ? q.substr(1, len - 2) : "";
        sort(mid.begin(), mid.end());
        string key = to_string(len) + q[0] + q[len - 1] + mid;
        auto it = mp.find(key);
        if (it == mp.end()) {
            cout << "0\n";
        } else {
            cout << it->second.count << " " << it->second.mn << " " << it->second.mx << "\n";
        }
    }
    return 0;
}
