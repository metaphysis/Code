#include <bits/stdc++.h>
using namespace std;

struct WordInfo {
    string word;
    int weight;
};

bool isBetter(const WordInfo& first, const WordInfo& second) {
    if (first.weight != second.weight) return first.weight > second.weight;
    return first.word < second.word;
}

void updateBest(unordered_map<string, WordInfo>& table, const string& key, const string& word, int weight) {
    auto it = table.find(key);
    if (it == table.end()) table.emplace(key, WordInfo{word, weight});
    else if (isBetter(WordInfo{word, weight}, it->second)) it->second = WordInfo{word, weight};
}

void chooseBest(bool& found, WordInfo& best, const WordInfo& candidate) {
    if (!found || isBetter(candidate, best)) {
        best = candidate;
        found = true;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int caseId = 1; caseId <= testCount; ++caseId) {
        int dCount, qCount;
        cin >> dCount >> qCount;
        unordered_map<string, WordInfo> exactMap, nearMap;
        exactMap.reserve(dCount * 2);
        nearMap.reserve(dCount * 3);
        for (int i = 0; i < dCount; ++i) {
            string word;
            int weight;
            cin >> word >> weight;
            updateBest(exactMap, word, word, weight);
            for (int j = 0; j < static_cast<int>(word.size()); ++j) {
                string key = word.substr(0, j) + word.substr(j + 1);
                updateBest(nearMap, key, word, weight);
            }
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Case " << caseId << ":\n";
        for (int i = 0; i < qCount; ++i) {
            string line, token;
            vector<string> parts;
            getline(cin, line);
            stringstream input(line);
            while (input >> token) parts.push_back(token);
            int x = stoi(parts.back());
            parts.pop_back();
            bool hasOutput = false;
            for (const string& query : parts) {
                auto exactIt = exactMap.find(query);
                WordInfo best;
                bool found = false;
                if (exactIt != exactMap.end()) {
                    best = exactIt->second;
                    found = true;
                } else if (x == 1) {
                    for (int j = 0; j < static_cast<int>(query.size()); ++j) {
                        string key = query.substr(0, j) + query.substr(j + 1);
                        auto shortIt = exactMap.find(key);
                        if (shortIt != exactMap.end()) chooseBest(found, best, shortIt->second);
                    }
                    auto longIt = nearMap.find(query);
                    if (longIt != nearMap.end()) chooseBest(found, best, longIt->second);
                }
                if (found) {
                    if (hasOutput) cout << ' ';
                    cout << best.word;
                    hasOutput = true;
                }
            }
            cout << '\n';
        }
    }
    return 0;
}
