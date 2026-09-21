#include <bits/stdc++.h>
using namespace std;

struct Person {
    int birth, death, spouse = 0, marriage = INT_MAX;
    long long saving = 0, money = 0;
    vector<int> children;
};

int curYear;
long long stateMoney;
vector<Person> people;
vector<int> heirMemo;

bool isAlive(int id) {
    return id != 0 && people[id].birth <= curYear && curYear < people[id].death;
}

bool hasSpouse(int id) {
    return people[id].marriage <= curYear && isAlive(people[id].spouse);
}

bool canInherit(int id) {
    if (heirMemo[id] != -1) return heirMemo[id];
    if (people[id].birth > curYear) return heirMemo[id] = 0;
    if (isAlive(id) || hasSpouse(id)) return heirMemo[id] = 1;
    for (int child : people[id].children) if (canInherit(child)) return heirMemo[id] = 1;
    return heirMemo[id] = 0;
}

void distribute(int id, long long amount) {
    if (amount == 0) return;
    if (isAlive(id)) {
        people[id].money += amount;
        return;
    }
    vector<int> heirs;
    for (int child : people[id].children) if (canInherit(child)) heirs.push_back(child);
    bool spouseAlive = hasSpouse(id);
    if (heirs.empty()) {
        if (spouseAlive) people[people[id].spouse].money += amount;
        else stateMoney += amount;
        return;
    }
    if (spouseAlive) {
        people[people[id].spouse].money += amount / 2;
        amount /= 2;
    }
    long long share = amount / static_cast<long long>(heirs.size());
    if (share == 0) return;
    for (int child : heirs) distribute(child, share);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int queryYear, n;
    bool firstCase = true;
    while (cin >> queryYear >> n) {
        people.assign(n + 1, Person());
        vector<int> deathOrder(n);
        for (int i = 1; i <= n; ++i) {
            int father, mother;
            cin >> people[i].birth >> people[i].death >> father >> mother >> people[i].saving;
            if (father != 0) people[father].children.push_back(i);
            if (mother != 0) people[mother].children.push_back(i);
            if (father != 0 && mother != 0) {
                people[father].spouse = mother;
                people[mother].spouse = father;
                people[father].marriage = min(people[father].marriage, people[i].birth);
                people[mother].marriage = min(people[mother].marriage, people[i].birth);
            }
            deathOrder[i - 1] = i;
        }
        sort(deathOrder.begin(), deathOrder.end(), [](int a, int b) {
            return people[a].death < people[b].death;
        });
        stateMoney = 0;
        for (int id : deathOrder) {
            if (people[id].death > queryYear) break;
            curYear = people[id].death;
            heirMemo.assign(n + 1, -1);
            long long age = static_cast<long long>(people[id].death) - people[id].birth;
            long long fortune = people[id].money + people[id].saving * age;
            people[id].money = 0;
            distribute(id, fortune);
        }
        curYear = queryYear;
        int livingCount = 0;
        for (int i = 1; i <= n; ++i) if (isAlive(i)) ++livingCount;
        if (!firstCase) cout << '\n';
        firstCase = false;
        cout << stateMoney << '\n' << livingCount << '\n';
        for (int i = 1; i <= n; ++i) {
            if (!isAlive(i)) continue;
            long long age = static_cast<long long>(queryYear) - people[i].birth;
            cout << i << ' ' << people[i].money + people[i].saving * age << '\n';
        }
    }
    return 0;
}
