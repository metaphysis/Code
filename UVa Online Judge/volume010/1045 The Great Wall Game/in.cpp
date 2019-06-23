#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    int cases = 1000;
    int stonex[16], stoney[16], row, cln, visited;

    srand(time(NULL));

    for (int i = 1; i <= cases; i++)
    {
        int n = rand() % 15 + 1;
        cout << n << '\n';
        for (int j = 1; j <= n; j++)
        {
            while (true)
            {
                visited = 0;
                row = rand() % n + 1, cln = rand() % n + 1;
                for (int k = 1; k < j; k++)
                    if (stonex[k] == row && stoney[k] == cln)
                    {
                        visited = 1;
                        break;
                    }
                if (!visited) break;
            }
            stonex[j] = row, stoney[j] = cln;
            if (j > 1) cout << ' ';
            cout << row << ' ' << cln;
        }
        cout << '\n';
    }
    cout << "0\n";

    return 0;
}
