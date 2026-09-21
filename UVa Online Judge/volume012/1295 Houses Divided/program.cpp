#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int first;
    int second;
    int distance;
};

struct Upper {
    int first;
    int second;
    int distance;
};

struct Solver {
    int rowCount, colCount, cellCount;
    vector<string> names;
    vector<int> houseIds;
    vector<bitset<100>> baseDomains;
    vector<Edge> edges;
    vector<vector<int>> location;
    map<string, int> idMap;

    int getId(const string &name) {
        if (idMap.count(name)) return idMap[name];
        int id = names.size();
        idMap[name] = id;
        names.push_back(name);
        baseDomains.push_back(bitset<100>());
        baseDomains.back().set();
        if (name.size() >= 5 && name.substr(0, 5) == "house") houseIds.push_back(id);
        return id;
    }

    int getDistance(int first, int second) {
        int firstRow = first / colCount, firstCol = first % colCount;
        int secondRow = second / colCount, secondCol = second % colCount;
        return abs(firstRow - secondRow) + abs(firstCol - secondCol);
    }

    bool revise(vector<bitset<100>> &domains, int first, int second, int distance, bool lessEqual) {
        bitset<100> nextDomain;
        bool changed = false;
        for (int firstPos = 0; firstPos < cellCount; firstPos++) {
            if (!domains[first][firstPos]) continue;
            bool supported = false;
            for (int secondPos = 0; secondPos < cellCount; secondPos++) {
                if (!domains[second][secondPos]) continue;
                int currentDistance = getDistance(firstPos, secondPos);
                if ((lessEqual && currentDistance <= distance) || (!lessEqual && currentDistance == distance)) {
                    supported = true;
                    break;
                }
            }
            if (supported) nextDomain.set(firstPos);
            else changed = true;
        }
        domains[first] = nextDomain;
        return changed;
    }

    bool propagate(vector<bitset<100>> &domains, const vector<Upper> &uppers) {
        bool changed = true;
        while (changed) {
            changed = false;
            for (const Edge &edge : edges) {
                if (revise(domains, edge.first, edge.second, edge.distance, false)) changed = true;
                if (revise(domains, edge.second, edge.first, edge.distance, false)) changed = true;
            }
            for (const Upper &upper : uppers) {
                if (revise(domains, upper.first, upper.second, upper.distance, true)) changed = true;
                if (revise(domains, upper.second, upper.first, upper.distance, true)) changed = true;
            }
            for (int i = 0; i < static_cast<int>(domains.size()); i++)
                if (domains[i].count() == 0) return false;
            for (int i = 0; i < static_cast<int>(domains.size()); i++) {
                if (domains[i].count() != 1) continue;
                int position = -1;
                for (int j = 0; j < cellCount; j++)
                    if (domains[i][j]) position = j;
                for (int j = 0; j < static_cast<int>(domains.size()); j++) {
                    if (i == j || domains[j].count() == 1) continue;
                    if (domains[j][position]) {
                        domains[j].reset(position);
                        changed = true;
                    }
                }
            }
            for (int i = 0; i < static_cast<int>(domains.size()); i++)
                if (domains[i].count() == 0) return false;
        }
        for (int i = 0; i < static_cast<int>(domains.size()); i++)
            for (int j = i + 1; j < static_cast<int>(domains.size()); j++)
                if (domains[i].count() == 1 && domains[j].count() == 1 && domains[i] == domains[j]) return false;
        return true;
    }

    bool search(vector<bitset<100>> domains, const vector<Upper> &uppers) {
        if (!propagate(domains, uppers)) return false;
        int selected = -1, minSize = 101;
        for (int i = 0; i < static_cast<int>(domains.size()); i++) {
            int currentSize = domains[i].count();
            if (currentSize > 1 && currentSize < minSize) {
                minSize = currentSize;
                selected = i;
            }
        }
        if (selected == -1) return true;
        for (int position = 0; position < cellCount; position++) {
            if (!domains[selected][position]) continue;
            vector<bitset<100>> nextDomains = domains;
            nextDomains[selected].reset();
            nextDomains[selected].set(position);
            if (search(nextDomains, uppers)) return true;
        }
        return false;
    }

    bool feasible(int limit, int specialFirst, int specialSecond) {
        vector<bitset<100>> domains = baseDomains;
        vector<Upper> uppers;
        if (specialFirst != -1) {
            uppers.push_back({specialFirst, specialSecond, limit});
        } else {
            for (int i = 0; i < static_cast<int>(houseIds.size()); i++)
                for (int j = i + 1; j < static_cast<int>(houseIds.size()); j++)
                    uppers.push_back({houseIds[i], houseIds[j], limit});
        }
        return search(domains, uppers);
    }

    void addLocation(const string &name, char row, int column) {
        int id = getId(name);
        int position = (row - 'A') * colCount + column;
        baseDomains[id].reset();
        baseDomains[id].set(position);
    }

    void addDistance(const string &name, int distance, const string &otherName) {
        int first = getId(name), second = getId(otherName);
        edges.push_back({first, second, distance});
    }

    int getMaximumGuaranteedSeparation() {
        int result = 0;
        int maxDistance = rowCount + colCount - 2;
        for (int i = 0; i < static_cast<int>(houseIds.size()); i++)
            for (int j = i + 1; j < static_cast<int>(houseIds.size()); j++) {
                int low = 0, high = maxDistance;
                while (low < high) {
                    int middle = (low + high) / 2;
                    if (feasible(middle, houseIds[i], houseIds[j])) high = middle;
                    else low = middle + 1;
                }
                result = max(result, low);
            }
        return result;
    }

    int getMinimumMaximumSeparation() {
        int low = 0, high = rowCount + colCount - 2;
        while (low < high) {
            int middle = (low + high) / 2;
            if (feasible(middle, -1, -1)) high = middle;
            else low = middle + 1;
        }
        return low;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int description = 0, m, n;
    while (cin >> m >> n) {
        if (m == 0 && n == 0) break;
        string line;
        getline(cin, line);
        Solver solver;
        solver.rowCount = m;
        solver.colCount = n;
        solver.cellCount = m * n;
        while (getline(cin, line)) {
            if (line == "END") break;
            stringstream input(line);
            string name, type;
            input >> name >> type;
            if (type == "LOCATION") {
                char row;
                int column;
                input >> row >> column;
                solver.addLocation(name, row, column);
            } else {
                int distance;
                string otherName;
                input >> distance >> otherName;
                solver.addDistance(name, distance, otherName);
            }
        }
        int minimumMaximum = solver.getMinimumMaximumSeparation();
        int maximumGuaranteed = solver.getMaximumGuaranteedSeparation();
        cout << "DESCRIPTION " << description + 1 << '\n';
        cout << "Maximum guaranteed separation is " << minimumMaximum << " blocks.\n";
        cout << "Houses separated by at least " << maximumGuaranteed << " blocks:\n";
        vector<pair<int, int>> result;
        for (int i = 0; i < static_cast<int>(solver.houseIds.size()); i++)
            for (int j = i + 1; j < static_cast<int>(solver.houseIds.size()); j++) {
                int low = 0, high = solver.rowCount + solver.colCount - 2;
                while (low < high) {
                    int middle = (low + high) / 2;
                    if (solver.feasible(middle, solver.houseIds[i], solver.houseIds[j])) high = middle;
                    else low = middle + 1;
                }
                if (low == maximumGuaranteed) result.push_back({i, j});
            }
        for (const pair<int, int> &item : result)
            cout << solver.names[solver.houseIds[item.first]] << ' ' << solver.names[solver.houseIds[item.second]] << '\n';
        cout << '\n';
        description++;
    }
    return 0;
}
