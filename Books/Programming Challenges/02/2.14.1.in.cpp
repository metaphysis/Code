#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    srand(time(NULL));
    int n = 100;
    cout << n << '\n';
    for (int i = 0; i < n; i++) { if (i) cout << ' '; cout << i; }
    cout << '\n';
    int m = 10;
    cout << m << '\n';
    for (int i = 1; i <= m; i++)
    {
        int L = rand() % 100 + 1;
        int R = rand() % (100 - L + 1);
        cout << L << ' ' << (L + R) << '\n';
    }
    return 0;
}
