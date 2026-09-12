#include <bits/stdc++.h>
using namespace std;

long long solveCase(int l, int w, const vector<pair<int, int>>& trees) {
    vector<int> ys;
    ys.push_back(0);
    ys.push_back(w);
    for (const auto& tree : trees)
        ys.push_back(tree.second);
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    long long ans = 0;
    int k = ys.size();
    for (int i = 0; i < k; i++) {
        for (int j = i + 1; j < k; j++) {
            vector<int> xs;
            for (const auto& tree : trees) {
                if (tree.second > ys[i] && tree.second < ys[j])
                    xs.push_back(tree.first);
            }
            sort(xs.begin(), xs.end());
            int lastX = 0;
            long long maxWidth = 0;
            for (int x : xs) {
                maxWidth = max(maxWidth, (long long)x - lastX);
                lastX = x;
            }
            maxWidth = max(maxWidth, (long long)l - lastX);
            ans = max(ans, maxWidth * (ys[j] - ys[i]));
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, caseNo = 1;
    cin >> t;
    while (t--) {
        int l, w, n;
        cin >> l >> w >> n;
        vector<pair<int, int>> trees(n);
        for (auto& tree : trees)
            cin >> tree.first >> tree.second;
        cout << "Case " << caseNo++ << ": " << solveCase(l, w, trees) << '\n';
    }
    return 0;
}
