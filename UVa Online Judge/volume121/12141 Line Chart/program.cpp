// Line Chart
// UVa ID: 12141
// Verdict: Accepted
// Submission Date: 2025-11-11
// UVa Run Time: 0.890s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <stdio.h> 
#include <vector>
#include <string.h>
#include <algorithm>
#include <map>
using namespace std;

#define MAXN 10050
const int MOD = 1000000;

int U[64][3][MAXN], D[64][3][MAXN];
int shift[64][3][MAXN];

int query(int A[], int idx) {
    int sum = 0;
    while (idx) 
        sum = (sum + A[idx]) % MOD, idx -= idx & -idx;
    return sum;
}

void update(int A[], int idx, int val, int L) {
    while (idx <= L) 
        A[idx] = (A[idx] + val) % MOD, idx += idx & -idx;
}

int main() {
    int T, n, k, x, y;
    int cases = 0;
    scanf("%d", &T);
    
    while (T--) {
        scanf("%d %d", &n, &k);
        vector<pair<int, int>> v;
        map<int, int> mp;
        
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &x, &y);
            mp[y] = 0;
            v.push_back(make_pair(x, y));
        }
        
        sort(v.begin(), v.end());
        int L = 1;
        for (auto &it : mp) it.second = L++;
        for (int i = 0; i < n; i++) 
            v[i].second = mp[v[i].second];
        
        memset(U, 0, sizeof(U));
        memset(D, 0, sizeof(D));
        memset(shift, 0, sizeof(shift));
        
        int used[10005] = {};
        for (int i = 0; i < n; i++) {
            if (!used[v[i].second]) {
                shift[0][0][v[i].second] = -1;
                used[v[i].second] = 1;
            }
        }
        
        update(U[0][1], 1, 1, L);
        update(U[0][2], 1, 1, L);
        
        int ans = 0;
        if (k == 0) ans++;
        
        for (int i = 0; i < n; i++) {
            int r = v[i].second;
            
            for (int j = 0; j <= k; j++) {
                int s0 = (query(U[j][0], r) + query(D[j][0], L - r - 1) - shift[j][0][r]) % MOD;
                int s1 = (query(U[j][1], r) + query(D[j][1], L - r - 1) - shift[j][1][r]) % MOD;
                int s2 = (query(U[j][2], r) + query(D[j][2], L - r - 1) - shift[j][2][r]) % MOD;
                
                shift[j][0][r] = (shift[j][0][r] + s0) % MOD;
                shift[j][1][r] = (shift[j][1][r] + s1) % MOD;
                shift[j][2][r] = (shift[j][2][r] + s2) % MOD;
                
                if (j == k) ans = (ans + s0) % MOD;
                
                if (s2) {
                    update(U[j][0], r + 1, s2, L);
                    update(U[j][2], r + 1, s2, L);
                    if (j + 1 <= k) 
                        update(U[j + 1][1], r + 1, s2, L);
                }
                
                if (s1) {
                    update(D[j][0], L - r, s1, L);
                    update(D[j][1], L - r, s1, L);
                    if (j + 1 <= k)
                        update(D[j + 1][2], L - r, s1, L);
                }
            }
        }
        
        printf("Case %d: %d\n", ++cases, (ans + MOD) % MOD);
    }
    return 0;
}
