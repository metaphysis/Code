#include <bits/stdc++.h>
using namespace std;

struct Point {
    int xp, ap, dp;
    bool operator < (const Point &other) const {
        if (xp != other.xp) return xp < other.xp;
        if (ap != other.ap) return ap < other.ap;
        return dp < other.dp;
    }
};

bool same(const Point &a, const Point &b) {
    return a.xp == b.xp && a.ap == b.ap && a.dp == b.dp;
}

vector<Point> getSums(const vector<Point> &task, const Point &target) {
    int n = task.size();
    vector<Point> res;
    for (int mask = 0; mask < (1 << n); mask++) {
        int xp = 0, ap = 0, dp = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                xp += task[i].xp;
                ap += task[i].ap;
                dp += task[i].dp;
            }
        }
        if (xp <= target.xp && ap <= target.ap && dp <= target.dp) res.push_back({xp, ap, dp});
    }
    return res;
}

bool solve() {
    Point target;
    int m;
    cin >> target.xp >> target.ap >> target.dp >> m;
    vector<Point> task[3];
    for (int i = 0; i < m; i++) {
        string name;
        Point cur;
        cin >> name >> cur.xp >> cur.ap >> cur.dp;
        task[i / 10].push_back(cur);
    }
    vector<Point> sum1 = getSums(task[0], target);
    vector<Point> sum2 = getSums(task[1], target);
    vector<Point> sum3 = getSums(task[2], target);
    vector<Point> sum12;
    sum12.reserve(sum1.size() * sum2.size());
    for (const Point &a : sum1) {
        for (const Point &b : sum2) {
            int xp = a.xp + b.xp, ap = a.ap + b.ap, dp = a.dp + b.dp;
            if (xp <= target.xp && ap <= target.ap && dp <= target.dp) sum12.push_back({xp, ap, dp});
        }
    }
    sort(sum12.begin(), sum12.end());
    for (const Point &cur : sum3) {
        Point need = {target.xp - cur.xp, target.ap - cur.ap, target.dp - cur.dp};
        vector<Point>::iterator it = lower_bound(sum12.begin(), sum12.end(), need);
        if (it != sum12.end() && same(*it, need)) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        if (solve()) cout << "POSSIBLE\n";
        else cout << "IMPOSSIBLE\n";
    }
    return 0;
}
