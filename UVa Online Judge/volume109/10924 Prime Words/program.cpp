// Prime Words
// UVa ID: 10924
// Verdict: Accepted
// Submission Date: 2018-03-02
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

bool isPrime(int a)
{
    if (a <= 2) return true;
    if ((a & 1) == 0) return false;

    int high = (int)sqrt(a);
    for (int i = 3; i <= high; i += 2)
        if (a % i == 0)
            return false;

    return true;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        int sum = 0;
        for (auto c : line)
            if (isupper(c)) sum += c - 'A' + 27;
            else sum += c - 'a' + 1;
        if (isPrime(sum)) cout << "It is a prime word.\n";
        else cout << "It is not a prime word.\n";
    }

    return 0;
}
