#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    
    for (int cs = 1; cs <= 1000; cs++)
    {
        int L = rand() % 200 + 1, N = rand() % L + 1;
        cout << L << ' ' << N << '\n';
        int T = rand() % 40 + 1;
        for (int i = 1; i <= T; i++)
            cout << (rand() % 2);
        cout << '\n';
    }
    cout << "0 0\n";

    return 0;
}
