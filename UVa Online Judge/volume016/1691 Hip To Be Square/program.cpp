#include <bits/stdc++.h>
using namespace std;

typedef unsigned __int128 U128;

struct Item {
    int mask;
    long long value;
};

vector<int> primes;

U128 getMul(U128 value, long long factor, U128 inf) {
    if (value >= inf)
        return inf;
    if (value > inf / factor)
        return inf;
    return value * factor;
}

U128 getSqrt(U128 value) {
    U128 left = 0, right = (U128)1 << 63;
    while (left + 1 < right) {
        U128 mid = (left + right) >> 1;
        if (mid <= value / mid)
            left = mid;
        else
            right = mid;
    }
    return left;
}

void printU128(U128 value) {
    string result;
    if (value == 0) {
        cout << "0\n";
        return;
    }
    while (value > 0) {
        result.push_back(char('0' + value % 10));
        value /= 10;
    }
    reverse(result.begin(), result.end());
    cout << result << '\n';
}

void initPrimes() {
    vector<bool> isPrime(71, true);
    isPrime[0] = false;
    isPrime[1] = false;
    for (int i = 2; i * i <= 70; i++)
        if (isPrime[i])
            for (int j = i * i; j <= 70; j += i)
                isPrime[j] = false;
    for (int i = 2; i <= 70; i++)
        if (isPrime[i])
            primes.push_back(i);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    initPrimes();
    int a, b;
    const U128 inf = (U128)1 << 126;
    while (cin >> a >> b) {
        int root = sqrt(a);
        while (root * root < a)
            root++;
        if (root * root <= b) {
            cout << root << '\n';
            continue;
        }
        int limit = sqrt(b);
        vector<vector<pair<int, int>>> groups(b + 1);
        vector<Item> rawItems;
        for (int value = a; value <= b; value++) {
            int rest = value, mask = 0;
            for (int i = 0; i < (int)primes.size() && primes[i] <= limit; i++) {
                int count = 0, prime = primes[i];
                while (rest % prime == 0) {
                    rest /= prime;
                    count ^= 1;
                }
                if (count)
                    mask |= 1 << i;
            }
            if (rest == 1)
                rawItems.push_back({mask, value});
            else
                groups[rest].push_back({mask, value});
        }
        for (int value = 1; value <= b; value++) {
            if (groups[value].size() == 2) {
                int mask = groups[value][0].first ^ groups[value][1].first;
                long long product = 1LL * groups[value][0].second * groups[value][1].second;
                rawItems.push_back({mask, product});
            }
        }
        int usedMask = 0;
        for (const Item &item : rawItems)
            usedMask |= item.mask;
        vector<int> bitId(primes.size(), -1);
        int bitCount = 0;
        for (int i = 0; i < (int)primes.size(); i++) {
            if (usedMask & (1 << i)) {
                bitId[i] = bitCount;
                bitCount++;
            }
        }
        vector<Item> items;
        U128 answer = inf;
        for (Item item : rawItems) {
            int newMask = 0;
            for (int i = 0; i < (int)primes.size(); i++)
                if ((item.mask & (1 << i)) && bitId[i] != -1)
                    newMask |= 1 << bitId[i];
            if (newMask == 0) {
                if ((U128)item.value < answer)
                    answer = item.value;
            } else {
                item.mask = newMask;
                items.push_back(item);
            }
        }
        sort(items.begin(), items.end(), [](const Item &x, const Item &y) {
            if (x.mask != y.mask)
                return x.mask < y.mask;
            return x.value < y.value;
        });
        vector<Item> keptItems;
        for (int i = 0; i < (int)items.size();) {
            int j = i;
            while (j < (int)items.size() && items[j].mask == items[i].mask)
                j++;
            keptItems.push_back(items[i]);
            if (i + 1 < j)
                keptItems.push_back(items[i + 1]);
            i = j;
        }
        int stateCount = 1 << bitCount;
        vector<U128> dp(stateCount, inf);
        for (const Item &item : keptItems) {
            int mask = item.mask;
            for (int cur = 0; cur < stateCount; cur++) {
                int next = cur ^ mask;
                if (cur < next) {
                    U128 leftValue = dp[cur], rightValue = dp[next];
                    U128 newLeft = min(leftValue, getMul(rightValue, item.value, inf));
                    U128 newRight = min(rightValue, getMul(leftValue, item.value, inf));
                    dp[cur] = newLeft;
                    dp[next] = newRight;
                }
            }
            if ((U128)item.value < dp[mask])
                dp[mask] = item.value;
        }
        if (dp[0] < answer)
            answer = dp[0];
        if (answer == inf)
            cout << "none\n";
        else
            printU128(getSqrt(answer));
    }
    return 0;
}
