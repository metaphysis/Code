// Quantiser
// UVa ID: 857
// Verdict: Accepted
// Submission Date: 2017-12-29
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct midi
{
    int idx, code, note, measure, beat, tick;
    bool operator==(const midi &m) const
    {
        return idx == m.idx;
    }
}midis[2010];

void quantise(midi &m)
{
    for (int i = 0, j = 30, k = 60; k <= 480; i += 60, j += 60, k += 60)
    {
        if (m.tick >= i && m.tick < j)
        {
            m.tick = i;
            break;
        }
        
        if (m.tick >= j && m.tick <= k)
        {
            m.tick = k;
            break;
        }
    }
    
    if (m.tick == 480) m.tick = 0, m.beat += 1;
    if (m.beat == 5) m.beat = 1, m.measure += 1;
}

bool cmp1(midi &m1, midi &m2)
{
    if (m1.note != m2.note) return m1.note < m2.note;
    if (m1.measure != m2.measure) return m1.measure < m2.measure;
    if (m1.beat != m2.beat) return m1.beat < m2.beat;
    if (m1.tick != m2.tick) return m1.tick < m2.tick;
    return m1.idx < m2.idx;
}

bool cmp2(midi &m1, midi &m2)
{
    return m1.idx < m2.idx;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    while (cin >> n)
    {
        if (n == -1) { cout << n << '\n'; break; }

        for (int i = 0; i < n; i++)
        {
            midis[i].idx = i;
            cin >> midis[i].code >> midis[i].note >> midis[i].measure;
            cin >> midis[i].beat >> midis[i].tick;
            quantise(midis[i]);
        }
        
        sort(midis, midis + n, cmp1);
        for (int i = n - 1, j = n - 2; j >= 0; i--, j--)
        {
            if (midis[i].code == 0 && midis[j].code == 1 &&
                midis[i].note == midis[j].note &&
                midis[i].measure == midis[j].measure &&
                midis[i].beat == midis[j].beat &&
                midis[i].tick == midis[j].tick)
            {
                midis[i].idx = midis[j].idx = 0x3fffffff;
            }
        }
        sort(midis, midis + n, cmp2);
        n = unique(midis, midis + n) - midis;
        if (midis[n - 1].idx == 0x3fffffff) n--;
        cout << n << '\n';
        for (int i = 0; i < n; i++)
        {
            cout << midis[i].code << ' ' << midis[i].note << ' ' << midis[i].measure;
            cout << ' ' << midis[i].beat << ' ' << midis[i].tick << '\n';
        }
    }

    return 0;
}
