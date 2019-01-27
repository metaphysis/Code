// Constrained Exchange Sort
// UVa ID: 10073
// Verdict: TLE
// Submission Date: 2019-01-27
// UVa Run Time: 20.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct data
{
    long long s, m1, m2;
    short pre, idx, cnt;
    data(long long s = 0, long long m1 = 0, long long m2 = 0, short pre = 0, short idx = 0, short cnt = 0): s(s), m1(m1), m2(m2), pre(pre), idx(idx), cnt(cnt) {}
};

vector<int> offset[13];

map<long long, pair<long long, long long>> cache;

inline long long swap(long long s, short idx, short nexti)
{
    long long lmask = (15LL << (4 * (idx - 1))), rmask = (15LL << (4 * (nexti - 1)));
    long long nexts = s & (~(lmask | rmask));
    nexts |= (((s & lmask) >> (4 * (idx - 1))) << (4 * (nexti - 1)));
    nexts |= (((s & rmask) >> (4 * (nexti - 1))) << (4 * (idx - 1)));
    return nexts;
}

inline void setMove(data &d, long long &nextm1, long long &nextm2, short idx)
{
    nextm1 = d.m1, nextm2 = d.m2;
    if (d.cnt < 16)
        nextm1 = (nextm1 << 4) | (d.s & (15LL << (4 * (idx - 1)))) >> (4 * (idx - 1));
    else
        nextm2 = (nextm2 << 4) | (d.s & (15LL << (4 * (idx - 1)))) >> (4 * (idx - 1));
}

void print(long long m1, long long m2, long long nextm1, long long nextm2)
{
    string seq;
    while (m2)
    {
        int alpha = (m2 & 15LL);
        seq.insert(seq.begin(), 'A' + alpha - 1);
        m2 = m2 >> 4;
    }
    while (m1)
    {
        int alpha = (m1 & 15LL);
        seq.insert(seq.begin(), 'A' + alpha - 1);
        m1 = m1 >> 4;
    }
    while (nextm2)
    {
        int alpha = (nextm2 & 15LL);
        seq.push_back('A' + alpha - 1);
        nextm2 = nextm2 >> 4;
    }
    while (nextm1)
    {
        int alpha = (nextm1 & 15LL);
        seq.push_back('A' + alpha - 1);
        nextm1 = nextm1 >> 4;
    }
    cout << seq << '\n';
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int di[4] = {1, 3, 6, 12};
    for (int i = 1; i <= 12; i++)
        for (int j = 0; j <= 2; j++)
        {
            int nextd = i + di[j];
            if (nextd >= 1 && nextd <= 12)
                if ((i - 1) / di[j + 1] == (nextd - 1) / di[j + 1])
                    offset[i].push_back(nextd);
            nextd = i - di[j];
            if (nextd >= 1 && nextd <= 12)
                if ((i - 1) / di[j + 1] == (nextd - 1) / di[j + 1])
                    offset[i].push_back(nextd);
        }

    long long nexts, nextm1, nextm2;
    data d = data(0x123456789ABC, 0, 0, -1, 1, 0);
    queue<data> q;
    q.push(d);
    cache[d.s] = make_pair(0, 0);
    while (!q.empty())
    {
        d = q.front(); q.pop();
        if (d.cnt >= 15) continue;
        for (auto nexti : offset[d.idx])
            if (nexti != d.pre)
            {
                nexts = swap(d.s, d.idx, nexti);
                if (cache.find(nexts) == cache.end())
                {
                    setMove(d, nextm1, nextm2, nexti);
                    cache[nexts] = make_pair(nextm1, nextm2);
                    q.push(data(nexts, nextm1, nextm2, d.idx, nexti, d.cnt + 1));
                }
            }
    }

    int cases;
    cin >> cases;
    string seq;
    for (int cs = 1; cs <= cases; cs++)
    {
        cout << "Permutation #" << cs << '\n';
        cin >> seq;
        long long s = 0;
        short idx = -1;
        for (int i = 0; i < seq.length(); i++)
        {
            if (seq[i] == 'L') idx = seq.length() - i;
            s = (s << 4) | (seq[i] - 'A' + 1);
        }

        if (cache.find(s) != cache.end())
        {
            pair<long long, long long> p = cache[s];
            print(0, 0, p.first, p.second);
            cout << '\n';
            continue;
        }

        data dd = data(s, 0, 0, -1, idx, 0);
        queue<data> qq;
        qq.push(dd);
        while (!qq.empty())
        {
            dd = qq.front(); qq.pop();
            for (auto nexti : offset[dd.idx])
                if (nexti != dd.pre)
                {
                    nexts = swap(dd.s, dd.idx, nexti);
                    setMove(dd, nextm1, nextm2, nexti);
                    if (cache.find(nexts) != cache.end())
                    {
                        pair<long long, long long> p = cache[nexts];
                        print(nextm1, nextm2, p.first, p.second);
                        goto out;
                    }
                    else
                    {
                        qq.push(data(nexts, nextm1, nextm2, dd.idx, nexti, dd.cnt + 1));
                    }
                }
        }
        out:
        cout << '\n';
    }

    return 0;
}
