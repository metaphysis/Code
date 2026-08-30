#include <bits/stdc++.h>
using namespace std;

const int inf = -1000000000;

struct Tram {
    int left, right, len;
};

bool cmpTram(const Tram &a, const Tram &b) {
    if (a.left != b.left)
        return a.left < b.left;
    return a.right > b.right;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k, caseId = 0;
    while (cin >> n >> m >> k) {
        vector<int> x(n), y(n);
        for (int i = 0; i < n; i++)
            cin >> x[i] >> y[i];
        vector<Tram> trams;
        for (int i = 0; i < n; i++) {
            int maxHeight = 0;
            for (int j = i + 1; j < n; j++) {
                if (y[i] == y[j] && maxHeight < y[i])
                    trams.push_back({i, j, x[j] - x[i]});
                maxHeight = max(maxHeight, y[j]);
            }
        }
        sort(trams.begin(), trams.end(), cmpTram);
        int tramCount = trams.size();
        vector<int> parent(tramCount + 1, 0);
        vector<vector<int>> children(tramCount + 1);
        vector<int> stackNodes;
        for (int i = 0; i < tramCount; i++) {
            while (!stackNodes.empty()) {
                int top = stackNodes.back();
                if (trams[top].left <= trams[i].left && trams[i].right <= trams[top].right)
                    break;
                stackNodes.pop_back();
            }
            if (!stackNodes.empty())
                parent[i + 1] = stackNodes.back() + 1;
            children[parent[i + 1]].push_back(i + 1);
            stackNodes.push_back(i);
        }
        int cap = k - 1;
        vector<vector<vector<int>>> dp(tramCount + 1, vector<vector<int>>(cap + 1, vector<int>(m + 1, inf)));
        for (int v = tramCount; v >= 1; v--) {
            vector<vector<int>> skip(cap + 1, vector<int>(m + 1, inf));
            vector<vector<int>> take(cap + 1, vector<int>(m + 1, inf));
            for (int depth = 0; depth <= cap; depth++)
                skip[depth][0] = take[depth][0] = 0;
            for (int child : children[v]) {
                vector<vector<int>> nextSkip(cap + 1, vector<int>(m + 1, inf));
                vector<vector<int>> nextTake(cap + 1, vector<int>(m + 1, inf));
                for (int depth = 0; depth <= cap; depth++) {
                    for (int used = 0; used <= m; used++) {
                        if (skip[depth][used] == inf && take[depth][used] == inf)
                            continue;
                        for (int add = 0; used + add <= m; add++) {
                            if (skip[depth][used] != inf && dp[child][depth][add] != inf)
                                nextSkip[depth][used + add] = max(nextSkip[depth][used + add], skip[depth][used] + dp[child][depth][add]);
                            if (depth < cap && take[depth][used] != inf && dp[child][depth + 1][add] != inf)
                                nextTake[depth][used + add] = max(nextTake[depth][used + add], take[depth][used] + dp[child][depth + 1][add]);
                        }
                    }
                }
                skip.swap(nextSkip);
                take.swap(nextTake);
            }
            for (int depth = 0; depth <= cap; depth++) {
                for (int used = 0; used <= m; used++) {
                    dp[v][depth][used] = skip[depth][used];
                    if (depth < cap && used > 0 && take[depth][used - 1] != inf)
                        dp[v][depth][used] = max(dp[v][depth][used], take[depth][used - 1] + trams[v - 1].len);
                }
            }
        }
        vector<vector<int>> root(cap + 1, vector<int>(m + 1, inf));
        for (int depth = 0; depth <= cap; depth++)
            root[depth][0] = 0;
        for (int child : children[0]) {
            vector<vector<int>> nextRoot(cap + 1, vector<int>(m + 1, inf));
            for (int depth = 0; depth <= cap; depth++) {
                for (int used = 0; used <= m; used++) {
                    if (root[depth][used] == inf)
                        continue;
                    for (int add = 0; used + add <= m; add++)
                        if (dp[child][depth][add] != inf)
                            nextRoot[depth][used + add] = max(nextRoot[depth][used + add], root[depth][used] + dp[child][depth][add]);
                }
            }
            root.swap(nextRoot);
        }
        int answer = root[0][m];
        if (answer == inf)
            answer = -1;
        cout << "Case " << ++caseId << ": " << answer << '\n';
    }
    return 0;
}
