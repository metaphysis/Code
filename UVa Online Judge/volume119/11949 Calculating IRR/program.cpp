#include <bits/stdc++.h>
using namespace std;

double calc(const vector<double>& a, double r) {
    double sum = 0.0, p = 1.0;
    for (int i = 1; i < (int)a.size(); i++) {
        p *= 1.0 + r;
        sum += a[i] / p;
    }
    return sum - a[0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for (int tc = 0; tc < n; tc++) {
        string s;
        getline(cin, s);
        while (s.empty()) getline(cin, s);
        stringstream ss(s);
        vector<double> a;
        double x, sum = 0.0;
        while (ss >> x) {
            a.push_back(x);
            if (a.size() > 1) sum += x;
        }
        double l, r;
        if (sum > a[0]) {
            l = 0.0;
            r = 1.0;
        } else {
            l = -0.999999999999;
            r = 0.0;
        }
        double fl = calc(a, l), mid = 0.0;
        for (int i = 0; i < 200; i++) {
            mid = (l + r) / 2.0;
            double fm = calc(a, mid);
            if (fl * fm <= 0.0) r = mid;
            else {
                l = mid;
                fl = fm;
            }
        }
        double ans = mid * 100.0;
        if (ans >= 0.0) ans = floor(ans * 1000.0 + 0.5) / 1000.0;
        else ans = ceil(ans * 1000.0 - 0.5) / 1000.0;
        if (fabs(ans) < 0.0005) ans = 0.0;
        cout << fixed << setprecision(3) << ans << "%\n";
    }
    return 0;
}
