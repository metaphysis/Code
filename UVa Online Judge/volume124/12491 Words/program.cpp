// Words
// UVa ID: 12491
// Verdict: Accepted
// Submission Date: 2026-04-26
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

bool puedeConcatenar(const vector<string>& A, const vector<string>& B) {
    // (剩余A串, 剩余B串)
    queue<pair<string, string>> q;
    set<pair<string, string>> visitado;

    // 初始状态：任意两个单词的组合作为起点
    for (const string& a : A) {
        for (const string& b : B) {
            if (a == b) return true;
            q.push({a, b});
            visitado.insert({a, b});
        }
    }

    while (!q.empty()) {
        auto [sa, sb] = q.front(); q.pop();

        if (sa == sb) return true;

        if (sa.size() < sb.size()) {
            // 尝试用A中的单词扩展sa
            for (const string& w : A) {
                string nuevaSa = sa + w;
                // 比较 nuevaSa 和 sb 的公共前缀
                int len = min(nuevaSa.size(), sb.size());
                if (nuevaSa.substr(0, len) == sb.substr(0, len)) {
                    string restaA = nuevaSa.substr(len);
                    string restaB = sb.substr(len);
                    if (restaA == restaB) return true;
                    if (!visitado.count({restaA, restaB})) {
                        visitado.insert({restaA, restaB});
                        q.push({restaA, restaB});
                    }
                }
            }
        } else {
            // 尝试用B中的单词扩展sb
            for (const string& w : B) {
                string nuevaSb = sb + w;
                int len = min(sa.size(), nuevaSb.size());
                if (sa.substr(0, len) == nuevaSb.substr(0, len)) {
                    string restaA = sa.substr(len);
                    string restaB = nuevaSb.substr(len);
                    if (restaA == restaB) return true;
                    if (!visitado.count({restaA, restaB})) {
                        visitado.insert({restaA, restaB});
                        q.push({restaA, restaB});
                    }
                }
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N1, N2;
    while (cin >> N1 >> N2) {
        vector<string> A(N1), B(N2);
        for (int i = 0; i < N1; ++i) cin >> A[i];
        for (int i = 0; i < N2; ++i) cin >> B[i];

        cout << (puedeConcatenar(A, B) ? 'S' : 'N') << '\n';
    }
    return 0;
}
