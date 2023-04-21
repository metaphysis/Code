// Function Overloading
// UVa ID: 11032
// Verdict: Accepted
// Submission Date: 2023-04-21
// UVa Run Time: 0.390s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10000000;

int t[MAXN + 100], T[MAXN + 100];

inline int lowbit(int x) { return x & (-x); }

void add(int x, int delta){
    for (int i = x; i <= MAXN; i += lowbit(i))
        T[i] += delta;
}

int get(int x) {
    int sum = 0;
    for (int i = x; i; i -= lowbit(i))
        sum += T[i];
    return sum;
}

int sum(int L, int R) { return get(R) - get(L - 1); }

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    for (int i = 1; i <= MAXN; i++) {
        int n = i, sod = 0;
        while (n) {
            sod += n % 10;
            n /= 10;
        }
        if (!t[i + sod]) {
            t[i + sod] = i;
            add(i + sod, 1);
        }
    }
    int cases;
    cin >> cases;
    cin.ignore(256, '\n');
    string line;
    for (int cs = 1; cs <= cases; cs++) {
        cout << "Case " << cs << ": ";
        getline(cin, line);
        istringstream iss(line);
        int a, b;
        if (line.find(' ') != line.npos) {
            iss >> a >> b;
            if (a > b) cout << 0;
            else cout << (b - a + 1) - sum(a, b);
        } else {
            iss >> a;
            if (!t[a]) cout << -1;
            else cout << t[a];
        }
        cout << '\n';
    }
    return 0;
}
