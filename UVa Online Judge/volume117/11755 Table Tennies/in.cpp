#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int cases = 1000;
    cout << cases << '\n';
    for (int cs = 1; cs <= cases; cs++)
    {
        int L = rand() % 101;
        for (int i = 0; i < L; i++)
        {
            if (rand() % 2 == 1) cout << 'W';
            else cout << 'L';
        }
        cout << '\n';
        int p1 = rand() % 101, p2 = rand() % 101;
        cout << fixed << setprecision(3) << p1 / 100.0 << ' ' << p2 / 100.0 << '\n';
    }
    return 0;
}
