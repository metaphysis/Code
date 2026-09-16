#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using boost::multiprecision::cpp_int;

int lcm(int a, int b) {
    return a / __gcd(a, b) * b;
}

cpp_int getCount(const vector<cpp_int>& diff, long long k) {
    int degree = static_cast<int>(diff.size()) - 1;
    cpp_int result = 0, comb = 1;
    for (int i = 0; i <= degree; ++i) {
        result += diff[i] * comb;
        if (i < degree)
            comb = comb * (k - i) / (i + 1);
    }
    return result;
}

vector<cpp_int> buildDifference(const vector<cpp_int>& values) {
    vector<cpp_int> current = values, diff;
    while (!current.empty()) {
        diff.push_back(current[0]);
        vector<cpp_int> next;
        for (int i = 1; i < static_cast<int>(current.size()); ++i)
            next.push_back(current[i] - current[i - 1]);
        current = next;
    }
    while (diff.size() > 1 && diff.back() == 0)
        diff.pop_back();
    return diff;
}

long long getAnswer(const vector<int>& weights, long long people) {
    int n = static_cast<int>(weights.size()), period = 1;
    for (int weight : weights)
        period = lcm(period, weight);
    int degree = n - 1, maxWeight = period * (degree + 1) - 1;
    vector<cpp_int> dp(maxWeight + 1, 0);
    dp[0] = 1;
    for (int weight : weights)
        for (int sum = weight; sum <= maxWeight; ++sum)
            dp[sum] += dp[sum - weight];
    long long limit = people * 100LL, answer = LLONG_MAX;
    for (int remainder = 0; remainder < period; ++remainder) {
        if (remainder > limit)
            continue;
        vector<cpp_int> values;
        for (int j = 0; j <= degree; ++j)
            values.push_back(dp[remainder + j * period]);
        vector<cpp_int> diff = buildDifference(values);
        long long minK = remainder == 0 ? 1 : 0;
        long long maxK = (limit - remainder) / period;
        if (maxK < minK)
            continue;
        if (getCount(diff, maxK) < people)
            continue;
        long long left = minK, right = maxK;
        while (left < right) {
            long long middle = left + (right - left) / 2;
            if (getCount(diff, middle) >= people)
                right = middle;
            else
                left = middle + 1;
        }
        answer = min(answer, remainder + left * period);
    }
    return answer == LLONG_MAX ? -1 : answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, setId = 1;
    while (cin >> n && n != 0) {
        vector<int> weights(n);
        for (int& weight : weights)
            cin >> weight;
        int q;
        cin >> q;
        cout << "Set " << setId++ << '\n';
        while (q--) {
            long long people;
            cin >> people;
            long long answer = getAnswer(weights, people);
            if (answer == -1)
                cout << "no candy for you\n";
            else
                cout << answer << '\n';
        }
    }
    return 0;
}
