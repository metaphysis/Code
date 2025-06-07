#include <bits/stdc++.h>
using namespace std;
char g[4] = {'A', 'G', 'C', 'T' };
int main(int argc, char *argv[]) {
    srand(time(NULL));
    int cases = 1;
    cout << cases << '\n';
    for (int cs = 1; cs <= cases; cs++) {
        int n = 6;
        cout << n << '\n';
        for (int i = 1; i <= n; i++) {
            int L = 1000000;
            for (int j = 0; j < L; j++)
                cout << g[rand() % 4];
            cout << '\n';
        }
    }
    return 0;
}
