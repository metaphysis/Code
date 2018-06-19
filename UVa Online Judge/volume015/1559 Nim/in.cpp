#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    
    for (int cs = 1; cs <= 100; cs++)
    {
        int N = rand() % 10 + 1;
        int S = rand() % ((1 << 13) - 1) + 1;
        cout << N << ' ' << S;
        for (int i = 0; i < 2 * N; i++)
            cout << ' ' << (rand() % 16 + 1);
        cout << '\n';
    }
    cout << "0\n";
    
    return 0;
}
