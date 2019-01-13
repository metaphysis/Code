#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int n = rand() % 490000 + 10000, m = 10000;
    cout << n << ' ' << m << '\n';
    for (int i = 0, sign = 1; i < n; i++)
    {
        if (i) cout << ' ';
        if (rand() % 100 > 80) sign *= -1;
        cout << sign * (rand() % 1000000000);
    }
    cout << '\n';
    for (int i = 0; i < m; i++)
    {
        int s = rand() % n + 1;
        int e;
        if (s == n) e = s;
        else e = s + rand() % (n - s);
        cout << s << ' ' << e << '\n';
        
    }
    return 0;
}
