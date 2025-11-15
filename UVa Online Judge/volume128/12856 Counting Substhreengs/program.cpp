// Counting Substhreengs
// UVa ID: 12856
// Verdict: Accepted
// Submission Date: 2025-11-09
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <string>
#include <cstring>
using namespace std;

long long countSubsthreengs(const string& s) {
    long long totalCount = 0;
    int n = s.length();
    
    for (int i = 0; i < n; ) {
        if (isdigit(s[i])) {
            int count[3] = {1, 0, 0}; // 前缀和模3的计数，初始前缀和0出现1次
            int sumMod = 0;
            
            int j = i;
            while (j < n && isdigit(s[j])) {
                int digit = s[j] - '0';
                sumMod = (sumMod + digit) % 3;
                totalCount += count[sumMod];
                count[sumMod]++;
                j++;
            }
            i = j;
        } else {
            i++;
        }
    }
    
    return totalCount;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string line;
    while (getline(cin, line)) {
        cout << countSubsthreengs(line) << "\n";
    }
    
    return 0;
}
