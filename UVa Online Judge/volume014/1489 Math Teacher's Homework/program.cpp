#include <bits/stdc++.h>  
using namespace std;  
  
typedef long long ll;  
const int maxN = 55;  
const ll mod = 1000000003LL;  
ll dp[maxN][maxN], bits[31], arr[maxN], n, k;  
  
void addMod(ll &x, ll y) {  
    x += y;  
    if (x >= mod) x %= mod;  
}  
  
ll getRight(int id, int pos) {  
    if (pos == 0) return 0;  
    return arr[id] & (bits[pos] - 1);  
}  
  
ll solveDp(int pos, int id, int need, int cnt) {  
    memset(dp, 0, sizeof(dp));  
    dp[0][0] = 1;  
    for (int i = 1; i <= n; i++) {  
        for (int j = 0; j <= cnt; j++) {  
            if (arr[i] & bits[pos]) {  
                if (i == id) addMod(dp[i][j], dp[i - 1][j]);  
                else {  
                    if (j >= 1) addMod(dp[i][j], dp[i - 1][j - 1] * (getRight(i, pos) + 1));  
                    if (i > id) addMod(dp[i][j], dp[i - 1][j] * bits[pos]);  
                }  
            } else addMod(dp[i][j], dp[i - 1][j] * (getRight(i, pos) + 1));  
        }  
    }  
    ll ret = 0;  
    for (int i = 0; i <= cnt; i++)  
        if ((i & 1) == need) addMod(ret, dp[n][i]);  
    return ret;  
}  
  
ll dfs(int pos) {  
    if (pos == -1) return 1;  
    ll ret = 0;  
    int cnt = 0, need = (k & bits[pos]) >> pos;  
    for (int i = 1; i <= n; i++)  
        if (arr[i] & bits[pos]) cnt++;  
    if ((cnt & 1) == need) addMod(ret, dfs(pos - 1));  
    for (int i = 1; i <= n; i++)  
        if (arr[i] & bits[pos]) addMod(ret, solveDp(pos, i, need, cnt));  
    return ret;  
}  
  
int main() {  
    ios::sync_with_stdio(false);  
    cin.tie(nullptr);  
    for (int i = 0; i <= 30; i++) bits[i] = 1LL << i;  
    while (cin >> n >> k) {  
        if (!n && !k) break;  
        for (int i = 1; i <= n; i++) cin >> arr[i];  
        cout << dfs(30) % mod << '\n';  
    }  
    return 0;  
}
