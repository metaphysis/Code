// Base64 Decoding
// UVa ID: 10343
// Verdict: Wrong Answer
// Submission Date: 2025-11-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 字符到 6 位值的映射表（-1 表示无效）
int charToVal[256];

// 初始化映射表
void initTable() {
    fill(charToVal, charToVal + 256, -1);
    for (int i = 0; i < 26; ++i) charToVal['A' + i] = i;
    for (int i = 0; i < 26; ++i) charToVal['a' + i] = 26 + i;
    for (int i = 0; i < 10; ++i) charToVal['0' + i] = 52 + i;
    charToVal['+'] = 62;
    charToVal['/'] = 63;
}

// 解码一个 Base64 字符串（已过滤掉无关字符）
string decodeBase64(const string& encoded) {
    string decoded;
    int n = encoded.size();
    for (int i = 0; i < n; i += 4) {
        int v[4] = {0};
        int validCnt = 0;
        for (int j = 0; j < 4; ++j) {
            char c = encoded[i + j];
            if (c == '=') v[j] = -1;          // 填充符
            else v[j] = charToVal[(unsigned char)c];
            if (v[j] != -1) ++validCnt;
        }
        if (validCnt == 4) {
            decoded.push_back((v[0] << 2) | (v[1] >> 4));
            decoded.push_back(((v[1] & 0xF) << 4) | (v[2] >> 2));
            decoded.push_back(((v[2] & 0x3) << 6) | v[3]);
        } else if (validCnt == 3) {
            decoded.push_back((v[0] << 2) | (v[1] >> 4));
            decoded.push_back(((v[1] & 0xF) << 4) | (v[2] >> 2));
        } else if (validCnt == 2) {
            decoded.push_back((v[0] << 2) | (v[1] >> 4));
        }
    }
    return decoded;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    initTable();
    string current;   // 当前数据集的 Base64 字符序列（含 '='）
    char ch;
    while (cin.get(ch)) {
        if (ch == '#') {
            if (!current.empty()) {
                string decoded = decodeBase64(current);
                cout << decoded << '#';
                current.clear();
            }
            // 若 current 为空，说明是连续的 #，忽略
        } else {
            // 只保留 Base64 有效字符和 '='
            bool isValid = (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') ||
                           (ch >= '0' && ch <= '9') || ch == '+' || ch == '/' || ch == '=';
            if (isValid) current.push_back(ch);
            // 其他字符（空格、换行等）忽略
        }
    }
    return 0;
}
