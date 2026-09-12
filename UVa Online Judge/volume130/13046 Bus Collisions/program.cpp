#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> buildPath(const vector<pair<int, int>> &points) {
    vector<pair<int, int>> path;
    int n = points.size(), i;
    for (i = 0; i < n; i++) {
        int j = (i + 1) % n;
        int x = points[i].first, y = points[i].second;
        int nx = points[j].first, ny = points[j].second;
        int dx = (nx > x) - (nx < x), dy = (ny > y) - (ny < y);
        int len = abs(nx - x) + abs(ny - y), k;
        for (k = 0; k < len; k++) {
            path.push_back({x + dx * k, y + dy * k});
        }
    }
    return path;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, cs;
    cin >> t;
    for (cs = 1; cs <= t; cs++) {
        int n, m, i;
        cin >> n;
        vector<pair<int, int>> first(n);
        for (i = 0; i < n; i++) cin >> first[i].first >> first[i].second;
        cin >> m;
        vector<pair<int, int>> second(m);
        for (i = 0; i < m; i++) cin >> second[i].first >> second[i].second;
        vector<pair<int, int>> path1 = buildPath(first), path2 = buildPath(second);
        long long len1 = path1.size(), len2 = path2.size();
        long long period = len1 / __gcd(len1, len2) * len2;
        bool found = false;
        pair<int, int> answer;
        long long time;
        for (time = 0; time < period; time++) {
            if (path1[time % len1] == path2[time % len2]) {
                answer = path1[time % len1];
                found = true;
                break;
            }
        }
        cout << "Case " << cs << ": ";
        if (found) cout << answer.first << ' ' << answer.second << '\n';
        else cout << "No Collision\n";
    }
    return 0;
}
