#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        int n, m, baseSteps, oddSteps, evenSteps, answer = INT_MAX;
        cin >> n >> m;
        baseSteps = (n + m - 1) / m;
        if (n % 2 == m % 2) {
            oddSteps = baseSteps;
            if (oddSteps % 2 == 0) ++oddSteps;
            answer = oddSteps;
        }
        if (n % 2 == 0 && m < n) {
            evenSteps = max(baseSteps, (n + (n - m) - 1) / (n - m));
            if (evenSteps % 2 != 0) ++evenSteps;
            answer = min(answer, evenSteps);
        }
        if (answer == INT_MAX) cout << "IMPOSSIBLE\n";
        else cout << answer << '\n';
    }
    return 0;
}
