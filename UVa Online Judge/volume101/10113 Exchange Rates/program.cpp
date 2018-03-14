// Exchange Rates
// UVa ID: 10113
// Verdict: Accepted
// Submission Date: 2018-01-29
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

char prompt, equals;
int edges[64][64] = {0}, cnt = 1;
pair<int, int> rate[64][64];
map<string, int> indexer;
string item1, item2;
int number1, number2, visited[64], parent[64];
    
int gcd(int a, int b)
{
    if (a < b) swap(a, b);
    return b ? gcd(b, a % b) : a;
}

void dfs(int u)
{
    visited[u] = 1;
    for (int v = 1; v <= 60; v++)
        if (edges[u][v] && !visited[v])
        {
            parent[v] = u;
            dfs(v);
        }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> prompt, prompt != '.')
    {
        if (prompt == '!')
        {
            cin >> number1 >> item1 >> equals >> number2 >> item2;
            if (indexer.find(item1) == indexer.end())
            {
                indexer[item1] = cnt;
                cnt++;
            }
            if (indexer.find(item2) == indexer.end())
            {
                indexer[item2] = cnt;
                cnt++;
            }
            edges[indexer[item1]][indexer[item2]] = 1;
            edges[indexer[item2]][indexer[item1]] = 1;
            int g = gcd(number1, number2);
            number1 /= g, number2 /= g;
            rate[indexer[item1]][indexer[item2]] = make_pair(number1, number2);
            rate[indexer[item2]][indexer[item1]] = make_pair(number2, number1);
        }
        else
        {
            cin >> item1 >> equals >> item2;
            memset(visited, 0, sizeof(visited));
            memset(parent, 0, sizeof(parent));
            dfs(indexer[item1]);
            if (visited[indexer[item2]])
            {
                number1 = number2 = 1;
                int v = indexer[item2];
                while (parent[v])
                {
                    int u = parent[v];
                    number1 *= rate[u][v].first, number2 *= rate[u][v].second;
                    int g = gcd(number1, number2);
                    number1 /= g, number2 /= g;
                    v = parent[v];
                }
                cout << number1 << ' ' << item1 << " = " << number2 << ' ' << item2 << '\n';
            }
            else cout << "? " << item1 << " = ? " << item2 << '\n';
        }
    }

    return 0;
}
