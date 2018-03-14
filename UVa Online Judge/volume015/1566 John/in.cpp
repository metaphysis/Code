#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int cases = 1000;
    cout << cases << '\n';
    for (int c = 1; c <= cases; c++)
    {
        int n = rand() % 47 + 1;
        cout << n << '\n';
        for (int i = 1; i <= n; i++)
        {
            int m = rand() % 4747 + 1;
            if (i > 1) cout << ' ';
            if (rand() % 1000 < 300) cout << 1;
            else cout << m;
        }
        cout << '\n';
    }
    return 0;
}
