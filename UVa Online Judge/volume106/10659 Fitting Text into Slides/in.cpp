#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));

    string cs = "abcdefghijklmnopqrstyuwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ`1234567890-=+_)(*&^%$#@!~|}{[]\\\":;\'?><,./";
    int cases = 100, cnt = cs.size();
    cout << cases << '\n';
    for (int c = 1; c <= cases; c++)
    {
        int n = rand() % 20 + 1;
        cout << n << '\n';
        for (int l = 1; l <= n; l++)
        {
            int m = rand() % 50 + 1;
            for (int i = 0; i < m; i++)
            {
                if (i) cout << ' ';
                int w = rand() % 20 + 1;
                for (int k = 0; k <= w; k++)
                    cout << cs[rand() % cnt];
            }
            cout << '\n';
        }
        int X = rand() % 2500 + 1, Y = rand() % 2500 + 1;
        cout << X << ' ' << Y << '\n';
    }

    return 0;
}
