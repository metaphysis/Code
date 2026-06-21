// Recursive Texting
// UVa ID: 12596
// Verdict: Accepted
// Submission Date: 2026-06-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 数字 -> 英文单词
const string digitWord[10] = {"ZERO", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE"};

// 字母 -> 数字（手机键盘）
const int letterToDigit[26] = {
    2, 2, 2,  // A B C
    3, 3, 3,  // D E F
    4, 4, 4,  // G H I
    5, 5, 5,  // J K L
    6, 6, 6,  // M N O
    7, 7, 7, 7, // P Q R S
    8, 8, 8,  // T U V
    9, 9, 9, 9  // W X Y Z
};

string wordAfterOne[26];          // 每个字母一步转换后的单词
long long lenMemo[21][26];        // lenMemo[step][ch] 表示字母 ch 经过 step 步转换后的长度

// 递归获取字符
char getChar(int step, int ch, long long pos) {
    if (step == 0) return char('A' + ch);
    const string &s = wordAfterOne[ch];
    long long acc = 0;
    for (char c : s) {
        int idx = c - 'A';
        long long subLen = lenMemo[step - 1][idx];
        if (pos > acc + subLen) acc += subLen;
        else return getChar(step - 1, idx, pos - acc);
    }
    return '?'; // 不会执行到
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 预处理 wordAfterOne
    for (int i = 0; i < 26; ++i) {
        int d = letterToDigit[i];
        wordAfterOne[i] = digitWord[d];
    }

    // 预计算 lenMemo[step][ch]
    for (int step = 0; step <= 20; ++step) {
        for (int ch = 0; ch < 26; ++ch) {
            if (step == 0) {
                lenMemo[step][ch] = 1;
            } else {
                long long total = 0;
                for (char c : wordAfterOne[ch]) {
                    total += lenMemo[step - 1][c - 'A'];
                }
                lenMemo[step][ch] = total;
            }
        }
    }

    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        string W;
        int n;
        long long k;
        cin >> W >> n >> k;

        long long acc = 0;
        int chosenCh = -1;
        long long offset = 0;

        for (char c : W) {
            int idx = c - 'A';
            long long subLen = lenMemo[n][idx];
            if (k > acc + subLen) {
                acc += subLen;
            } else {
                chosenCh = idx;
                offset = k - acc;
                break;
            }
        }

        char ans = getChar(n, chosenCh, offset);
        cout << "Case " << tc << ": " << ans << '\n';
    }

    return 0;
}
