// Children's Game
// UVa ID: 10905
// Verdict: Accepted
// Submission Date: 2018-01-12
// UVa Run Time: 0.020s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

bool cmp(string a, string b)
{
    string aa = a + b, bb = b + a;
    for (int i = 0; i < aa.length(); i++)
        if (aa[i] != bb[i])
            return aa[i] > bb[i];
    return false;
}

inline bool cmp1(const string &a, const string &b)
{
    static char c1, c2;
    static int A, B, L;
    
    A = a.length(), B = b.length(), L = a.length() + b.length();
    
    for (int i = 0; i < L ; i++)
    {
        if (i < A) c1 = a[i]; else c1 = b[i - A];
        if (i < B) c2 = b[i]; else c2 = a[i - B];
        if (c1 != c2) return c1 > c2;
    }
    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    string numbers[64];

    while (cin >> n, n > 0)
    {
        for (int i = 0; i < n; i++)
            cin >> numbers[i];

        sort(numbers, numbers + n, cmp1);

        for (int i = 0; i < n; i++)
            cout << numbers[i];
        cout << '\n';
    }

    return 0;
}
