#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int cases = 20;
    for (int cs = 1; cs <= cases; cs++)
    {
        int N = rand() % 17 + 4;
        int S = rand() % 1001;
        cout << N << ' ' << S << '\n';
        for (int s = 1; s <= S; s++)
        {
            int B = rand() % (N * N) + 1;
            cout << B << ' ';
            int E = rand() % (N * N) + 1;
            while (E == B) E = rand() % (N * N) + 1;
            cout << E << '\n';
        }
    }
    cout << "0 " << cases << '\n';
}
