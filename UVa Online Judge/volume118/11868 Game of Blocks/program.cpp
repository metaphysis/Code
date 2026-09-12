#include <bits/stdc++.h>
using namespace std;

const long long mod = 100000007;

vector<long long> multiplyPoly(const vector<long long> &first, const vector<long long> &second, const vector<long long> &count) {
    int len = static_cast<int>(count.size()) - 1, i, j, d;
    long long value;
    vector<long long> result(2 * len - 1, 0);
    for (i = 0; i < len; i++)
        for (j = 0; j < len; j++)
            result[i + j] = (result[i + j] + first[i] * second[j]) % mod;
    for (i = 2 * len - 2; i >= len; i--) {
        value = result[i];
        if (value == 0)
            continue;
        for (d = 1; d <= len; d++)
            result[i - d] = (result[i - d] + value * count[d]) % mod;
    }
    result.resize(len);
    return result;
}

long long solveCase(int colorCount, const vector<int> &lengths, long long n) {
    int i, length, maxLen = 0;
    for (i = 0; i < colorCount; i++)
        maxLen = max(maxLen, lengths[i]);
    vector<long long> count(maxLen + 1, 0), initial(maxLen, 0);
    for (i = 0; i < colorCount; i++)
        count[lengths[i]]++;
    initial[0] = 1;
    for (i = 1; i < maxLen; i++) {
        for (length = 1; length <= i; length++)
            initial[i] = (initial[i] + count[length] * initial[i - length]) % mod;
    }
    vector<long long> result(maxLen, 0), base(maxLen, 0);
    result[0] = 1;
    if (maxLen == 1)
        base[0] = count[1];
    else
        base[1] = 1;
    while (n > 0) {
        if (n & 1)
            result = multiplyPoly(result, base, count);
        n >>= 1;
        if (n > 0)
            base = multiplyPoly(base, base, count);
    }
    long long answer = 0;
    for (i = 0; i < maxLen; i++)
        answer = (answer + result[i] * initial[i]) % mod;
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount, caseId, colorCount, i;
    long long n;
    cin >> testCount;
    for (caseId = 1; caseId <= testCount; caseId++) {
        cin >> colorCount;
        vector<int> lengths(colorCount);
        for (i = 0; i < colorCount; i++)
            cin >> lengths[i];
        cin >> n;
        cout << "Case " << caseId << ": " << solveCase(colorCount, lengths, n) << '\n';
    }
    return 0;
}
