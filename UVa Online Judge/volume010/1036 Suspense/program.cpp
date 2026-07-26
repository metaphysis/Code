// Suspense
// UVa ID: 1036
// Verdict: Accepted
// Submission Date: 2026-07-25
// UVa Run Time: 0.000s
// https://blog.csdn.net/metaphysis/article/details/163183126

#include <bits/stdc++.h>
using namespace std;

struct DangerInterval {
    long double left;
    long double right;
};

long double calculateArcPart(long double a, long double heightDifference) {
    long double slope = 2.0L * sqrtl(a) * sqrtl(heightDifference);
    return (slope * sqrtl(1.0L + slope * slope) + asinhl(slope)) / (4.0L * a);
}

long double calculateCableLength(long double firstHeight, long double secondHeight, long double roadHeight, long double distance) {
    long double lowestHeight = roadHeight + 1.0L;
    long double firstDifference = firstHeight - lowestHeight;
    long double secondDifference = secondHeight - lowestHeight;
    long double coefficient = powl(sqrtl(firstDifference) + sqrtl(secondDifference), 2.0L) / (distance * distance);
    return calculateArcPart(coefficient, firstDifference) + calculateArcPart(coefficient, secondDifference);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseNumber = 1;
    int janFloor;
    int terezaFloor;
    long double distance;
    while (cin >> janFloor >> terezaFloor >> distance) {
        if (janFloor == 0 && terezaFloor == 0 && fabsl(distance) < 1e-12L)
            break;
        vector<char> janPets(janFloor);
        vector<char> terezaPets(terezaFloor);
        for (int i = 0; i < janFloor; i++)
            cin >> janPets[i];
        for (int i = 0; i < terezaFloor; i++)
            cin >> terezaPets[i];
        long double janHeight = 3.0L * janFloor - 2.0L;
        long double terezaHeight = 3.0L * terezaFloor - 2.0L;
        long double lowerBound = 1.0L;
        long double upperBound = min(janHeight, terezaHeight) - 2.0L;
        vector<long double> catHeights;
        vector<long double> birdHeights;
        for (int i = 0; i < janFloor; i++) {
            long double height = 3.0L * (i + 1) - 2.0L;
            if (janPets[i] == 'C')
                catHeights.push_back(height);
            if (janPets[i] == 'B')
                birdHeights.push_back(height);
        }
        for (int i = 0; i < terezaFloor; i++) {
            long double height = 3.0L * (i + 1) - 2.0L;
            if (terezaPets[i] == 'C')
                catHeights.push_back(height);
            if (terezaPets[i] == 'B')
                birdHeights.push_back(height);
        }
        vector<DangerInterval> dangerIntervals;
        for (long double catHeight : catHeights) {
            for (long double birdHeight : birdHeights) {
                long double left = max(catHeight - 3.0L, birdHeight - 0.5L);
                long double right = min(catHeight + 0.5L, birdHeight + 3.0L);
                if (left < right)
                    dangerIntervals.push_back({left, right});
        }
        sort(dangerIntervals.begin(), dangerIntervals.end(), [](const DangerInterval &first, const DangerInterval &second) {
            if (fabsl(first.left - second.left) > 1e-12L)
                return first.left < second.left;
            return first.right < second.right;
        });
        long double roadHeight = lowerBound;
        const long double epsilon = 1e-12L;
        for (const DangerInterval &interval : dangerIntervals) {
            if (roadHeight > interval.left + epsilon && roadHeight < interval.right - epsilon)
                roadHeight = interval.right;
        }
        cout << "Case " << caseNumber++ << ": ";
        if (roadHeight > upperBound + epsilon) {
            cout << "impossible\n";
            if (caseNumber > 2)
                cout << '\n';
            continue;
        }
        long double cableLength = calculateCableLength(janHeight, terezaHeight, roadHeight, distance);
        cout << fixed << setprecision(3) << static_cast<double>(cableLength) << '\n';
        if (caseNumber > 2)
            cout << '\n';
    }
    return 0;
}
