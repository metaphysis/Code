// Box
// UVa ID: 1587
// Verdict: Accepted
// Submission Date: 2019-02-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct pallet
{
    int w, h;
    pallet (int w = 0, int h = 0): w(w), h(h) {}
    bool operator<(const pallet &p) const
    {
        if (w != p.w) return w < p.w;
        return h < p.h;
    }
} pallets[6];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int w, h;
    while (cin >> w >> h)
    {
        if (w > h) swap(w, h);
        pallets[0] = pallet(w, h);
        for (int i = 1; i <= 5; i++)
        {
            cin >> w >> h;
            if (w > h) swap(w, h);
            pallets[i] = pallet(w, h);
        }
        sort(pallets, pallets + 6);
        bool possible =
            pallets[0].w == pallets[1].w && pallets[0].h == pallets[1].h &&
            pallets[2].w == pallets[3].w && pallets[2].h == pallets[3].h &&
            pallets[4].w == pallets[5].w && pallets[4].h == pallets[5].h &&
            pallets[0].w == pallets[2].w && ((pallets[0].h == pallets[4].w &&
            pallets[2].h == pallets[4].h) || (pallets[0].h == pallets[4].h &&
            pallets[2].h == pallets[4].w));
        cout << (possible ? "POSSIBLE" : "IMPOSSIBLE") << '\n';
    }

    return 0;
}
