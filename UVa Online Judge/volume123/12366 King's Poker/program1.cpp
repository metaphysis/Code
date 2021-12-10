// King's Poker
// UVa ID: 12366
// Verdict: Accepted
// Submission Date: 2021-12-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int SET = 3, PAIR = 2, UNPAIR = 1;

struct hand
{
    int A, B, C;
    hand (int a = 0, int b = 0, int c = 0)
    {
        A = a, B = b, C = c;
        if (A > B) swap(A, B);
        if (B > C) swap(B, C);
        if (A > B) swap(A, B);
    }
    int getRank() const
    {
        if (A == B && B == C) return SET;
        if (A == B || B == C) return PAIR;
        return UNPAIR;
    }
    bool operator<(const hand& h) const
    {
        int r1 = getRank(), r2 = h.getRank();
        if (r1 != r2) return r1 < r2;
        if (r1 == SET) return A < h.A;
        if (r1 == UNPAIR)
        {
            if (A != h.A) return A < h.A;
            if (B != h.B) return B < h.B;
            return C < h.C;
        }
        r1 = A == B ? A : B;
        r2 = h.A == h.B ? h.A : h.B;
        if (r1 != r2) return r1 < r2;
        r1 = A == B ? C : A;
        r2 = h.A == h.B ? h.C : h.A;
        return r1 < r2;
    }
    bool operator==(const hand &h) const
    {
        return A == h.A && B == h.B && C == h.C;
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    vector<hand> hands;
    for (int i = 1; i <= 13; i++)
        for (int j = 1; j <= 13; j++)
            for (int k = 1; k <= 13; k++)
                hands.push_back(hand(i, j, k));
    sort(hands.begin(), hands.end());
    hands.erase(unique(hands.begin(), hands.end()), hands.end());

    //for (int i = 0; i < hands.size(); i++)
    //    cout << hands[i].A << ' ' << hands[i].B << ' ' << hands[i].C << '\n';
    //return 0;

    int A, B, C;
    while (cin >> A >> B >> C)
    {
        if (A == 0) break;
        hand h = hand(A, B, C);
        if (h.getRank() == UNPAIR) cout << "1 1 2\n";
        else
        {
            int k = upper_bound(hands.begin(), hands.end(), h) - hands.begin();
            if (k >= hands.size()) cout << "*\n";
            else cout << hands[k].A << ' ' << hands[k].B << ' ' << hands[k].C << '\n';
        }
    }

    return 0;
}
