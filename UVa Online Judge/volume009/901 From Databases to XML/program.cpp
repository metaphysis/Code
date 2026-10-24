// From Databases to XML
// UVa ID: 901
// Verdict: Accepted
// Submission Date: 2026-10-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Table {
    string name;
    vector<string> columns;
    vector<int> colPos;
    vector<int> keyIndices;
    vector<string> rawKeyNames;
    bool referenceable = false;
    vector<int> refIndices;
    vector<pair<int, int>> refTargets;
    int parentTable = -1;
    vector<int> attributeOrder;
    int inputArity = 0;
};

struct Record {
    int table = -1;
    vector<string> values;
    vector<int> children;
    bool embedded = false;
};

vector<string> splitValues(string& inside) {
    vector<string> values;
    size_t start = 0;
    while (true) {
        size_t comma = inside.find(',', start);
        if (comma == string::npos) {
            values.push_back(inside.substr(start));
            break;
        }
        values.push_back(inside.substr(start, comma - start));
        start = comma + 1;
    }
    return values;
}

bool parseTuple(string& line, string& name, vector<string>& values) {
    size_t leftParen = line.find('(');
    if (leftParen == string::npos) return false;
    name = line.substr(0, leftParen);
    string inside = line.substr(leftParen + 1);
    if (!inside.empty()) inside.pop_back();
    values = splitValues(inside);
    return true;
}

string solve(vector<string>& inputLines) {
    vector<Table> tables;
    map<string, int> tableIndex;
    vector<pair<string, vector<string>>> dataRows;
    bool readingData = false;
    for (string& line : inputLines) {
        if (line.empty()) continue;
        if (!readingData && line == "data") {
            readingData = true;
            continue;
        }
        string name;
        vector<string> values;
        if (!parseTuple(line, name, values)) continue;
        if (!readingData) {
            Table table;
            table.name = name;
            table.inputArity = values.size();
            for (string& value : values)
                if (!value.empty() && value[0] == '#')
                    table.rawKeyNames.push_back(value.substr(1));
            set<string> seen;
            for (int i = 0; i < values.size(); ++i)
                if (seen.insert(values[i]).second) {
                    table.columns.push_back(values[i]);
                    table.colPos.push_back(i);
                }
            for (int i = 0; i < table.columns.size(); ++i)
                if (!table.columns[i].empty() && table.columns[i][0] == '#')
                    table.keyIndices.push_back(i);
            table.referenceable = !table.keyIndices.empty();
            if (!tableIndex.count(name)) {
                int id = tables.size();
                tableIndex[name] = id;
                tables.push_back(table);
            }
        } else dataRows.push_back({name, values});
    }
    map<string, pair<int, int>> keyInfo;
    for (int i = 0; i < tables.size(); ++i) {
        if (!tables[i].referenceable) continue;
        for (int keyIndex : tables[i].keyIndices) {
            string keyName = tables[i].columns[keyIndex].substr(1);
            if (!keyInfo.count(keyName)) keyInfo[keyName] = {i, keyIndex};
        }
    }
    for (Table& table : tables) {
        table.attributeOrder.resize(table.columns.size());
        iota(table.attributeOrder.begin(), table.attributeOrder.end(), 0);
        sort(table.attributeOrder.begin(), table.attributeOrder.end(), [&](int a, int b) {
            if (table.columns[a] != table.columns[b]) return table.columns[a] < table.columns[b];
            return a < b;
        });
        for (int column : table.attributeOrder) {
            if (!table.columns[column].empty() && table.columns[column][0] == '#') continue;
            auto it = keyInfo.find(table.columns[column]);
            if (it != keyInfo.end()) {
                table.refIndices.push_back(column);
                table.refTargets.push_back(it->second);
            }
        }
        if (table.refIndices.empty()) {
            table.parentTable = -1;
            continue;
        }
        int candidate = table.refTargets[0].first;
        bool allSame = true;
        for (auto& target : table.refTargets) {
            if (target.first != candidate) {
                allSame = false;
                break;
            }
        }
        if (!allSame) {
            table.parentTable = -1;
            continue;
        }
        vector<string> refNames;
        for (int column : table.refIndices) refNames.push_back(table.columns[column]);
        sort(refNames.begin(), refNames.end());
        vector<string> keyNames = tables[candidate].rawKeyNames;
        sort(keyNames.begin(), keyNames.end());
        table.parentTable = (refNames == keyNames) ? candidate : -1;
    }
    vector<Record> records;
    records.reserve(dataRows.size());
    for (auto& row : dataRows) {
        auto tableIt = tableIndex.find(row.first);
        if (tableIt == tableIndex.end()) continue;
        int tableId = tableIt->second;
        Table& table = tables[tableId];
        int maxPos = -1;
        for (int pos : table.colPos) maxPos = max(maxPos, pos);
        if (row.second.size() <= maxPos) continue;
        Record record;
        record.table = tableId;
        record.values = row.second;
        records.push_back(record);
    }
    vector<vector<map<string, vector<int>>>> keyLookup(tables.size());
    for (int i = 0; i < tables.size(); ++i) keyLookup[i].resize(tables[i].columns.size());
    for (int i = 0; i < records.size(); ++i) {
        Table& table = tables[records[i].table];
        for (int keyIndex : table.keyIndices)
            keyLookup[records[i].table][keyIndex][records[i].values[table.colPos[keyIndex]]].push_back(i);
    }
    vector<int> roots;
    for (int i = 0; i < records.size(); ++i) {
        Record& record = records[i];
        Table& table = tables[record.table];
        int parentTable = table.parentTable;
        if (parentTable == -1) {
            roots.push_back(i);
            continue;
        }
        vector<int> candidates;
        bool firstRef = true;
        bool matched = true;
        for (int k = 0; k < table.refIndices.size(); ++k) {
            int column = table.refIndices[k];
            int keyCol = table.refTargets[k].second;
            string& value = record.values[table.colPos[column]];
            auto it = keyLookup[parentTable][keyCol].find(value);
            if (it == keyLookup[parentTable][keyCol].end()) {
                matched = false;
                break;
            }
            if (firstRef) {
                candidates = it->second;
                firstRef = false;
            } else {
                set<int> keep(candidates.begin(), candidates.end());
                vector<int> next;
                for (int parent : it->second)
                    if (keep.count(parent))
                        next.push_back(parent);
                candidates = next;
            }
        }
        if (!matched || candidates.empty()) {
            roots.push_back(i);
            continue;
        }
        record.embedded = true;
        for (int parent : candidates) records[parent].children.push_back(i);
    }
    auto recordLess = [&](int a, int b) {
        Table& tableA = tables[records[a].table];
        Table& tableB = tables[records[b].table];
        if (tableA.name != tableB.name) return tableA.name < tableB.name;
        for (int column : tableA.attributeOrder) {
            string& valueA = records[a].values[tableA.colPos[column]];
            string& valueB = records[b].values[tableB.colPos[column]];
            if (valueA != valueB) return valueA < valueB;
        }
        return a < b;
    };
    sort(roots.begin(), roots.end(), recordLess);
    for (Record& record : records) sort(record.children.begin(), record.children.end(), recordLess);
    auto isReferenceColumn = [&](Table& table, int column) {
        return find(table.refIndices.begin(), table.refIndices.end(), column) != table.refIndices.end();
    };
    ostringstream output;
    output << "<DB>\n";
    vector<bool> onPath(records.size(), false);
    function<void(int)> emitRecord = [&](int index) {
        if (onPath[index]) return;
        onPath[index] = true;
        Record& record = records[index];
        Table& table = tables[record.table];
        output << '<' << table.name;
        for (int column : table.attributeOrder) {
            if (record.embedded && isReferenceColumn(table, column)) continue;
            output << ' ' << table.columns[column] << "=\"" << record.values[table.colPos[column]] << '"';
        }
        output << ">\n";
        for (int child : record.children) emitRecord(child);
        output << "</" << table.name << ">\n";
        onPath[index] = false;
    };
    for (int root : roots) emitRecord(root);
    output << "</DB>";
    return output.str();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<vector<string>> cases;
    vector<string> currentCase;
    string line;
    while (getline(cin, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.empty()) {
            if (!currentCase.empty()) {
                cases.push_back(currentCase);
                currentCase.clear();
            }
        } else currentCase.push_back(line);
    }
    if (!currentCase.empty()) cases.push_back(currentCase);
    for (int i = 0; i < cases.size(); ++i) {
        if (i > 0) cout << '\n';
        cout << solve(cases[i]) << '\n';
    }
    return 0;
}
