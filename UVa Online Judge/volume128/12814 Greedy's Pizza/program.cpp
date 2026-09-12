#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<int> day(7);
    while (cin >> day[0]) {
        for (int i = 1; i < 7; i++) cin >> day[i];
        vector<double> prob(7, 0.0);
        double sum = 0.0;
        for (int i = 0; i < 7; i++) {
            if (day[i] == 0) continue;
            prob[(i + 1) % 7] += 0.6;
            prob[(i + 2) % 7] += 0.4;
            sum += 1.0;
        }
        cout << fixed << setprecision(5);
        for (int i = 0; i < 7; i++) {
            if (i > 0) cout << ' ';
            if (sum == 0.0) cout << 0.0;
            else cout << prob[i] / sum;
        }
        cout << '\n';
    }
    return 0;
}
