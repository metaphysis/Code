#include <bits/stdc++.h>

using namespace std;

int n, k;
const int MAXN = 10000;
bool circle[MAXN + 10];

int findLast()
{
    fill(circle, circle + MAXN, true);

    int index = 1, nn = n;
    while (nn > 1)
    {
        int kk = k;
        for (; index <= n; index++)
            if (circle[index] && (--kk == 0))
                break;

        while (kk)
        {
            for (index = 1; index <= n; index++)
                if (circle[index] && (--kk == 0))
                    break;
        }

        circle[index] = false;
        nn--;
    }

    for (int i = 1; i <= n; i++)
        if (circle[i])
            return i;
}

int main(int argc, char *argv[])
{
    while (cin >> n >> k, n && k)
        cout << findLast() << endl;

    return 0;
}
