#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int cases = 100, mask[1024], m;
    for (int cs = 1; cs <= cases; cs++)
    {
        memset(mask, 0, sizeof(mask));
        int N = rand() % 10 + 1, M = rand() % (1 << N) / 2 + 1;
        cout << N << ' ' << M << '\n';
        for (int i = 0; i < M; i++)
        {
            do { m = rand() % (1 << N); } while (mask[m]);
            mask[m] = 1;
            bitset<10> b(m);
            string mask = b.to_string().substr(10 - N);
            if (rand() % 100 >= 80) mask[rand() % N] = '*';
            cout << mask << '\n';
        }
    }
    cout << "0 0\n";
    return 0;
}
