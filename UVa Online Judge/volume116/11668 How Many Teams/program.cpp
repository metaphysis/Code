// How Many Teams
// UVa ID: 11668
// Verdict: Accepted
// Submission Date: 2026-08-01
// UVa Run Time: 0.620s

#include <bits/stdc++.h>
using namespace std;

const int mod = 1234;
const int maxOne = 100;
const int maxTwo = 50;
const int maxThree = 33;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    int choose[maxOne + 1][maxOne + 1] = {};
    for (int i = 0; i <= maxOne; i++) {
        choose[i][0] = choose[i][i] = 1;
        for (int j = 1; j < i; j++)
            choose[i][j] = (choose[i - 1][j - 1] + choose[i - 1][j]) % mod;
    }
    int factorial[maxOne + 1] = {};
    factorial[0] = 1;
    for (int i = 1; i <= maxOne; i++)
        factorial[i] = factorial[i - 1] * i % mod;
    int stateSize = (maxOne + 1) * (maxTwo + 1) * (maxThree + 1);
    auto getIndex = [](int oneCount, int twoCount, int threeCount) {
        return (oneCount * (maxTwo + 1) + twoCount) * (maxThree + 1) + threeCount;
    };
    for (int caseNumber = 1; caseNumber <= testCount; caseNumber++) {
        int n, k;
        cin >> n >> k;
        map<string, int> departmentMap;
        for (int i = 0; i < n; i++) {
            string studentInfo;
            cin >> studentInfo;
            int splitPosition = studentInfo.find('-');
            string department = studentInfo.substr(splitPosition + 1);
            departmentMap[department]++;
        }
        int oneCount = 0;
        int twoCount = 0;
        int threeCount = 0;
        for (auto department : departmentMap) {
            if (department.second == 1)
                oneCount++;
            else if (department.second == 2)
                twoCount++;
            else
                threeCount++;
        }
        vector<int> currentValue(stateSize, 0);
        vector<int> nextValue(stateSize, 0);
        vector<int> stateMark(stateSize, 0);
        vector<int> currentStates;
        currentStates.push_back(getIndex(oneCount, twoCount, threeCount));
        currentValue[currentStates[0]] = 1;
        int stamp = 0;
        int teamCount = n / k;
        for (int team = 0; team < teamCount; team++) {
            stamp++;
            vector<int> nextStates;
            for (int stateIndex : currentStates) {
                int value = currentValue[stateIndex];
                int temp = stateIndex;
                int three = temp % (maxThree + 1);
                temp /= maxThree + 1;
                int two = temp % (maxTwo + 1);
                int one = temp / (maxTwo + 1);
                for (int x = 0; x <= min(one, k); x++) {
                    for (int y = 0; y <= min(two, k - x); y++) {
                        int z = k - x - y;
                        if (z > three)
                            continue;
                        int nextOne = one - x + y;
                        int nextTwo = two - y + z;
                        int nextThree = three - z;
                        int nextIndex = getIndex(nextOne, nextTwo, nextThree);
                        if (stateMark[nextIndex] != stamp) {
                            stateMark[nextIndex] = stamp;
                            nextStates.push_back(nextIndex);
                            nextValue[nextIndex] = 0;
                        }
                        long long ways = value;
                        ways = ways * choose[one][x] % mod;
                        ways = ways * choose[two][y] % mod;
                        ways = ways * choose[three][z] % mod;
                        nextValue[nextIndex] = (nextValue[nextIndex] + ways) % mod;
                    }
                }
            }
            currentStates.swap(nextStates);
            currentValue.swap(nextValue);
        }
        int answer = currentValue[getIndex(0, 0, 0)];
        for (auto department : departmentMap) {
            if (department.second == 2)
                answer = answer * factorial[2] % mod;
            else if (department.second == 3)
                answer = answer * factorial[3] % mod;
        }
        for (int i = 0; i < teamCount; i++)
            answer = answer * factorial[k] % mod;
        cout << "Case " << caseNumber << ": " << answer << '\n';
    }
    return 0;
}
