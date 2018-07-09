// Dancing Digits
// UVa ID: 11198
// Verdict: Accepted
// Submission Date: 2018-07-09
// UVa Run Time: 0.790s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct package
{
    string digit;
    int moves;
    package (string digit = "", int moves = 0): digit(digit), moves(moves) {}
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, sign[10], cases = 0;
    while (cin >> n, n != 0)
    {
        cout << "Case " << ++cases << ": ";
        
        memset(sign, 0, sizeof(sign));
        int negative = 0;
        string digit;
        digit += (char)('0' + abs(n));
        if (n < 0) negative++, sign[abs(n)] = 1;
        for (int i = 1; i < 8; i++)
        {
            cin >> n;
            digit += (char)('0' + abs(n));
            if (n < 0) negative++, sign[abs(n)] = 1;
        }
        if (digit == "12345678")
        {
            cout << "0\n";
            continue;
        }
        if (digit != "12345678" && (negative == 0 || negative == 8))
        {
            cout << "-1\n";
            continue;
        }

        package pack = package(digit, 0);
        set<string> visited;
        visited.insert(digit);
        queue<package> q;
        q.push(pack);

        int best = -1;
        while (!q.empty())
        {
            pack = q.front(); q.pop();
            if (pack.digit == "12345678")
            {
                best = pack.moves;
                break;
            }

            for (int i = 0; i < 8; i++)
                for (int j = 0; j < 8; j++)
                {
                    if (i == j) continue;
                    int sum = (pack.digit[i] - '0') + (pack.digit[j] - '0');
                    if (sum != 3 && sum != 5 && sum != 7 && sum != 11 && sum != 13) continue;
                    int flag1 = sign[pack.digit[i] - '0'], flag2 = sign[pack.digit[j] - '0'];
                    if ((!flag1 && !flag2) || (flag1 && flag2)) continue;

                    if (i != j - 1)
                    {
                        string nextDigit;
                        for (int k = 0; k < 8; k++)
                        {
                            if (k == i) continue;
                            if (k == j) nextDigit += pack.digit[i];
                            nextDigit += pack.digit[k];
                        }
                        if (visited.count(nextDigit) == 0)
                        {
                            visited.insert(nextDigit);
                            q.push(package(nextDigit, pack.moves + 1));
                        }
                    }
                    if (i != j + 1)
                    {
                        string nextDigit;
                        for (int k = 0; k < 8; k++)
                        {
                            if (k == i) continue;
                            nextDigit += pack.digit[k];
                            if (k == j) nextDigit += pack.digit[i];
                        }
                        if (visited.count(nextDigit) == 0)
                        {
                            visited.insert(nextDigit);
                            q.push(package(nextDigit, pack.moves + 1));
                        }
                    }
                }
        }
        cout << best << '\n';
    }

    return 0;
}
