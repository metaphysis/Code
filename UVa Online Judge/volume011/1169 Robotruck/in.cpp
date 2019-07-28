#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int cases = 20, ROW = 1000, CLN = 1000;
    cout << cases << '\n';
    for (int cs = 1; cs <= cases; cs++)
    {
        cout << '\n';
        int C = rand() % 99 + 2;
        cout << C << '\n';
        int N = rand() % 1000 + 1;
        cout << N << '\n';
        for (int i = 1; i <= N; i++)
        {
            cout << rand() % ROW << ' ' << rand() % CLN;
            int L = rand() % (C - 1) + 1;
            cout << ' ' << L << '\n';
        }
    }
    return 0;
}
