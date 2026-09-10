// Take Me Home (To the Place I Belong)
// UVa ID: 11252
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 0.100s

#include <bits/stdc++.h>
using namespace std;

struct BoxType {
    int size;
    int price;
};

long long getQuantityAtMost(const vector<int> &objectSizes, const vector<long long> &prefixQuantity, int limit) {
    int position = upper_bound(objectSizes.begin(), objectSizes.end(), limit) - objectSizes.begin();
    return prefixQuantity[position];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int extraCost;
    int boxCount;
    int objectTypeCount;
    int testCase = 1;

    while (cin >> extraCost >> boxCount >> objectTypeCount) {
        if (extraCost == 0 && boxCount == 0 && objectTypeCount == 0) break;

        vector<BoxType> boxTypes(boxCount);
        for (BoxType &boxType : boxTypes)
            cin >> boxType.size >> boxType.price;

        vector<pair<int, int>> objects(objectTypeCount);
        for (pair<int, int> &object : objects)
            cin >> object.first >> object.second;

        sort(boxTypes.begin(), boxTypes.end(), [](const BoxType &first, const BoxType &second) {
            if (first.size != second.size) return first.size > second.size;
            return first.price < second.price;
        });

        vector<BoxType> filteredBoxTypes;
        for (const BoxType &boxType : boxTypes)
            if (filteredBoxTypes.empty() || filteredBoxTypes.back().size != boxType.size)
                filteredBoxTypes.push_back(boxType);

        sort(objects.begin(), objects.end());

        vector<int> objectSizes;
        vector<long long> prefixQuantity(1, 0);

        for (const pair<int, int> &object : objects) {
            objectSizes.push_back(object.first);
            prefixQuantity.push_back(prefixQuantity.back() + object.second);
        }

        int boxTypeCount = filteredBoxTypes.size();
        int largestObjectSize = objectSizes.back();
        int smallestObjectSize = objectSizes.front();
        long long totalQuantity = prefixQuantity.back();
        const long long infinity = numeric_limits<long long>::max() / 4;

        vector<long long> dp(boxTypeCount, infinity);

        for (int i = 0; i < boxTypeCount; i++) {
            if (filteredBoxTypes[i].size < largestObjectSize) continue;

            long long uncoveredQuantity = totalQuantity - getQuantityAtMost(
                objectSizes,
                prefixQuantity,
                filteredBoxTypes[i].size
            );

            dp[i] = extraCost + uncoveredQuantity * filteredBoxTypes[i].price;
        }

        for (int i = 0; i < boxTypeCount; i++) {
            if (dp[i] == infinity) continue;

            for (int j = i + 1; j < boxTypeCount; j++) {
                if (filteredBoxTypes[j].price >= filteredBoxTypes[i].price) continue;

                long long middleQuantity = getQuantityAtMost(
                    objectSizes,
                    prefixQuantity,
                    filteredBoxTypes[i].size
                ) - getQuantityAtMost(
                    objectSizes,
                    prefixQuantity,
                    filteredBoxTypes[j].size
                );

                long long newCost = dp[i] + middleQuantity * filteredBoxTypes[i].price + extraCost;
                dp[j] = min(dp[j], newCost);
            }
        }

        long long answer = infinity;

        for (int i = 0; i < boxTypeCount; i++) {
            if (dp[i] == infinity) continue;
            if (filteredBoxTypes[i].size < smallestObjectSize) continue;

            long long smallQuantity = getQuantityAtMost(
                objectSizes,
                prefixQuantity,
                filteredBoxTypes[i].size
            );

            long long totalCost = dp[i] + smallQuantity * filteredBoxTypes[i].price;
            answer = min(answer, totalCost);
        }

        cout << "case " << testCase++ << ": ";
        if (answer == infinity)
            cout << "not possible\n";
        else
            cout << answer << '\n';
    }

    return 0;
}
