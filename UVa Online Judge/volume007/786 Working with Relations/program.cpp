// Working with Relations
// UVa ID: 786
// Verdict: Accepted
// Submission Date: 2026-07-19
// UVa Run Time: 0.280s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const long long infinityValue = (1LL << 60);
const int minWage = 1;
const int maxWage = 99999;

struct Operand {
    bool isNumber;
    long long value;
    string name;
};

struct Relation {
    Operand left;
    string op;
    Operand right;
};

bool isNumber(const string& text) {
    if (text.empty())
        return false;
    int start = text[0] == '-' || text[0] == '+' ? 1 : 0;
    if (start == (int)text.size())
        return false;
    for (int i = start; i < (int)text.size(); ++i)
        if (!isdigit(text[i]))
            return false;
    return true;
}

Operand parseOperand(const string& text) {
    if (isNumber(text))
        return {true, stoll(text), ""};
    return {false, 0, text};
}

void addConstraint(const Operand& left, const Operand& right, long long limit, const unordered_map<string, int>& employeeId, vector<vector<long long>>& distance) {
    int source = 0;
    if (!left.isNumber && !right.isNumber) {
        int leftId = employeeId.at(left.name);
        int rightId = employeeId.at(right.name);
        distance[rightId][leftId] = min(distance[rightId][leftId], limit);
    } else if (!left.isNumber && right.isNumber) {
        int leftId = employeeId.at(left.name);
        distance[source][leftId] = min(distance[source][leftId], right.value + limit);
    } else if (left.isNumber && !right.isNumber) {
        int rightId = employeeId.at(right.name);
        distance[rightId][source] = min(distance[rightId][source], limit - left.value);
    } else if (left.value - right.value > limit) {
        distance[source][source] = -1;
    }
}

void addRelation(const Relation& relation, const unordered_map<string, int>& employeeId, vector<vector<long long>>& distance) {
    if (relation.op == "<")
        addConstraint(relation.left, relation.right, -1, employeeId, distance);
    else if (relation.op == "<=")
        addConstraint(relation.left, relation.right, 0, employeeId, distance);
    else if (relation.op == ">")
        addConstraint(relation.right, relation.left, -1, employeeId, distance);
    else if (relation.op == ">=")
        addConstraint(relation.right, relation.left, 0, employeeId, distance);
    else {
        addConstraint(relation.left, relation.right, 0, employeeId, distance);
        addConstraint(relation.right, relation.left, 0, employeeId, distance);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    bool firstCase = true;
    while (true) {
        vector<Relation> relations;
        set<string> employeeNames;
        bool hasInput = false;
        while (getline(cin, line)) {
            if (line.empty())
                continue;
            hasInput = true;
            if (line == "-")
                break;
            string leftText;
            string op;
            string rightText;
            stringstream input(line);
            input >> leftText >> op >> rightText;
            Operand left = parseOperand(leftText);
            Operand right = parseOperand(rightText);
            relations.push_back({left, op, right});
            if (!left.isNumber)
                employeeNames.insert(left.name);
            if (!right.isNumber)
                employeeNames.insert(right.name);
        }
        if (!hasInput && relations.empty())
            break;
        vector<string> names(employeeNames.begin(), employeeNames.end());
        unordered_map<string, int> employeeId;
        for (int i = 0; i < (int)names.size(); ++i)
            employeeId[names[i]] = i + 1;
        int nodeCount = names.size() + 1;
        vector<vector<long long>> distance(nodeCount, vector<long long>(nodeCount, infinityValue));
        for (int i = 0; i < nodeCount; ++i)
            distance[i][i] = 0;
        for (int i = 1; i < nodeCount; ++i) {
            // 加入所有员工的工资范围
            distance[0][i] = min(distance[0][i], (long long)maxWage);
            distance[i][0] = min(distance[i][0], (long long)-minWage);
        }
        for (const Relation& relation : relations)
            addRelation(relation, employeeId, distance);
        for (int middle = 0; middle < nodeCount; ++middle)
            for (int from = 0; from < nodeCount; ++from) {
                if (distance[from][middle] == infinityValue)
                    continue;
                for (int to = 0; to < nodeCount; ++to) {
                    if (distance[middle][to] == infinityValue)
                        continue;
                    distance[from][to] = min(distance[from][to], distance[from][middle] + distance[middle][to]);
                }
            }
        if (!firstCase)
            cout << '\n';
        firstCase = false;
        bool possible = true;
        for (int i = 0; i < nodeCount; ++i)
            if (distance[i][i] < 0)
                possible = false;
        if (!possible) {
            cout << "No solution\n";
            if (cin.eof())
                break;
            continue;
        }
        cout << "OK\n";
        for (const string& name : names) {
            int id = employeeId[name];
            long long lowest = -distance[id][0];
            long long highest = distance[0][id];
            cout << setw(8) << left << name << ' ' << setw(5) << right << lowest << ' ' << setw(5) << right << highest << '\n';
        }
        if (cin.eof())
            break;
    }
    return 0;
}
