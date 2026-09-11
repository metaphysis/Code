#include <bits/stdc++.h>
using namespace std;

const int maxN = 20000;
const int maxL = 105;
const int maxW = (maxN + 63) / 64;
unsigned long long bitMap[maxL][4][maxW];
int bitCnt[maxL][4];

int charToId(char ch) {
    if (ch == 'A') return 0;
    if (ch == 'C') return 1;
    if (ch == 'G') return 2;
    if (ch == 'T') return 3;
    return -1;
}

void addSequence(const string &seq, int id) {
    int word = (id - 1) >> 6, bit = (id - 1) & 63;
    unsigned long long mask = 1ULL << bit;
    for (int i = 0; i < (int)seq.size(); ++i) {
        int chId = charToId(seq[i]);
        if (chId == -1) {
            for (int j = 0; j < 4; ++j) {
                bitMap[i][j][word] |= mask;
                ++bitCnt[i][j];
            }
        } else {
            bitMap[i][chId][word] |= mask;
            ++bitCnt[i][chId];
        }
    }
}

void querySequence(const string &seq, int id) {
    int basePos = -1, baseId = -1, baseCnt = INT_MAX;
    for (int i = 0; i < (int)seq.size(); ++i) {
        int chId = charToId(seq[i]);
        if (chId != -1 && bitCnt[i][chId] < baseCnt) {
            basePos = i;
            baseId = chId;
            baseCnt = bitCnt[i][chId];
        }
    }
    unsigned long long result[maxW];
    for (int i = 0; i < maxW; ++i) result[i] = 0;
    if (basePos == -1) {
        int wordCnt = (id - 1 + 63) >> 6;
        for (int i = 0; i < wordCnt; ++i) result[i] = ~0ULL;
        if ((id - 1) & 63) result[wordCnt - 1] = (1ULL << ((id - 1) & 63)) - 1;
    } else {
        for (int i = 0; i < maxW; ++i) result[i] = bitMap[basePos][baseId][i];
        for (int i = 0; i < (int)seq.size(); ++i) {
            int chId = charToId(seq[i]);
            if (chId == -1 || i == basePos) continue;
            for (int j = 0; j < maxW; ++j) result[j] &= bitMap[i][chId][j];
        }
    }
    bool hasMatch = false;
    for (int i = 0; i < maxW; ++i)
        if (result[i]) {
            hasMatch = true;
            break;
        }
    if (!hasMatch) return;
    cout << id << ":";
    for (int i = 0; i < maxW; ++i) {
        unsigned long long bits = result[i];
        while (bits) {
            int offset = __builtin_ctzll(bits);
            int previousId = i * 64 + offset + 1;
            cout << " " << previousId;
            bits &= bits - 1;
        }
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        string seq;
        cin >> seq;
        querySequence(seq, i);
        addSequence(seq, i);
    }
    return 0;
}
