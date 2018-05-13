// The Tajmahal of ++Y2k
// UVa ID: 10087
// Verdict: Accepted
// Submission Date: 2018-05-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 110;

int n, m, offset, magic[MAXN][MAXN];

void display()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << setw(10) << right << magic[i][j] + offset;
        cout << '\n';
    }
}

// n = 2 * k + 1, k >= 1.
void fillMagic1()
{
    for (int i = 0, j = n / 2, k = 1; k <= n * n; k++)
    {
        magic[i][j] = k;
        if (k % n)
        {
            i = (i - 1 + n) % n;
            j = (j + 1) % n;
        }
        else
            i = (i + 1) % n;
    }
}

// n = 4 * k, k >= 1.
void fillMagic2()
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (((i % 4 == 0 || i % 4 == 3) && (j % 4 == 0 || j % 4 == 3)) ||
                ((i % 4 == 1 || i % 4 == 2) && (j % 4 == 1 || j % 4 == 2)))
                magic[i][j] = n * n - (i * n + j);
            else
                magic[i][j] = i * n + j + 1;
}

void fillHelper(int n, int offseti, int offsetj, int offsetk)
{
    for (int i = 0, j = n / 2, k = 1; k <= n * n; k++)
    {
        magic[i + offseti][j + offsetj] = k + offsetk;
        if (k % n)
        {
            i = (i - 1 + n) % n;
            j = (j + 1) % n;
        }
        else
            i = (i + 1) % n;
    }
}

// n = 4 * k + 2, k >= 1.
void fillMagic3()
{
    fillHelper(n / 2, 0, 0, 0);
    fillHelper(n / 2, n / 2, n / 2, n * n / 4);
    fillHelper(n / 2, 0, n / 2, n * n / 2);
    fillHelper(n / 2, n / 2, 0, n * n / 4 * 3);
    for (int i = 0; i < n / 2; i++)
        for (int j = 0; j < n / 4; j++)
            swap(magic[i][j], magic[i + n / 2][j]);
    for (int i = 0; i < n / 2; i++)
        for (int j = n - n / 4 + 1; j < n; j++)
            swap(magic[i][j], magic[i + n / 2][j]);
    for (int j = 0; j <= n / 4; j += n / 4)
        swap(magic[n / 4][j], magic[n / 4 + n / 2][j]);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n >> m)
    {
        int sum = n * (n * n + 1) / 2;
        if (n == 2 || ((m - sum) % n))
        {
            cout << "You can't be like Shahjahan!\n\n";
            continue;
        }
        offset = (m - sum) / n;

        memset(magic, 0, sizeof(magic));
        if (n % 2) fillMagic1();
        else if (n % 4 == 0) fillMagic2();
        else fillMagic3();
        display();
        cout << '\n';
    }

    return 0;
}
