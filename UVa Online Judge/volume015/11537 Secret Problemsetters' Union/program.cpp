// Secret Problemsetters' Union
// UVa ID: 11537
// Verdict: Accepted
// Submission Date: 2026-07-31
// UVa Run Time: 0.280s

#include <bits/stdc++.h>
using namespace std;

const int maxRating = 100007;
const int level0Size = (maxRating + 63) / 64;
const int level1Size = (level0Size + 63) / 64;

struct ProblemBank {
    vector<int> count;
    unsigned long long level0[level0Size];
    unsigned long long level1[level1Size];
    unsigned long long level2;

    ProblemBank() : count(maxRating, 0), level2(0) {
        memset(level0, 0, sizeof(level0));
        memset(level1, 0, sizeof(level1));
    }

    void activateRating(int rating) {
        int level0Index = rating / 64;
        int level0Bit = rating % 64;
        unsigned long long level0Mask = 1ULL << level0Bit;
        if ((level0[level0Index] & level0Mask) != 0) return;
        level0[level0Index] |= level0Mask;

        int level1Index = level0Index / 64;
        int level1Bit = level0Index % 64;
        unsigned long long level1Mask = 1ULL << level1Bit;
        if ((level1[level1Index] & level1Mask) == 0) {
            level1[level1Index] |= level1Mask;
            level2 |= 1ULL << level1Index;
        }
    }

    void deactivateRating(int rating) {
        int level0Index = rating / 64;
        int level0Bit = rating % 64;
        level0[level0Index] &= ~(1ULL << level0Bit);
        if (level0[level0Index] != 0) return;

        int level1Index = level0Index / 64;
        int level1Bit = level0Index % 64;
        level1[level1Index] &= ~(1ULL << level1Bit);
        if (level1[level1Index] == 0) level2 &= ~(1ULL << level1Index);
    }

    void addProblem(int rating) {
        if (count[rating] == 0) activateRating(rating);
        ++count[rating];
    }

    int getHighestRating() const {
        int level1Index = 63 - __builtin_clzll(level2);
        unsigned long long level1Value = level1[level1Index];
        int level0Index = level1Index * 64 + 63 - __builtin_clzll(level1Value);
        unsigned long long level0Value = level0[level0Index];
        int rating = level0Index * 64 + 63 - __builtin_clzll(level0Value);
        return rating;
    }

    void clearBank() {
        fill(count.begin(), count.end(), 0);
        memset(level0, 0, sizeof(level0));
        memset(level1, 0, sizeof(level1));
        level2 = 0;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int testCaseCount;
    cin >> testCaseCount;

    for (int testCase = 1; testCase <= testCaseCount; ++testCase) {
        int problemSetterCount;
        cin >> problemSetterCount;

        vector<ProblemBank> banks(problemSetterCount + 1);
        char operation;

        while (cin >> operation) {
            if (operation == 'Q') break;

            if (operation == 'I') {
                int bankId;
                int problemCount;
                int initialRating;
                int multiplier;
                cin >> bankId >> problemCount >> initialRating >> multiplier;

                long long currentRating = initialRating;
                for (int index = 1; index <= problemCount; ++index) {
                    currentRating = (currentRating + 1LL * index * multiplier) % maxRating;
                    banks[bankId].addProblem(static_cast<int>(currentRating));
                }
            } else if (operation == 'U') {
                int bankId;
                int problemCount;
                cin >> bankId >> problemCount;

                if (problemCount == 0) {
                    cout << "0 0\n";
                    continue;
                }

                int highestRating = banks[bankId].getHighestRating();
                int lowestRating = highestRating;
                int remainingCount = problemCount;

                while (remainingCount > 0) {
                    int currentRating = banks[bankId].getHighestRating();
                    int takeCount = min(remainingCount, banks[bankId].count[currentRating]);

                    banks[bankId].count[currentRating] -= takeCount;
                    remainingCount -= takeCount;
                    lowestRating = currentRating;

                    if (banks[bankId].count[currentRating] == 0) banks[bankId].deactivateRating(currentRating);
                }

                cout << highestRating << ' ' << lowestRating << '\n';
            } else if (operation == 'M') {
                for (int bankId = 2; bankId <= problemSetterCount; ++bankId) {
                    for (int rating = 0; rating < maxRating; ++rating) {
                        if (banks[bankId].count[rating] == 0) continue;

                        if (banks[1].count[rating] == 0) banks[1].activateRating(rating);
                        banks[1].count[rating] += banks[bankId].count[rating];
                    }

                    banks[bankId].clearBank();
                }
            }
        }

        if (testCase != testCaseCount) cout << '\n';
    }

    return 0;
}
