// n Group k
// UVa ID: 10568
// Verdict: Accepted
// Submission Date: 2025-12-14
// UVa Run Time: 0.320s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using int128 = __int128;

// 预计算阶乘
vector<int128> factorial(31);
void precomputeFactorial() {
    factorial[0] = 1;
    for (int i = 1; i <= 30; ++i) factorial[i] = factorial[i - 1] * i;
}

// 组合数计算 C(n, k)
int128 combination(int n, int k) {
    if (k < 0 || k > n) return 0;
    if (k > n - k) k = n - k;
    
    int128 result = 1;
    for (int i = 1; i <= k; ++i) {
        result = result * (n - k + i) / i;
    }
    return result;
}

// 计算分组数
int128 countWays(int n, int k) {
    int groups = (n + k - 1) / k;  // ceil(n/k)
    int remainder = n % k;
    
    if (remainder == 0) {
        // 所有组大小都是k
        int128 ways = factorial[n];
        
        // 除以 (k!)^groups
        int128 kFactorial = factorial[k];
        for (int i = 0; i < groups; ++i) ways /= kFactorial;
        
        // 除以 groups! (组间无序)
        ways /= factorial[groups];
        return ways;
    } else {
        // 有一个大小为remainder的组，其余groups-1个组大小为k
        // 1. 选择remainder个学生给较小的组
        int128 ways = combination(n, remainder);
        
        // 2. 剩余学生分配到groups-1个大小为k的组中
        int remaining = n - remainder;
        ways *= factorial[remaining];
        
        // 除以 (k!)^(groups-1)
        int128 kFactorial = factorial[k];
        for (int i = 0; i < groups - 1; ++i) ways /= kFactorial;
        
        // 除以 (groups-1)! (大小为k的组之间无序)
        ways /= factorial[groups - 1];
        return ways;
    }
}

// 生成所有解的数据结构
vector<vector<string>> allSolutions;
string students;
int N, K;

void generateSolutions(int idx, vector<string>& currentGroups, vector<bool>& used, 
                       int currentGroupSize, int currentGroupStart) {
    if (idx == N) {
        int smallGroups = 0;
        for (const auto& group : currentGroups) {
            if ((int)group.size() < K) smallGroups++;
        }
        if (smallGroups <= 1) allSolutions.push_back(currentGroups);
        return;
    }

    // 尝试加入当前组
    if (!currentGroups.empty() && currentGroupSize < K) {
        for (int i = currentGroupStart; i < N; ++i) {
            if (!used[i]) {
                used[i] = true;
                currentGroups.back().push_back(students[i]);
                generateSolutions(idx + 1, currentGroups, used, currentGroupSize + 1, i + 1);
                currentGroups.back().pop_back();
                used[i] = false;
            }
        }
    }

    // 开始新组
    if ((int)currentGroups.size() < (N + K - 1) / K) {
        for (int i = 0; i < N; ++i) {
            if (!used[i]) {
                used[i] = true;
                currentGroups.push_back(string(1, students[i]));
                generateSolutions(idx + 1, currentGroups, used, 1, i + 1);
                currentGroups.pop_back();
                used[i] = false;
                break;
            }
        }
    }
}

// 将int128转换为字符串
string int128ToString(int128 n) {
    if (n == 0) return "0";
    
    string result = "";
    bool negative = false;
    
    if (n < 0) {
        negative = true;
        n = -n;
    }
    
    while (n > 0) {
        result = char('0' + (n % 10)) + result;
        n /= 10;
    }
    
    if (negative) result = "-" + result;
    return result;
}

int main() {
    precomputeFactorial();
    string query;
    
    while (cin >> query) {
        if (query == "END") break;
        
        int n, k;
        cin >> n >> k;
        
        if (query == "COUNT") {
            int128 result = countWays(n, k);
            cout << int128ToString(result) << endl;
        } 
        else if (query == "GENERATE") {
            N = n;
            K = k;
            students = "";
            for (int i = 0; i < n; ++i) students += char('A' + i);
            
            allSolutions.clear();
            vector<string> currentGroups;
            vector<bool> used(n, false);
            
            // 开始第一个组
            if (n > 0) {
                used[0] = true;
                currentGroups.push_back(string(1, students[0]));
                generateSolutions(1, currentGroups, used, 1, 1);
            } else {
                allSolutions.push_back({});
            }

            // 排序解
            sort(allSolutions.begin(), allSolutions.end());
            
            // 输出数量
            cout << allSolutions.size() << endl;
            
            // 输出具体解
            for (const auto& sol : allSolutions) {
                for (size_t i = 0; i < sol.size(); ++i) {
                    if (i > 0) cout << " ";
                    cout << sol[i];
                }
                cout << endl;
            }
        }
    }
    
    return 0;
}
