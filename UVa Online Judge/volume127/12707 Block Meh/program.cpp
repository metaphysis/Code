#include <bits/stdc++.h>
using namespace std;

struct Interval {
    int s, e;
};

bool cmp(const Interval& a, const Interval& b) {
    if (a.s != b.s) return a.s < b.s;
    return a.e < b.e;
}

int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        int N;
        cin >> N;
        vector<Interval> intervals(N);
        for (int i = 0; i < N; ++i) cin >> intervals[i].s >> intervals[i].e;
        sort(intervals.begin(), intervals.end(), cmp);
        vector<int> tail;
        for (const auto& in : intervals) {
            int x = in.e;
            auto it = upper_bound(tail.begin(), tail.end(), x);
            if (it == tail.end()) tail.push_back(x);
            else *it = x;
        }
        cout << "Case " << tc << ": " << tail.size() << "\n";
    }
    return 0;
}
