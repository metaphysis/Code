// Get Straight
// UVa ID: 11013
// Verdict: Accepted
// Submission Date: 2021-12-10
// UVa Run Time: 0.110s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int ns[5];
bool adjacent(int i) { return (ns[i] + 1) % 13 == ns[i + 1]; }
int getPayment()
{
    sort(ns, ns + 5);
    int p = 0;
    do
    {
        if (adjacent(0) && adjacent(1) && adjacent(2) && adjacent(3)) p = max(p, 100);
        if (adjacent(0) && adjacent(1) && adjacent(2)) p = max(p, 10);
        if (adjacent(0) && adjacent(1) && adjacent(3)) p = max(p, 5);
        if (adjacent(0) && adjacent(1)) p = max(p, 3);
        if (adjacent(0) && adjacent(2)) p = max(p, 1);   
    } while (next_permutation(ns, ns + 5));
    return p;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    map<string, int> c2n;

    char value[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
    char suit[4] = {'S', 'H', 'D', 'C'};

    for (int i = 0; i <= 12; i++)
        for (int j = 0; j <= 3; j++)
        {
            string s;
            s += value[i];
            s += suit[j];
            c2n[s] = i * 4 + j;
        }

    string cards[5];
    int used[52];
    while (cin >> cards[0])
    {
        if (cards[0] == "#") break;
        memset(used, 0, sizeof used);
        for (int i = 1; i < 5; i++) cin >> cards[i];
        for (int i = 0; i < 5; i++)
        {
            ns[i] = c2n[cards[i]] / 4;
            used[c2n[cards[i]]] = 1;
        }
        int idx = -1;
        int stay = getPayment() * 47 - 47;
        for (int i = 0; i < 5; i++)
        {
            int best = 0;
            for (int j = 0; j < 52; j++)
            {
                if (used[j]) continue;
                for (int k = 0; k < 5; k++) ns[k] = c2n[cards[k]] / 4;
                ns[i] = j / 4;
                best += getPayment();
            }
            best -= 94;
            if (best > stay)
            {
                stay = best;
                idx = i;
            }
        }
        if (idx >= 0) cout << "Exchange " << cards[idx];
        else cout << "Stay";
        cout << '\n';
    }
    return 0;
}
