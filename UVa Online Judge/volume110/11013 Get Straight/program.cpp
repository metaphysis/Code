// Get Straight
// UVa ID: 11013
// Verdict: Accepted
// Submission Date: 2021-12-10
// UVa Run Time: 0.160s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

set<multiset<int>> _100, _10, _5, _3, _1;
map<string, int> c2n;
   
void prepare()
{
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

    int pre, nxt, pre1, nxt1;
    for (int i = 0; i <= 12; i++)
    {
        multiset<int> h;

        // 100
        for (int j = 0; j <= 4; j++) h.insert((i + j) % 13);
        _100.insert(h);

        // 10
        h.clear();
        pre = (i + 12) % 13, nxt = (i + 4) % 13;
        for (int j = 0; j <= 3; j++) h.insert((i + j) % 13);
        for (int k = 0; k <= 12; k++)
            if (k != pre && k != nxt)
            {
                h.insert(k);
                _10.insert(h);
                h.erase(h.find(k));
            }

        // 5
        h.clear();
        nxt = (i + 3) % 13;
        for (int j = 0; j <= 2; j++) h.insert((i + j) % 13);
        for (int j = 0; j <= 12; j++)
        {
            int c1 = j, c2 = (j + 1) % 13;
            if (c1 == pre || c1 == nxt || c2 == pre || c2 == nxt) continue;
            h.insert(c1);
            h.insert(c2);
            _5.insert(h);
            h.erase(h.find(c1));
            h.erase(h.find(c2));
        }
        
        // 3
        h.clear();
        nxt = (i + 3) % 13;
        for (int j = 0; j <= 2; j++) h.insert((i + j) % 13);
        for (int j = 0; j <= 12; j++)
            for (int k = 0; k <= 12; k++)
            {
                if ((j + 12) % 13 == k || (j + 1) % 13 == k) continue;
                if (j == pre || j == nxt || k == pre || k == nxt) continue;
                h.insert(j);
                h.insert(k);
                _3.insert(h);
                h.erase(h.find(j));
                h.erase(h.find(k));
            }

        // 1
        h.clear();
        nxt = (i + 2) % 13;
        for (int j = 0; j <= 1; j++) h.insert((i + j) % 13);
        for (int j = 0; j <= 12; j++)
        {
            int c1 = j, c2 = (j + 1) % 13;
            if (c1 == pre || c1 == nxt || c2 == pre || c2 == nxt) continue;
            h.insert(c1);
            h.insert(c2);
            pre1 = (c1 + 12) % 13, nxt1 = (c2 + 1) % 13;
            for (int k = 0; k <= 12; k++)
            {
                if (k == pre || k == nxt || k == pre1 || k == nxt1) continue;
                h.insert(k);
                _1.insert(h);
                h.erase(h.find(k));
            }
            h.erase(h.find(c1));
            h.erase(h.find(c2));
        }
    }
}

int getPayment(int ns[5])
{
    multiset<int> h;
    for (int i = 0; i < 5; i++) h.insert(ns[i]);
    if (_100.count(h)) return 100;
    if (_10.count(h)) return 10;
    if (_5.count(h)) return 5;
    if (_3.count(h)) return 3;
    if (_1.count(h)) return 1;
    return 0;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    prepare();

    string cards[5];
    int used[52], ns[5];
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
        int stay = getPayment(ns) * 47 - 47;
        for (int i = 0; i < 5; i++)
        {
            int best = 0;
            for (int j = 0; j < 52; j++)
            {
                if (used[j]) continue;
                for (int k = 0; k < 5; k++) ns[k] = c2n[cards[k]] / 4;
                ns[i] = j / 4;
                best += getPayment(ns);
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
