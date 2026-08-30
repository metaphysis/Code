#include <bits/stdc++.h>
using namespace std;

struct Activity {
    char name;
    long long fixedCost, variableCost;
};

struct Country {
    long long people;
    bool applicable[5];
    int efficiency[5];
};

int activityCount, countryCount;
long long budget, answer;
Activity activities[5];
Country countries[10];

void dfs(int index, int usedMask, long long cost, long long people) {
    if (index == activityCount) {
        answer = max(answer, people);
        return;
    }
    dfs(index + 1, usedMask, cost, people);
    for (int i = 0; i < countryCount; i++) {
        if (!countries[i].applicable[index] || (usedMask & (1 << i)))
            continue;
        long long activityCost = activities[index].fixedCost * 1000 + activities[index].variableCost * countries[i].people;
        if (cost + activityCost > budget)
            continue;
        long long attracted = (countries[i].people * countries[i].efficiency[index] + 50) / 100;
        dfs(index + 1, usedMask | (1 << i), cost + activityCost, people + attracted);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        long long money;
        cin >> activityCount >> countryCount >> money;
        budget = money * 1000000;
        for (int i = 0; i < activityCount; i++)
            cin >> activities[i].name >> activities[i].fixedCost >> activities[i].variableCost;
        for (int i = 0; i < countryCount; i++) {
            int applicableCount;
            cin >> applicableCount >> countries[i].people;
            for (int j = 0; j < activityCount; j++) {
                countries[i].applicable[j] = false;
                countries[i].efficiency[j] = 0;
            }
            for (int j = 0; j < applicableCount; j++) {
                char name;
                string efficiency;
                cin >> name >> efficiency;
                efficiency.pop_back();
                int activityIndex = 0;
                while (activities[activityIndex].name != name)
                    activityIndex++;
                countries[i].applicable[activityIndex] = true;
                countries[i].efficiency[activityIndex] = stoi(efficiency);
            }
        }
        answer = 0;
        dfs(0, 0, 0, 0);
        cout << answer << '\n';
    }
    return 0;
}
