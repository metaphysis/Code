#include <bits/stdc++.h>
using namespace std;

bool isNormal(const vector<int>& times) {
    int n = times.size(), i;
    long double sum = 0.0L, mean, median, variance = 0.0L, sigma, asymmetry;
    vector<int> sortedTimes = times;
    for (i = 0; i < n; i++) sum += times[i];
    mean = sum / n;
    sort(sortedTimes.begin(), sortedTimes.end());
    median = n % 2 == 1 ? sortedTimes[n / 2] : (sortedTimes[n / 2 - 1] + sortedTimes[n / 2]) / 2.0L;
    for (i = 0; i < n; i++) variance += (times[i] - mean) * (times[i] - mean);
    variance /= n;
    sigma = sqrt(variance);
    if (sigma == 0.0L) return false;
    asymmetry = fabsl(3.0L * (mean - median) / sigma);
    return asymmetry < 0.2L;
}

void runSimulation(int n, int d, const string& s, int x) {
    int i, t, player, startTime;
    vector<int> moveCount(n, 0), finishTime(n, -1), times(n);
    vector<pair<int, int>> ranking;
    for (t = 1; t <= static_cast<int>(s.size()); t++) {
        player = s[t - 1] - '1';
        startTime = 1 + player * x;
        if (t >= startTime && finishTime[player] == -1) {
            moveCount[player]++;
            if (moveCount[player] == d) finishTime[player] = t;
        }
    }
    for (i = 0; i < n; i++) {
        if (finishTime[i] == -1) {
            cout << "INVALID SIMULATION\n";
            return;
        }
        times[i] = finishTime[i] - (1 + i * x) + 1;
    }
    if (!isNormal(times)) {
        cout << "INVALID SIMULATION\n";
        return;
    }
    for (i = 0; i < n; i++) ranking.push_back({times[i], i + 1});
    sort(ranking.begin(), ranking.end());
    cout << "ORDER OF RACING:";
    for (i = 0; i < n; i++) cout << " " << ranking[i].second;
    cout << "\n";
}

void solve() {
    int testCount, n, d, q, i, j;
    string s;
    cin >> testCount;
    for (i = 0; i < testCount; i++) {
        cin >> n >> d >> s >> q;
        vector<int> xs(q);
        for (j = 0; j < q; j++) cin >> xs[j];
        for (j = 0; j < q; j++) runSimulation(n, d, s, xs[j]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
