#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int cases = 10000;
    cout << cases << '\n';
    for (int cs = 1; cs <= cases; cs++)
    {
        int N, M;
        N = rand() % 4 + 1;
        M = rand() % (50 / N + 1);
        cout << M << ' ' << N;
        int visited[M] = {};
        for (int i = 0; i < N; i++)
        {
            cout << ' ';
            if (M == 0) cout << 0;
            else
            {
                int r = rand() % M;
                if (visited[r]) cout << 0;
                else
                {
                    cout << r;
                    visited[r] = 1;
                }
            }
        }
        cout << ' ' << rand() % N + 1;
        cout << '\n';
    }
    return 0;
}
