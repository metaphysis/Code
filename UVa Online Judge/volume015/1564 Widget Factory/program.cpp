// Widget Factory
// UVa ID: 1564
// Verdict: Accepted
// Submission Date: 2026-01-09
// UVa Run Time: 0.210s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MOD = 7;
const int MIN_DAY = 3;
const int MAX_DAY = 9;

// 将星期字符串转换为数字（0-6）
int dayToInt(const string& s) {
    if (s == "MON") return 0;
    if (s == "TUE") return 1;
    if (s == "WED") return 2;
    if (s == "THU") return 3;
    if (s == "FRI") return 4;
    if (s == "SAT") return 5;
    return 6;
}

// 求模 MOD 下的逆元，由于 MOD=7 是素数，直接枚举即可
int inv(int a) {
    for (int i = 0; i < MOD; i++) if ((a * i) % MOD == 1) return i;
    return 0;
}

// 高斯消元求解模线性方程组，返回：0无解，1唯一解，2多解
int gauss(vector<vector<int>>& a, vector<int>& ans, int n, int m) {
    int row = 0;
    vector<int> where(m, -1);
    
    // 消元过程
    for (int col = 0; col < m && row < n; col++) {
        // 选择主元行
        int sel = row;
        for (int i = row; i < n; i++) if (a[i][col] > a[sel][col]) sel = i;
        if (a[sel][col] == 0) continue; // 该列全零，跳过（自由变量）
        // 交换到当前行
        for (int j = col; j <= m; j++) swap(a[sel][j], a[row][j]);
        where[col] = row; // 记录变量 col 所在的行
        
        // 将主元系数化为 1
        int invVal = inv(a[row][col]);
        for (int j = col; j <= m; j++) a[row][j] = a[row][j] * invVal % MOD;
        
        // 消去其他行的当前列
        for (int i = 0; i < n; i++) if (i != row) {
            int c = a[i][col];
            if (c == 0) continue;
            for (int j = col; j <= m; j++) {
                a[i][j] = (a[i][j] - c * a[row][j]) % MOD;
                if (a[i][j] < 0) a[i][j] += MOD;
            }
        }
        row++;
    }
    
    // 初始化解向量
    ans.assign(m, 0);
    for (int i = 0; i < m; i++) if (where[i] != -1) 
        ans[i] = a[where[i]][m] * inv(a[where[i]][i]) % MOD;
    
    // 验证解是否满足所有方程
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = 0; j < m; j++) sum = (sum + a[i][j] * ans[j]) % MOD;
        if (sum != a[i][m]) return 0; // 无解
    }
    
    // 检查是否有自由变量
    for (int i = 0; i < m; i++) if (where[i] == -1) return 2; // 多解
    
    return 1; // 唯一解
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    while (cin >> n >> m, n || m) {
        // 增广矩阵：m 行，n 列系数 + 1 列常数
        vector<vector<int>> a(m, vector<int>(n + 1, 0));
        
        for (int i = 0; i < m; i++) {
            int k; string s, t;
            cin >> k >> s >> t;
            int start = dayToInt(s), end = dayToInt(t);
            // 计算右侧常数：经过的天数模 7
            a[i][n] = (end - start + 8) % MOD; // +8 等价于 +1 mod 7
            
            // 统计每种小部件的制造次数（模 7）
            vector<int> cnt(n, 0);
            for (int j = 0; j < k; j++) {
                int x; cin >> x;
                cnt[x - 1]++;
            }
            for (int j = 0; j < n; j++) a[i][j] = cnt[j] % MOD;
        }
        
        vector<int> ans(n);
        int res = gauss(a, ans, m, n);
        
        if (res == 0) {
            // 无解
            cout << "Inconsistent data.\n";
        } else if (res == 2) {
            // 多解
            cout << "Multiple solutions.\n";
        } else {
            // 唯一解，将模 7 值转换为 3-9 之间的天数
            bool valid = true;
            for (int i = 0; i < n; i++) {
                int val = ans[i];
                bool found = false;
                for (int d = MIN_DAY; d <= MAX_DAY; d++) {
                    if (d % MOD == val) {
                        ans[i] = d;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    valid = false;
                    break;
                }
            }
            
            if (!valid) {
                cout << "Inconsistent data.\n";
            } else {
                for (int i = 0; i < n; i++) {
                    if (i) cout << " ";
                    cout << ans[i];
                }
                cout << "\n";
            }
        }
    }
    
    return 0;
}
