#include <bits/stdc++.h>
using namespace std;

int totalN;
vector<int> primeList, targetExp, curExp, layerList;
vector<vector<int>> factExp;
unordered_set<string> badState;

bool isZero() {
    for (int value : curExp)
        if (value != 0)
            return false;
    return true;
}

string makeKey(int remN, int maxSize) {
    string key = to_string(remN) + "," + to_string(maxSize);
    for (int value : curExp)
        key += "," + to_string(value);
    return key;
}

bool dfs(int remN, int maxSize) {
    if (isZero()) {
        for (int i = 0; i < remN; i++)
            layerList.push_back(1);
        return true;
    }
    if (remN < 2)
        return false;
    string key = makeKey(remN, maxSize);
    if (badState.count(key))
        return false;
    int upperSize = min(remN, maxSize);
    for (int size = upperSize; size >= 2; size--) {
        bool valid = true;
        for (int i = 0; i < static_cast<int>(primeList.size()); i++)
            if (factExp[size][i] > curExp[i]) {
                valid = false;
                break;
            }
        if (!valid)
            continue;
        for (int i = 0; i < static_cast<int>(primeList.size()); i++)
            curExp[i] -= factExp[size][i];
        layerList.push_back(size);
        if (dfs(remN - size, size))
            return true;
        layerList.pop_back();
        for (int i = 0; i < static_cast<int>(primeList.size()); i++)
            curExp[i] += factExp[size][i];
    }
    badState.insert(key);
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int caseId = 1; caseId <= testCount; caseId++) {
        int primeCount;
        cin >> totalN >> primeCount;
        primeList.clear();
        for (int value = 2; value <= totalN; value++) {
            bool isPrime = true;
            for (int divisor = 2; divisor * divisor <= value; divisor++)
                if (value % divisor == 0) {
                    isPrime = false;
                    break;
                }
            if (isPrime)
                primeList.push_back(value);
        }
        targetExp.assign(primeList.size(), 0);
        for (int i = 0; i < primeCount; i++) {
            int prime, exponent;
            cin >> prime >> exponent;
            for (int j = 0; j < static_cast<int>(primeList.size()); j++)
                if (primeList[j] == prime) {
                    targetExp[j] = exponent;
                    break;
                }
        }
        factExp.assign(totalN + 1, vector<int>(primeList.size(), 0));
        for (int size = 2; size <= totalN; size++) {
            int value = size;
            for (int i = 0; i < static_cast<int>(primeList.size()); i++) {
                while (value % primeList[i] == 0) {
                    factExp[size][i]++;
                    value /= primeList[i];
                }
            }
            for (int i = 0; i < static_cast<int>(primeList.size()); i++)
                factExp[size][i] += factExp[size - 1][i];
        }
        curExp = targetExp;
        layerList.clear();
        badState.clear();
        dfs(totalN, totalN);
        vector<vector<int>> layers;
        int currentPart = 1;
        for (int size : layerList) {
            vector<int> layer;
            for (int i = 0; i < size; i++)
                layer.push_back(currentPart++);
            layers.push_back(layer);
        }
        vector<vector<int>> dependents(totalN + 1);
        for (int i = 1; i < static_cast<int>(layers.size()); i++)
            for (int from : layers[i - 1])
                for (int to : layers[i])
                    dependents[from].push_back(to);
        cout << "Case#" << caseId << ":\n";
        for (int i = 1; i <= totalN; i++) {
            cout << dependents[i].size();
            for (int part : dependents[i])
                cout << " " << part;
            cout << "\n";
        }
    }
    return 0;
}
