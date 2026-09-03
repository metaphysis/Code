#include <bits/stdc++.h>
using namespace std;

struct ProductInfo {
    string name;
    int count;
    vector<string> ingredientNames;
    vector<int> fixedValues;
    vector<int> minValues;
    vector<int> maxValues;
    unordered_map<string, int> indexMap;
};

void buildBounds(ProductInfo &product) {
    int n = product.count;
    vector<vector<bitset<101>>> pre(n + 1, vector<bitset<101>>(101));
    vector<vector<bitset<101>>> suf(n + 1, vector<bitset<101>>(101));
    for (int x = 0; x <= 100; x++) {
        pre[0][x].set(0);
        suf[n][x].set(0);
    }
    for (int i = 0; i < n; i++) {
        vector<bitset<101>> cur(101);
        for (int x = 0; x <= 100; x++)
            if ((product.fixedValues[i] == -1 && x >= 1) || product.fixedValues[i] == x)
                cur[x] = pre[i][x] << x;
        for (int x = 100; x >= 0; x--)
            pre[i + 1][x] = cur[x] | (x == 100 ? bitset<101>() : pre[i + 1][x + 1]);
    }
    for (int i = n - 1; i >= 0; i--) {
        vector<bitset<101>> cur(101);
        for (int x = 0; x <= 100; x++)
            if ((product.fixedValues[i] == -1 && x >= 1) || product.fixedValues[i] == x)
                cur[x] = suf[i + 1][x] << x;
        for (int x = 0; x <= 100; x++)
            suf[i][x] = cur[x] | (x == 0 ? bitset<101>() : suf[i][x - 1]);
    }
    product.minValues.assign(n, 101);
    product.maxValues.assign(n, -1);
    for (int i = 0; i < n; i++) {
        for (int x = 0; x <= 100; x++) {
            if (product.fixedValues[i] != -1 && product.fixedValues[i] != x)
                continue;
            if (product.fixedValues[i] == -1 && x == 0)
                continue;
            bool possible = false;
            for (int prefixSum = 0; prefixSum + x <= 100; prefixSum++) {
                int suffixSum = 100 - prefixSum - x;
                if (pre[i][x][prefixSum] && suf[i + 1][x][suffixSum]) {
                    possible = true;
                    break;
                }
            }
            if (possible) {
                product.minValues[i] = min(product.minValues[i], x);
                product.maxValues[i] = max(product.maxValues[i], x);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int productCount;
    while (cin >> productCount && productCount != 0) {
        vector<ProductInfo> products(productCount);
        for (int i = 0; i < productCount; i++) {
            cin >> products[i].name;
            cin >> products[i].count;
            string line;
            getline(cin, line);
            products[i].ingredientNames.resize(products[i].count);
            products[i].fixedValues.assign(products[i].count, -1);
            for (int j = 0; j < products[i].count; j++) {
                getline(cin, line);
                stringstream stream(line);
                string ingredientName, percentageText;
                stream >> ingredientName;
                products[i].ingredientNames[j] = ingredientName;
                products[i].indexMap[ingredientName] = j;
                if (stream >> percentageText)
                    products[i].fixedValues[j] = stoi(percentageText.substr(0, percentageText.size() - 1));
            }
            buildBounds(products[i]);
        }
        int queryCount;
        cin >> queryCount;
        while (queryCount--) {
            string queryType, ingredientName;
            cin >> queryType >> ingredientName;
            vector<int> minValues(productCount, 0), maxValues(productCount, 0);
            for (int i = 0; i < productCount; i++) {
                auto iterator = products[i].indexMap.find(ingredientName);
                if (iterator == products[i].indexMap.end())
                    continue;
                int index = iterator->second;
                minValues[i] = products[i].minValues[index];
                maxValues[i] = products[i].maxValues[index];
            }
            vector<string> answer;
            for (int i = 0; i < productCount; i++) {
                bool possible = true;
                for (int j = 0; j < productCount; j++) {
                    if (queryType == "most" && maxValues[i] < minValues[j]) {
                        possible = false;
                        break;
                    }
                    if (queryType == "least" && minValues[i] > maxValues[j]) {
                        possible = false;
                        break;
                    }
                }
                if (possible)
                    answer.push_back(products[i].name);
            }
            for (int i = 0; i < static_cast<int>(answer.size()); i++) {
                if (i > 0)
                    cout << ' ';
                cout << answer[i];
            }
            cout << '\n';
        }
    }
    return 0;
}
