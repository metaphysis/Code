// Wily Hacker's Problem
// UVa ID: 779
// Verdict: Accepted
// Submission Date: 2026-10-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

uint32_t leftRotate(uint32_t value, uint32_t shift) {
    value &= 0xffff;
    shift &= 15;
    if (shift == 0) return value;
    return ((value << shift) | (value >> (16 - shift))) & 0xffff;
}

uint32_t rightRotate(uint32_t value, uint32_t shift) {
    value &= 0xffff;
    shift &= 15;
    if (shift == 0) return value;
    return ((value >> shift) | (value << (16 - shift))) & 0xffff;
}

uint32_t parseWord(const string &value, int position) {
    return stoul(value.substr(position, 4), nullptr, 16);
}

string decrypt(const string &cipher, const string &key) {
    uint32_t c1 = parseWord(cipher, 0), c2 = parseWord(cipher, 4), c3 = parseWord(cipher, 8), c4 = parseWord(cipher, 12);
    uint32_t k1 = parseWord(key, 0), k2 = parseWord(key, 4), k3 = parseWord(key, 8), k4 = parseWord(key, 12);
    uint32_t b1 = rightRotate(c1, k4), b2 = (c2 + 65536 - k3) & 0xffff, b3 = (c3 + 65536 - k2) & 0xffff, b4 = rightRotate(c4, k1);
    uint32_t x1 = b1 ^ b3, x2 = b2 ^ b4;
    uint32_t y1 = leftRotate(x1, k1 ^ k2), y2 = leftRotate((y1 + x2) & 0xffff, k3 ^ k4);
    uint32_t z2 = (y1 + y2) & 0xffff;
    uint32_t a1 = b1 ^ y2, a2 = b2 ^ z2, a3 = b3 ^ y2, a4 = b4 ^ z2;
    uint32_t m1 = rightRotate(a1, k1), m2 = (a2 + 65536 - k2) & 0xffff, m3 = (a3 + 65536 - k3) & 0xffff, m4 = rightRotate(a4, k4);
    string message;
    message += char(m1 & 0xff);
    message += char((m1 >> 8) & 0xff);
    message += char(m2 & 0xff);
    message += char((m2 >> 8) & 0xff);
    message += char(m3 & 0xff);
    message += char((m3 >> 8) & 0xff);
    message += char(m4 & 0xff);
    message += char((m4 >> 8) & 0xff);
    return message;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string cipher, key;
    while (cin >> cipher >> key)
        cout << decrypt(cipher, key) << '\n';
    return 0;
}
