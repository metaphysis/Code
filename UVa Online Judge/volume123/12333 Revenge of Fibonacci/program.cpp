// Revenge of Fibonacci
// UVa ID: 12333
// Verdict: Accepted
// Submission Date: 2025-10-29
// UVa Run Time: 0.320s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
const int MAXN = 50010, WIDTH = 8, BASE = 100000000;
int f[3][MAXN];
struct node {
    bool visited;
    vector<int> idxs;
    node* children[10];
    node () { memset(children, visited = 0, sizeof children); }
} root;
int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T;
    cin >> T;
    string prefix;
    int answer[MAXN], cnt = 0;
    memset(answer, -1, sizeof answer);
    for (int i = 1; i <= T; i++) {
        cin >> prefix;
        if (prefix == "1") { answer[i] = 0; cnt++; continue; }
        node* current = &root;
        for (auto c : prefix) {
            if (!current->children[c - '0']) current->children[c - '0'] = new node();
            current = current->children[c - '0'];
        }
        current->idxs.push_back(i);
    }
    int digits[110];
    int f1 = 0, f2 = 1, f3 = 2, length = 1;
    f[0][0] = 1, f[1][0] = 1;
    for (int i = 2; i < 100000; i++) {
        int carry = 0;
        for (int j = 0; j < length; j++) {
            f[f3][j] = f[f1][j] + f[f2][j] + carry;
            carry = f[f3][j] / BASE;
            f[f3][j] %= BASE;
        }
        if (carry) f[f3][length++] = carry;
        int ds = 0, firstBlock = 1;
        for (int j = length - 1; j >= 0 && ds <= 40; j--) {
            string block = to_string(f[f3][j]);
            if (firstBlock) firstBlock = 0;
            else while (block.length() < WIDTH) block = '0' + block;
            for(auto c : block) digits[ds++] = c - '0';
        }
        node* current = &root;
        for (int j = 0; j < ds; j++) {
            current = current->children[digits[j]];
            if (!current) break;
            if (current->idxs.size() && !current->visited) {
                current->visited = true;
                for (auto idx : current->idxs) answer[idx] = i;
                cnt += current->idxs.size();
            }
        }
        if (cnt == T) break;
        f1++, f2++, f3++;
        f1 %= 3, f2 %= 3, f3 %= 3;
    }
    for (int i = 1; i <= T; i++) cout << "Case #" << i << ": " << answer[i] << '\n';
    return 0;
}
