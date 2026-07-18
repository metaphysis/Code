// The Turtle's Journey
// UVa ID: 12811
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000003;

// 三元组结果
struct Result {
    long long leftDeg;
    long long rightDeg;
    long long steps;
};

// 递归解析表达式列表，遇到 stop 标记（"]" 或 "end"）时停止并消耗该标记
Result parseList(istream& in, const string& stop) {
    long long l = 0, r = 0, s = 0;
    string token;
    while (in >> token) {
        if (token == stop) break;                    // 消耗终止符并退出
        if (token == "left") {
            int val; in >> val;
            l = (l + val) % MOD;
        } else if (token == "right") {
            int val; in >> val;
            r = (r + val) % MOD;
        } else if (token == "forward") {
            int val; in >> val;
            s = (s + val) % MOD;
        } else if (token == "repeat") {
            int n; in >> n;
            string bracket; in >> bracket;           // 读取 "["
            Result inner = parseList(in, "]");       // 递归解析内部，已经消耗了 "]"
            l = (l + inner.leftDeg * n) % MOD;
            r = (r + inner.rightDeg * n) % MOD;
            s = (s + inner.steps * n) % MOD;
        }
        // 语法保证不会出现其他 token
    }
    return {l, r, s};
}

// 解析单个完整程序，返回三个值
Result parseProgram(istream& in) {
    string beginToken; in >> beginToken;             // 读取 "begin"
    return parseList(in, "end");                     // 解析到 "end" 并消耗它
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        Result res = parseProgram(cin);
        cout << res.leftDeg << " " << res.rightDeg << " " << res.steps << "\n";
    }
    return 0;
}
