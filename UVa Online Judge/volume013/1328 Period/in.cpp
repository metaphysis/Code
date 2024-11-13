// 
// UVa ID: 
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2024，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    srand(time(NULL));
    int cases = 100;
    string s = "abcdefghijklmnopqrstuvwxyz";
    for (int cs = 1; cs <= cases; cs++) {
        int N = rand() % 1000 + 2;
        cout << N << '\n';
        for (int i = 1; i <= N; i++) cout << s[rand() % 2];
        cout << '\n';
    }
    cout << 0 << '\n';
    return 0;
}
