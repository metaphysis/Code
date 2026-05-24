// LA Encoding
// UVa ID: 11410
// Verdict: Accepted
// Submission Date: 2026-05-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
int main() {
    int t;
    cin >> t;
    while (t--) {
        string msg, broken;
        cin >> msg >> broken;
        // 1. 将消息看作 26 进制数，计算数值（A=0, B=1, ..., Z=25）
        long long rank = 0;
        for (char c : msg) rank = rank * 26 + (c - 'A');
        // 2. 构建可用字母表（按 A-Z 顺序，排除坏键）
        string avail;
        for (char c = 'A'; c <= 'Z'; ++c)
            if (broken.find(c) == string::npos) avail += c;
        int cnt = avail.size();
        // 3. 将 rank 转换为 cnt 进制
        string encoded;
        if (rank == 0) encoded = avail[0]; // 对应消息 "A"，但消息首字母不可能是 A，所以实际上不会执行
        else {
            while (rank > 0) {
                encoded += avail[rank % cnt];
                rank /= cnt;
            }
            reverse(encoded.begin(), encoded.end());
        }
        cout << encoded << '\n';
    }
    return 0;
}
