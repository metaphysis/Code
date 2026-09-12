#include <bits/stdc++.h>
using namespace std;

long long calc(const string &str) {
    long long cnt[27] = {};
    long long sum = 0, ans = 0;
    int kind = 0;
    for (char ch : str) {
        if (ch >= 'A' && ch <= 'Z')
            cnt[ch - 'A']++;
        else if (ch == ' ')
            cnt[26]++;
    }
    priority_queue<long long, vector<long long>, greater<long long>> que;
    for (int i = 0; i < 27; i++)
        if (cnt[i] > 0) {
            que.push(cnt[i]);
            sum += cnt[i];
            kind++;
        }
    if (kind == 0) return 0;
    if (kind == 1) return sum;
    while (que.size() > 1) {
        long long x = que.top(), y;
        que.pop(); y = que.top(); que.pop();
        ans += x + y;
        que.push(x + y);
    }
    return ans;
}

void printAns(const string &str) {
    string text;
    bool inSpace = false;
    auto isAsciiSpace = [](unsigned char ch) -> bool {
        return ch == ' ' || ch == '\t' || ch == '\n' ||
               ch == '\r' || ch == '\f' || ch == '\v';
    };
    for (unsigned char ch : str) {
        if (isAsciiSpace(ch)) {
            if (!inSpace) {
                text += ' ';
                inSpace = true;
            }
        } else if (ch >= 'a' && ch <= 'z') {
            text += static_cast<char>(ch - 'a' + 'A');
            inSpace = false;
        } else if (ch >= 'A' && ch <= 'Z') {
            text += static_cast<char>(ch);
            inSpace = false;
        }
        // 其他字符（数字、标点、重音字母等）直接忽略
    }
    while (!text.empty() && text.back() == ' ') text.pop_back();
    cout << calc(text) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line, text;
    bool hasSentence = false;
    while (getline(cin, line)) {
        if (line.empty() && hasSentence) {
            printAns(text);
            text.clear();
            hasSentence = false;
        } else {
            if (hasSentence) text += '\n';
            text += line;
            hasSentence = true;
        }
    }
    if (hasSentence) printAns(text);
    return 0;
}
