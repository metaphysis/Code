// Base64 Decoding
// UVa ID: 10343
// Verdict: Wrong Answer
// Submission Date: 2025-11-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

// 在线测试数据存在问题，目前无法获得通过。

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

const string base64Chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int findIndex(char c) {
    if (c >= 'A' && c <= 'Z') return c - 'A';
    if (c >= 'a' && c <= 'z') return c - 'a' + 26;
    if (c >= '0' && c <= '9') return c - '0' + 52;
    if (c == '+') return 62;
    if (c == '/') return 63;
    return -1;
}

string base64Decode(const string& encoded) {
    string decoded;
    int len = encoded.size();
    int i = 0;
    while (i < len) {
        int chunk = 0, count = 0, euqal = 0;
        for (int j = 0; j < 4 && i < len; i++, j++) {
            char c = encoded[i];
            if (c == '=') { euqal++; continue; }
            int idx = findIndex(c);
            if (idx != -1) {
                chunk = (chunk << 6) | idx;
                count++;
            }
        }
        if (euqal) {
            if (euqal == 2) decoded += (chunk >> 4) & 0xFF;
            if (euqal == 1) decoded += (chunk >> 8) & 0xFF, decoded += (chunk >> 4) & 0xFF;
            break;
        }
        if (count >= 2) decoded += (chunk >> 16) & 0xFF;
        if (count >= 3) decoded += (chunk >> 8) & 0xFF;
        if (count >= 4) decoded += chunk & 0xFF;
    }
    return decoded;
}

int main() {
    string line, data;
    while (getline(cin, line))
        for (char c : line)
            if (c == '#') {
                if (!data.empty()) {
                    cout << base64Decode(data) << "#";
                    data.clear();
                }
            } else data += c;
    return 0;
}
