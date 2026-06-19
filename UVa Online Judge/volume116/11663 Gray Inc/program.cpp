// Gray Inc
// UVa ID: 11663
// Verdict: Accepted
// Submission Date: 2026-06-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 格雷码解码为二进制索引串（高位在前）
string grayToBinary(const string& gray) {
    int n = (int)gray.size();
    string bin(n, '0');
    bin[0] = gray[0];
    for (int i = 1; i < n; ++i)
        bin[i] = ((bin[i-1] - '0') ^ (gray[i] - '0')) + '0';
    return bin;
}

// 二进制索引串编码为格雷码（高位在前）
string binaryToGray(const string& bin) {
    int n = (int)bin.size();
    string gray(n, '0');
    gray[0] = bin[0];
    for (int i = 1; i < n; ++i)
        gray[i] = ((bin[i] - '0') ^ (bin[i-1] - '0')) + '0';
    return gray;
}

// 二进制串加 1（模 2^n），高位在前
void incrementBinary(string& bin) {
    int n = (int)bin.size();
    int i = n - 1;
    while (i >= 0 && bin[i] == '1') {
        bin[i] = '0';
        --i;
    }
    if (i >= 0) bin[i] = '1';
    // 若 i < 0，说明全 1 变为全 0，已自动取模
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    string w;
    while (cin >> m >> w) {
        if (m == 0 && w == "0") break;

        string bin = grayToBinary(w);
        for (int step = 0; step < m; ++step)
            incrementBinary(bin);

        cout << binaryToGray(bin) << '\n';
    }
    return 0;
}
