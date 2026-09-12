#include <bits/stdc++.h>
using namespace std;

struct City {
    string name;
    long long population, x, y;
};

long long getDistance(const City &a, const City &b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

long long getCost(const vector<City> &cities, const vector<City> &services, int closeMask) {
    long long totalCost = 0;
    for (const City &city : cities) {
        long long minDistance = numeric_limits<long long>::max();
        for (int i = 0; i < static_cast<int>(services.size()); ++i)
            if ((closeMask & (1 << i)) == 0)
                minDistance = min(minDistance, getDistance(city, services[i]));
        totalCost += city.population * minDistance;
    }
    return totalCost;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int cityCount;
    bool firstCase = true;
    while (cin >> cityCount) {
        vector<City> cities(cityCount);
        map<string, int> cityIndex;
        for (int i = 0; i < cityCount; ++i) {
            cin >> cities[i].name >> cities[i].population >> cities[i].x >> cities[i].y;
            cityIndex[cities[i].name] = i;
        }
        int serviceCount;
        cin >> serviceCount;
        vector<City> services(serviceCount);
        for (int i = 0; i < serviceCount; ++i) {
            string serviceName;
            cin >> serviceName;
            services[i] = cities[cityIndex[serviceName]];
        }
        int closeCount;
        cin >> closeCount;
        long long bestCost = numeric_limits<long long>::max();
        vector<string> bestNames;
        int totalMasks = 1 << serviceCount;
        for (int closeMask = 0; closeMask < totalMasks; ++closeMask) {
            if (__builtin_popcount(static_cast<unsigned int>(closeMask)) != closeCount)
                continue;
            long long currentCost = getCost(cities, services, closeMask);
            vector<string> currentNames;
            for (int i = 0; i < serviceCount; ++i)
                if (closeMask & (1 << i))
                    currentNames.push_back(services[i].name);
            sort(currentNames.begin(), currentNames.end());
            if (currentCost < bestCost || currentCost == bestCost && currentNames < bestNames) {
                bestCost = currentCost;
                bestNames = currentNames;
            }
        }
        if (!firstCase)
            cout << '\n';
        firstCase = false;
        for (const string &name : bestNames)
            cout << name << '\n';
    }
    return 0;
}
