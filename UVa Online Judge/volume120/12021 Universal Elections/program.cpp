#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
using namespace std;
using boost::multiprecision::cpp_int;

struct Party {
    string name;
    long long vote, seats;
};

cpp_int getCount(const vector<Party>& parties, long long n, const cpp_int& scale, const cpp_int& value) {
    if (value == 0)
        return cpp_int(n);
    cpp_int count = 0, limit = n;
    for (const Party& party : parties) {
        if (party.vote == 0)
            continue;
        cpp_int current = cpp_int(party.vote) * scale / value;
        if (current > limit - count)
            return limit;
        count += current;
    }
    return count;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCases, p, i;
    long long n;
    cpp_int scale = 1;
    for (i = 0; i < 40; i++)
        scale *= 10;
    cin >> testCases;
    while (testCases--) {
        cin >> n >> p;
        string blankName, invalidName;
        long long blankVotes, invalidVotes;
        cin >> blankName >> blankVotes;
        cin >> invalidName >> invalidVotes;
        vector<Party> parties(p);
        long long totalVotes = 0;
        for (i = 0; i < p; i++) {
            cin >> parties[i].name >> parties[i].vote;
            parties[i].seats = 0;
            totalVotes += parties[i].vote;
        }
        if (n > 0 && totalVotes > 0) {
            cpp_int low = 0, high = cpp_int(totalVotes) * scale + 1;
            while (high - low > 1) {
                cpp_int mid = (low + high) / 2;
                if (getCount(parties, n, scale, mid) >= n)
                    low = mid;
                else
                    high = mid;
            }
            cpp_int threshold = low + 1;
            for (i = 0; i < p; i++) {
                if (parties[i].vote == 0)
                    continue;
                cpp_int current = cpp_int(parties[i].vote) * scale / threshold;
                if (current > n)
                    current = n;
                parties[i].seats = current.convert_to<long long>();
            }
            int bestIndex = -1;
            for (i = 0; i < p; i++) {
                if (parties[i].vote == 0)
                    continue;
                if (bestIndex == -1) {
                    bestIndex = i;
                    continue;
                }
                cpp_int left = cpp_int(parties[i].vote) * (parties[bestIndex].seats + 1);
                cpp_int right = cpp_int(parties[bestIndex].vote) * (parties[i].seats + 1);
                if (left > right)
                    bestIndex = i;
                else if (left == right && parties[i].name < parties[bestIndex].name)
                    bestIndex = i;
            }
            if (bestIndex != -1) {
                cpp_int bestVote = parties[bestIndex].vote;
                cpp_int bestDenominator = parties[bestIndex].seats + 1;
                long long assigned = 0;
                for (i = 0; i < p; i++) {
                    if (parties[i].vote == 0) {
                        parties[i].seats = 0;
                        continue;
                    }
                    cpp_int numerator = cpp_int(parties[i].vote) * bestDenominator;
                    cpp_int denominator = bestVote;
                    cpp_int current = 0;
                    if (numerator > denominator)
                        current = (numerator - 1) / denominator;
                    if (current > n)
                        current = n;
                    parties[i].seats = current.convert_to<long long>();
                    assigned += parties[i].seats;
                }
                long long remain = n - assigned;
                vector<int> tied;
                for (i = 0; i < p; i++) {
                    cpp_int left = cpp_int(parties[i].vote) * bestDenominator;
                    cpp_int right = bestVote * (parties[i].seats + 1);
                    if (left == right)
                        tied.push_back(i);
                }
                sort(tied.begin(), tied.end(), [&](int a, int b) {
                    return parties[a].name < parties[b].name;
                });
                for (i = 0; i < remain; i++)
                    parties[tied[i]].seats++;
            }
        }
        for (i = 0; i < p; i++)
            cout << parties[i].name << " " << parties[i].seats << "\n";
    }
    return 0;
}
