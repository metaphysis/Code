#include <bits/stdc++.h>
using namespace std;

const long long negValue = -(1LL << 60);

struct Item {
    int cost, happy;
    vector<int> children;
};

struct TempItem {
    string name, parent;
    int cost, happy;
};

struct DpState {
    vector<long long> values;
    int maxCost;
};

vector<Item> items;
int cashLimit;

DpState dfsTree(int node) {
    DpState current;
    current.values.assign(cashLimit + 1, negValue);
    current.maxCost = -1;
    if (node == 0) {
        current.values[0] = 0;
        current.maxCost = 0;
    } else {
        if (items[node].cost > cashLimit) return current;
        current.values[items[node].cost] = items[node].happy;
        current.maxCost = items[node].cost;
    }
    for (int child : items[node].children) {
        DpState childState = dfsTree(child);
        if (childState.maxCost < 0) continue;
        vector<long long> nextValues = current.values;
        int nextMaxCost = min(cashLimit, current.maxCost + childState.maxCost);
        for (int usedCost = 0; usedCost <= current.maxCost; usedCost++) {
            if (current.values[usedCost] == negValue) continue;
            int maxAddCost = min(childState.maxCost, cashLimit - usedCost);
            for (int addCost = 0; addCost <= maxAddCost; addCost++) {
                if (childState.values[addCost] == negValue) continue;
                long long candidate = current.values[usedCost] + childState.values[addCost];
                if (candidate > nextValues[usedCost + addCost]) nextValues[usedCost + addCost] = candidate;
            }
        }
        current.values = move(nextValues);
        current.maxCost = nextMaxCost;
    }
    return current;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    int caseCount = 0;
    while (getline(cin, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.empty()) continue;
        if (line == "#") break;
        string fanName;
        int cash;
        stringstream headerStream(line);
        headerStream >> fanName >> cash;
        vector<TempItem> tempItems;
        while (getline(cin, line)) {
            if (!line.empty() && line.back() == '\r') line.pop_back();
            if (line == "%") break;
            if (line.empty()) continue;
            TempItem tempItem;
            stringstream itemStream(line);
            itemStream >> tempItem.name >> tempItem.parent >> tempItem.cost >> tempItem.happy;
            tempItems.push_back(tempItem);
        }
        int itemCount = static_cast<int>(tempItems.size());
        unordered_map<string, int> itemId;
        for (int i = 0; i < itemCount; i++) itemId[tempItems[i].name] = i + 1;
        items.assign(itemCount + 1, Item());
        for (int i = 0; i < itemCount; i++) {
            int id = i + 1;
            items[id].cost = tempItems[i].cost;
            items[id].happy = tempItems[i].happy;
        }
        for (int i = 0; i < itemCount; i++) {
            int id = i + 1;
            int parentId = tempItems[i].parent == "&" ? 0 : itemId[tempItems[i].parent];
            items[parentId].children.push_back(id);
        }
        cashLimit = cash;
        DpState answerState = dfsTree(0);
        long long bestHappy = 0;
        int bestCost = 0;
        for (int cost = 0; cost <= cashLimit; cost++) {
            if (answerState.values[cost] > bestHappy) {
                bestHappy = answerState.values[cost];
                bestCost = cost;
            }
        }
        if (caseCount > 0) cout << '\n';
        cout << fanName << '\n';
        cout << "Max happiness:" << bestHappy << '\n';
        cout << "Cost:" << bestCost << '\n';
        caseCount++;
    }
    return 0;
}
