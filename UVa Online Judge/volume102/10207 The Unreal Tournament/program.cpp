// The Unreal Tournament
// UVa ID: 10207
// Verdict: Accepted
// Submission Date: 2019-02-20
// UVa Run Time: 3.130s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1010;

int N, visited[MAXN][MAXN];
string call[MAXN][MAXN];
double pij[MAXN][MAXN], p;

string add(string number1, string number2)
{
    if (number1.length() < number2.length()) number1.swap(number2);
    number1.insert(number1.begin(), '0');

    int carry = 0, i = number1.length() - 1, j = number2.length() - 1;
    for (; i >= 0; i--, j--)
    {
        int sum = number1[i] - '0' + (j >= 0 ? (number2[j] - '0') : 0) + carry;
        number1[i] = sum % 10 + '0';
        carry = sum / 10;
    }

    while (number1.front() == '0' && number1.length() > 1) number1.erase(number1.begin());

    return number1;
}

void dfs(int i, int j)
{
    if (visited[i][j]) return;
    visited[i][j] = 1;
    if (i == 0)
    {
        pij[i][j] = 1;
        call[i][j] = "0";
        return;
    }
    if (j == 0)
    {
        pij[i][j] = 0;
        call[i][j] = "0";
        return;
    }
    dfs(i - 1, j);
    dfs(i, j - 1);
    call[i][j] = add(add(call[i - 1][j], call[i][j - 1]), "2");
    pij[i][j] = p * pij[i - 1][j] + (1 - p) * pij[i][j - 1];
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    while (cin >> p >> N)
    {
        if (N == 0) break;
        if (cases++) cout << '\n';
        memset(visited, 0, sizeof(visited));
        vector<pair<int, int>> ij;
        int maxi = 0, maxj = 0;
        for (int n = 0, i, j; n < N; n++)
        {
            cin >> i >> j;
            maxi = max(maxi, i);
            maxj = max(maxj, j);
            ij.push_back(make_pair(i, j));
        }
        dfs(maxi, maxj);
        for (auto p : ij)
        {
            int i = p.first, j = p.second;
            if (i == 0 && j == 0)
                cout << "-1.00000\n0\n";
            else
            {
                cout << fixed << setprecision(5) << pij[i][j] << '\n';
                cout << call[i][j] << '\n';
            }
        }
    }

    return 0;
}
