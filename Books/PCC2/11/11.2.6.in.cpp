#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int cases = 100;
    cout << cases << '\n';
    for (int cs = 1; cs <= cases; cs++)
    {
        int N = rand() % 100;
        int V = rand() % 1000;
        cout << N << ' ' << V << '\n';
        for (int i = 0; i < N; i++) cout << (rand() % 10 + 1) << ' ' << (rand() % 1000 + 1) << '\n';
        cout << '\n';
    }
    return 0;
}
