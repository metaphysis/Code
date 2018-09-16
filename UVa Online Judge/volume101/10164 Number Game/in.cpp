#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));

    int N[10] = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};

    for (int cases = 1; cases <= 100; cases++)
    {
        int n = N[rand() % 10];
        cout << n << '\n';
        for (int i = 0; i < (2 * n - 1); i++)
        {
            if (i) cout << ' ';
            cout << (rand() % 1000 + 1);
        }
        cout << '\n';
    }
    cout << "0\n";

    return 0;
}
