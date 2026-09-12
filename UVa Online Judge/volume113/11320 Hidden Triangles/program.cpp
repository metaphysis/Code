#include <bits/stdc++.h>
using namespace std;

const int maxN = 20005;
long double harm[maxN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    for (int i = 1; i < maxN; i++)
        harm[i] = harm[i - 1] + 1.0L / i;
    int x1Down, x2Down, x1Up, x2Up, h;
    int caseId = 1;
    while (cin >> x1Down >> x2Down >> x1Up >> x2Up >> h) {
        if (x1Down == 0 && x2Down == 0 && x1Up == 0 && x2Up == 0 && h == 0)
            break;
        int n = x2Down - x1Down + 1, m = x2Up - x1Up + 1;
        long double sum = 0;
        for (int r = 1; r < n; r++) {
            long double part = (m + r) * (harm[r + m - 1] - harm[r]) - (m - 1);
            sum += (long double)(n - r) * r * part;
        }
        long double total = (long double)n * (n - 1) / 2 * m * (m - 1) / 2;
        long double answer = h * sum / total;
        cout << "Case " << caseId++ << ": ";
        cout << fixed << setprecision(6) << (double)answer << '\n';
    }
    return 0;
}
