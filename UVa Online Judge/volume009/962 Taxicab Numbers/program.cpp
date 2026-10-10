// Taxicab Numbers
// UVa ID: 962
// Verdict: Accepted
// Submission Date: 2017-03-08
// UVa Run Time: 0.210s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

vector<long long> buildCabNumbers(long long maxValue) {
    vector<long long> sums, cabNumbers;
    long long maxBase = 1;
    while ((maxBase + 1) * (maxBase + 1) * (maxBase + 1) <= maxValue)
        ++maxBase;
    for (long long a = 1; a <= maxBase; ++a) {
        long long cubeA = a * a * a;
        for (long long b = a; b <= maxBase; ++b) {
            long long cubeB = b * b * b, sum = cubeA + cubeB;
            if (sum > maxValue)
                break;
            sums.push_back(sum);
        }
    }
    sort(sums.begin(), sums.end());
    for (int i = 0; i < sums.size();) {
        int j = i + 1;
        while (j < sums.size() && sums[j] == sums[i])
            ++j;
        if (j - i >= 2)
            cabNumbers.push_back(sums[i]);
        i = j;
    }
    return cabNumbers;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<pair<long long, long long>> queries;
    long long n1, rg, maxValue = 0;
    while (cin >> n1 >> rg) {
        queries.push_back({n1, rg});
        maxValue = max(maxValue, n1 + rg);
    }
    vector<long long> cabNumbers = buildCabNumbers(maxValue);
    for (const pair<long long, long long>& query : queries) {
        long long left = query.first, right = query.first + query.second;
        bool found = false;
        for (long long number : cabNumbers) {
            if (number < left)
                continue;
            if (number > right)
                break;
            cout << number << '\n';
            found = true;
        }
        if (!found)
            cout << "None\n";
    }
    return 0;
}
