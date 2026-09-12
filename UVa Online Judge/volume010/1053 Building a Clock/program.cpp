#include <bits/stdc++.h>
using namespace std;

const int inf = INT_MAX;
const double eps = 1e-9;

using Gear = pair<char, int>;
using GearSet = set<Gear>;

struct Result {
    int shaftCount, gearCount;
    string key, hourPlan, minutePlan;

    Result(int shafts = inf, int gears = inf, string solutionKey = "", string hour = "", string minute = "")
        : shaftCount(shafts), gearCount(gears), key(solutionKey), hourPlan(hour), minutePlan(minute) {}
};

vector<string> hourPlans, minutePlans;

Result validate(const string &hourPlan, const string &minutePlan) {
    set<char> usedGears;
    int shaftCount = 0, gearCount = 0;
    int commonEnd = 0;
    int commonLimit = min(minutePlan.length(), hourPlan.length());
    while (commonEnd < commonLimit && minutePlan[commonEnd] == hourPlan[commonEnd]) {
        if (minutePlan[commonEnd] == '-') ++shaftCount;
        else ++gearCount;
        ++commonEnd;
    }
    if (commonEnd > 0 && minutePlan[commonEnd - 1] == '-') {
        --shaftCount;
        --commonEnd;
    }
    auto checkSuffix = [&](const string &plan) {
        for (int i = commonEnd; i < plan.length(); ++i) {
            char gear = plan[i];
            if (gear == '-') {
                ++shaftCount;
                continue;
            }
            if (usedGears.find(gear) != usedGears.end()) return false;
            usedGears.insert(gear);
            ++gearCount;
        }
        return true;
    };
    if (!checkSuffix(minutePlan) || !checkSuffix(hourPlan)) return Result();
    string key = minutePlan + hourPlan;
    key.erase(remove(key.begin(), key.end(), '-'), key.end());
    return Result(shaftCount, gearCount, key, hourPlan, minutePlan);
}

void generateAnd(string oldPlan, double rate, int teeth, GearSet &gears);

void addPlan(const string &plan, double rate) {
    if (abs(rate - 2) < eps) hourPlans.push_back(plan);
    else if (abs(rate - 24) < eps) minutePlans.push_back(plan);
}

void generatePlus(string oldPlan, double rate, int teeth, GearSet &gears) {
    for (const Gear &gear : gears) {
        GearSet remaining = gears;
        remaining.erase(gear);
        double newRate = -rate * teeth / gear.second;
        string nextPlan = oldPlan + '-' + gear.first;
        addPlan(nextPlan, newRate);
        generatePlus(nextPlan, newRate, gear.second, remaining);
        generateAnd(oldPlan + gear.first, rate, gear.second, remaining);
    }
}

void generateAnd(string oldPlan, double rate, int teeth, GearSet &gears) {
    for (const Gear &gear : gears) {
        GearSet remaining = gears;
        remaining.erase(gear);
        double newRate = -rate * teeth / gear.second;
        string nextPlan = oldPlan + '-' + gear.first;
        addPlan(nextPlan, newRate);
        generatePlus(nextPlan, newRate, gear.second, remaining);
    }
}

bool isBetter(const Result &current, const Result &best) {
    if (current.shaftCount != best.shaftCount)
        return current.shaftCount < best.shaftCount;
    if (current.gearCount != best.gearCount)
        return current.gearCount < best.gearCount;
    if (current.key != best.key)
        return current.key < best.key;
    if (current.hourPlan != best.hourPlan)
        return current.hourPlan < best.hourPlan;
    return current.minutePlan < best.minutePlan;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseNumber = 0;
    while (true) {
        int n;
        cin >> n;
        if (n == 0) return 0;
        if (caseNumber) cout << '\n';
        int inputRate;
        cin >> inputRate;
        GearSet gears;
        for (int i = 0; i < n; ++i) {
            char name;
            int teeth;
            cin >> name >> teeth;
            gears.emplace(name, teeth);
        }
        hourPlans.clear();
        minutePlans.clear();
        if (inputRate == 2) hourPlans.emplace_back();
        else if (inputRate == 24) minutePlans.emplace_back();
        for (const Gear &gear : gears) {
            GearSet remaining = gears;
            remaining.erase(gear);
            generateAnd(string(1, gear.first), inputRate, gear.second, remaining);
        }
        Result best;
        for (const string &hourPlan : hourPlans)
            for (const string &minutePlan : minutePlans) {
                Result current = validate(hourPlan, minutePlan);
                if (isBetter(current, best)) best = current;
            }
        ++caseNumber;
        if (best.shaftCount == inf) {
            cout << "Trial " << caseNumber << " IS IMPOSSIBLE\n";
            continue;
        }
        cout << "Trial " << caseNumber << '\n';
        cout << "Minutes: *" << best.minutePlan << '\n';
        cout << "Hours:   *" << best.hourPlan << '\n';
    }
}
