#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    for (int cases = 1; cases <= 100; cases++)
    {
        int n = rand() % 100 + 1;
        int m = min(rand() % n + 1, 20);
        cout << n << ' ' << m << '\n';
        for (int i = 1; i <= n; i++)
        {
            cout << rand() % 21;
            cout << ' ';
            cout << rand() % 21;
            cout << '\n';
        }
        cout << '\n';
    }
    cout << "0 0\n";
    return 0;
}
