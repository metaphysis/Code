#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    srand(time(NULL));
    int cases = 100;
    cout << cases << '\n';
    for (int cs = 1; cs <= cases; cs++)
    {
        int n = rand() % 18 + 3;
        cout << n << '\n';
        int zero = 0;
        for (int i = 0; i < n - 1; i++)
        {
            int m = rand() % 31;
            if (i) cout << ' ';
            cout << m;
            if (m == 0) zero++;
        }
        if (!zero) cout << " 0\n";
        else cout << ' ' << rand() % 31 << '\n';
    }
    return 0;
}
