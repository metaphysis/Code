#include <bits/stdc++.h>
using namespace std;

struct Unit {
    bool isVar;
    int nodeId;
    char value;
};

struct Variable {
    string name;
    int length;
    int base;
};

class Solver {
private:
    vector<int> parent, rankValue;
    vector<char> known;
    vector<Variable> variables;
    map<string, int> varMap;

    int findRoot(int node) {
        if (parent[node] == node) return node;
        return parent[node] = findRoot(parent[node]);
    }

    bool setValue(int node, char value) {
        int root = findRoot(node);
        if (known[root] != 0 && known[root] != value) return false;
        known[root] = value;
        return true;
    }

    bool mergeNode(int first, int second) {
        int rootFirst = findRoot(first), rootSecond = findRoot(second);
        if (rootFirst == rootSecond) return true;
        if (rankValue[rootFirst] < rankValue[rootSecond]) swap(rootFirst, rootSecond);
        if (known[rootFirst] != 0 && known[rootSecond] != 0 && known[rootFirst] != known[rootSecond]) return false;
        parent[rootSecond] = rootFirst;
        if (known[rootFirst] == 0) known[rootFirst] = known[rootSecond];
        if (rankValue[rootFirst] == rankValue[rootSecond]) ++rankValue[rootFirst];
        return true;
    }

    int addVariable(const string &name, int length) {
        auto it = varMap.find(name);
        if (it != varMap.end()) return it->second;
        int id = variables.size(), base = parent.size(), i;
        variables.push_back({name, length, base});
        varMap[name] = id;
        for (i = 0; i < length; ++i) {
            parent.push_back(base + i);
            rankValue.push_back(0);
            known.push_back(0);
        }
        return id;
    }

    vector<Unit> parseText(const string &text) {
        vector<Unit> result;
        int i = 0, n = text.size();
        while (i < n) {
            if (text[i] != '<') {
                result.push_back({false, -1, text[i]});
                ++i;
                continue;
            }
            int colon = text.find(':', i), right = text.find('>', colon);
            string name = text.substr(i + 1, colon - i - 1);
            int length = stoi(text.substr(colon + 1, right - colon - 1));
            int id = addVariable(name, length), j;
            for (j = 0; j < length; ++j)
                result.push_back({true, variables[id].base + j, 0});
            i = right + 1;
        }
        return result;
    }

public:
    bool solve(const string &firstText, const string &secondText, map<string, string> &answer) {
        vector<Unit> firstUnits = parseText(firstText), secondUnits = parseText(secondText);
        int i = 0, j = 0;
        if (firstUnits.size() != secondUnits.size()) return false;
        while (i < (int)firstUnits.size() && j < (int)secondUnits.size()) {
            Unit first = firstUnits[i], second = secondUnits[j];
            if (!first.isVar && !second.isVar) {
                if (first.value != second.value) return false;
            } else if (first.isVar && second.isVar) {
                if (!mergeNode(first.nodeId, second.nodeId)) return false;
            } else if (first.isVar) {
                if (!setValue(first.nodeId, second.value)) return false;
            } else {
                if (!setValue(second.nodeId, first.value)) return false;
            }
            ++i;
            ++j;
        }
        for (auto item : varMap) {
            int id = item.second, k;
            string value;
            for (k = 0; k < variables[id].length; ++k) {
                int root = findRoot(variables[id].base + k);
                value += known[root] == 0 ? '*' : known[root];
            }
            answer[item.first] = value;
        }
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int lineCount, i;
    bool firstCase = true;
    while (cin >> lineCount) {
        string firstText, secondText, line;
        getline(cin, line);
        for (i = 0; i < lineCount; ++i) {
            getline(cin, line);
            firstText += line;
        }
        if (!(cin >> lineCount)) break;
        getline(cin, line);
        for (i = 0; i < lineCount; ++i) {
            getline(cin, line);
            secondText += line;
        }
        Solver solver;
        map<string, string> answer;
        bool matched = solver.solve(firstText, secondText, answer);
        if (!firstCase) cout << '\n';
        firstCase = false;
        if (!matched) {
            cout << "no\n";
            continue;
        }
        cout << "yes\n";
        for (auto item : answer)
            cout << item.first << ' ' << item.second << '\n';
    }
    return 0;
}
