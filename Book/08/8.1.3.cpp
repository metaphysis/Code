#include <bits/stdc++.h>

using namespace std;

const int MAXN = 32;

int n, magic[MAXN][MAXN], maxWidth[MAXN];

void display()
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            maxWidth[j] = max(maxWidth[j], (int)to_string(magic[i][j]).length());

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << setw(maxWidth[j] + 1) << right << magic[i][j];
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
            if (i != n / 4 || j)
                swap(magic[i][j], magic[i + n / 2][j]);
    swap(magic[n / 4][n / 4], magic[n / 4 + n / 2][n / 4]);
    for (int i = 0; i < n / 2; i++)
        for (int j = n - n / 4 + 1; j < n; j++)
            swap(magic[i][j], magic[i + n / 2][j]);
}

bool check()
{
    int M = n * (n * n + 1) / 2;
    int sum = 0, sum1 = 0, sum2 = 0;
    for (int i = 0; i < n; i++)
    {
        // Row by row.
        sum = 0;
        for (int j = 0; j < n; j++)
            sum += magic[i][j];
        if (sum != M) return false;
        
        // Column by column.
        sum = 0;
        for (int j = 0; j < n; j++)
            sum += magic[j][i];
        if (sum != M) return false;
        
        // Main and sub diagonal.
        sum1 += magic[i][i], sum2 += magic[i][n - 1 - i];
    }
    if (sum1 != M) return false;
    if (sum2 != M) return false;
    return true;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    
    int cases = 0;
    while (cin >> n)
    {
        if (cases++ > 0) cout << '\n';

        cout << "n=" << n << ", sum=" << n * (n * n + 1) / 2 << '\n';
        
        memset(magic, 0, sizeof(magic));

        if (n % 2)
            fillMagic1();
        else if (n % 4 == 0)
            fillMagic2();
        else
            fillMagic3();

        if (!check()) cout << "ERROR!\n";

        display();
    }

    return 0;
}
