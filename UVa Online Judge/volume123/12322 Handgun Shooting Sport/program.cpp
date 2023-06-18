// Handgun Shooting Sport
// UVa ID: 12322
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n, x1, x2, y1, y2;
    while (cin >> n, n) {
        vector<pair<double, double>> interval;
        for (int i = 0; i < n; i++) {
            cin >> x1 >> y1 >> x2 >> y2;
            double l = atan2(y1, x1), r = atan2(y2, x2);
            if (l > r) swap(l, r);
            interval.push_back(make_pair(l, r));
        }
        sort(interval.begin(), interval.end());
        int r = 0;
        for (int i = 0, j; i < interval.size(); ) {
            r++;
            double rightmost = interval[i].second;
            for (j = i; j < interval.size() && interval[j].first <= rightmost; j++)
                rightmost = min(rightmost, interval[j].second);
            i = j;
        }
        cout << r << '\n';
    }
    return 0;
}
