#include <bits/stdc++.h>

using namespace std;

long long factorial[20] = {1};

void cantorExpansion(string s, long long n)
{
    n %= factorial[s.length()];
    for (int i = s.length() - 1; i >= 0; i--)
    {
        long long idx = n / factorial[i];
        cout << s[idx];
        s.erase(s.begin() + idx);
        n %= factorial[i];
    }
    cout << '\n';
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < 20; i++) factorial[i] = factorial[i - 1] * i;

    string s;
    long long n;

    while (cin >> s >> n)
    {
        sort(s.begin(), s.end());
        cantorExpansion(s, n);
    }

    return 0;
}
