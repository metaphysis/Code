// Presidential Election
// UVa ID: 13113
// Verdict: Accepted
// Submission Date: 2021-12-29
// UVa Run Time: 0.130s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct voter
{
    int id;
    long long number;
    bool operator<(const voter &v)
    {
        if (number != v.number) return number > v.number;
        return id < v.id;
    }
} v[510];

long long getVote(int V, string percent)
{
    long long p = 0, d = 100;
    for (int i = 0; i < percent.length(); i++)
        if (isdigit(percent[i]))
            p = p * 10 + percent[i] - '0';
    size_t idx = percent.find('.');
    if (idx != percent.npos)
        for (int i = 0; i < (percent.length() - 1 - idx); i++)
            d *= 10;
    return V * p / d;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases;
    int A, B, V;
    long long VT;
    string Pi[510];
    
    cin >> cases;
    for (int cs = 0; cs < cases; cs++)
    {
        if (cs) cout << '\n';
        cin >> A >> B;
        for (int i = 0; i < A; i++)
            v[i].id = i, v[i].number = 0;
        VT = 0;
        for (int i = 0; i < B; i++)
        {
            for (int j = 0; j < A; j++)
                cin >> Pi[j];
            cin >> V;
            VT += V;
            for (int j = 0; j < A; j++)
                v[j].number += getVote(V, Pi[j]);
        }
        sort(v, v + A);
        cout << v[0].id + 1 << ' ' << v[0].number << '\n';
        if (A >= 2 && v[0].number < VT * 501 / 1000)
            cout << v[1].id + 1 << ' ' << v[1].number << '\n';
    }
    return 0;
}
