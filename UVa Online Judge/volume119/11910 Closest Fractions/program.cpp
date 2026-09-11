// Closest Fractions
// UVa ID: 11910
// Verdict: Accepted
// Submission Date: 2026-07-31
// UVa Run Time: 0.130s


#include <bits/stdc++.h>
using namespace std;

int gcdInt(int a, int b) {
    while (b) { int t = a % b; a = b; b = t; }
    return a;
}

vector<tuple<long double, int, int>> generateSortedFractions() {
    vector<tuple<long double, int, int>> res;
    res.reserve(600000);
    for (int x = 1; x <= 1000; ++x)
        for (int y = 1; y <= 1000; ++y)
            if (gcdInt(x, y) == 1)
                res.emplace_back((long double)x / y, x, y);
    sort(res.begin(), res.end(),
         [](const tuple<long double,int,int>& a, const tuple<long double,int,int>& b) {
             return get<0>(a) < get<0>(b);
         });
    return res;
}

string formatFraction(int x, int y) {
    long double val = (long double)x / y;
    int intPart = (int)floor(val);
    int digitsInt = to_string(intPart).length();
    int digitsFrac = 10 - digitsInt;
    if (digitsFrac < 0) digitsFrac = 0;
    char buf[64];
    snprintf(buf, sizeof(buf), "%.*Lf", digitsFrac, val);
    return string(buf);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    auto fractions = generateSortedFractions();
    string s;
    while (cin >> s) {
        long double target = stold(s);
        auto it = lower_bound(fractions.begin(), fractions.end(), target,
            [](const tuple<long double,int,int>& elem, long double value) {
                return get<0>(elem) < value;
            });
        int pos = (int)(it - fractions.begin());
        int n = (int)fractions.size();
        int left = max(0, pos - 10);
        int right = min(n - 1, pos + 10);
        vector<tuple<long double, int, int>> candidates;
        candidates.reserve(right - left + 1);
        for (int i = left; i <= right; ++i) {
            long double val = get<0>(fractions[i]);
            candidates.emplace_back(fabsl(val - target), get<1>(fractions[i]), get<2>(fractions[i]));
        }
        sort(candidates.begin(), candidates.end());
        cout << "Input : " << s << "\n";
        for (int i = 0; i < 3; ++i) {
            int x = get<1>(candidates[i]);
            int y = get<2>(candidates[i]);
            cout << string(4, ' ') << (i + 1) << " : " << formatFraction(x, y)
                 << " = " << setw(4) << std::right << x << " / " << y << "\n";
        }
    }
    return 0;
}
