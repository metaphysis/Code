// Dragster
// UVa ID: 11680
// Verdict: Accepted
// Submission Date: 2025-11-24
// UVa Run Time: 0.130s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 605;
vector<int> children[MAXN];
double prob[MAXN][MAXN];
double winProb[MAXN][MAXN];
int n;

void dfs(int u) {
    if (u <= n) {
        for (int i = 1; i <= n; i++) winProb[u][i] = 0.0;
        winProb[u][u] = 1.0;
        return;
    }
    
    int left = children[u][0];
    int right = children[u][1];
    dfs(left);
    dfs(right);
    
    for (int i = 1; i <= n; i++) winProb[u][i] = 0.0;
    
    for (int i = 1; i <= n; i++) {
        if (winProb[left][i] > 0) {
            double sum = 0.0;
            for (int j = 1; j <= n; j++)
                sum += winProb[right][j] * prob[i][j];
            winProb[u][i] += winProb[left][i] * sum;
        }
    }
    
    for (int i = 1; i <= n; i++) {
        if (winProb[right][i] > 0) {
            double sum = 0.0;
            for (int j = 1; j <= n; j++)
                sum += winProb[left][j] * prob[i][j];
            winProb[u][i] += winProb[right][i] * sum;
        }
    }
}

int main() {
    while (cin >> n && n) {
        for (int i = 1; i <= 2 * n; i++) children[i].clear();
        
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                cin >> prob[i][j];
        
        vector<pair<int, int>> matches(n - 1);
        for (int i = 0; i < n - 1; i++)
            cin >> matches[i].first >> matches[i].second;
        
        vector<bool> hasParent(2 * n + 1, false);
        
        for (int i = 0; i < n - 1; i++) {
            int raceId = n + 1 + i;
            int left = matches[i].first;
            int right = matches[i].second;
            
            children[raceId].push_back(left);
            children[raceId].push_back(right);
            hasParent[left] = true;
            hasParent[right] = true;
        }
        
        int root = 0;
        for (int i = n + 1; i <= 2 * n - 1; i++) {
            if (!hasParent[i]) {
                root = i;
                break;
            }
        }
        
        dfs(root);
        cout << fixed << setprecision(6) << winProb[root][1] << endl;
    }
    return 0;
}
