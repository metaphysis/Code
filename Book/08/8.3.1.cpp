#include <bits/stdc++.h>

using namespace std;

void print(int flag[], int idx)
{
    for (int i = 0; i < idx; i++)
        cout << setw(2) << right << flag[i];
    cout << '\n';
}

void generate(int flag[], int idx, int last, int n)
{
    if (idx < last)
    {
        if (idx == 0)
        {
            for (int i = 0; i < n; i++)
            {
                flag[idx] = i;
                generate(flag, idx + 1, last, n);
            }
        }
        else
        {
            for (int i = flag[idx - 1] + 1; i < n; i++)
            {
                flag[idx] = i;
                generate(flag, idx + 1, last, n);
            }
        }
    }
    else print(flag, idx);
}

void enumeratingSubset(int n)
{
    for (int i = 1; i <= n; i++)
    {
        int *flag = new int[n];
        generate(flag, 0, i, n);
        delete[]flag;
    }
}

int main(int argc, char *argv[])
{
    enumeratingSubset(8);

    return 0;
}
