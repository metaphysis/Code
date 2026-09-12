#include <bits/stdc++.h>
using namespace std;

int divThree(string &num) {
    string next;
    int carry = 0, cur;
    for (char ch : num) {
        cur = carry * 10 + ch - '0';
        if (!next.empty() || cur / 3 > 0) next += char('0' + cur / 3);
        carry = cur % 3;
    }
    if (next.empty()) next = "0";
    num = next;
    return carry;
}

void minusOne(string &num) {
    int pos = (int)num.size() - 1;
    while (num[pos] == '0') {
        num[pos] = '9';
        pos--;
    }
    num[pos]--;
    pos = 0;
    while (pos + 1 < (int)num.size() && num[pos] == '0') pos++;
    num = num.substr(pos);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int test;
    string num;
    cin >> test;
    while (test--) {
        cin >> num;
        minusOne(num);
        vector<string> board(19, string(19, '.'));
        for (int i = 0; i < 361 && num != "0"; i++) {
            int rem = divThree(num);
            if (rem == 1) board[i / 19][i % 19] = 'W';
            else if (rem == 2) board[i / 19][i % 19] = 'B';
        }
        for (int i = 0; i < 19; i++) cout << board[i] << '\n';
        cout << '\n';
    }
    return 0;
}
