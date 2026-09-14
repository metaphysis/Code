#include <bits/stdc++.h>
using namespace std;

vector<string> splitSide(const string &side) {
    vector<string> result;
    string current;
    for (char ch : side) {
        if (ch == '+') {
            result.push_back(current);
            current.clear();
        } else {
            current += ch;
        }
    }
    result.push_back(current);
    return result;
}

map<string, int> parseFormula(const string &formula) {
    map<string, int> result;
    int index = 0;
    while (index < static_cast<int>(formula.size())) {
        string name;
        name += formula[index++];
        if (index < static_cast<int>(formula.size()) && formula[index] >= 'a' && formula[index] <= 'z')
            name += formula[index++];
        int count = 1;
        if (index < static_cast<int>(formula.size()) && formula[index] >= '1' && formula[index] <= '9')
            count = formula[index++] - '0';
        result[name] += count;
    }
    return result;
}

void buildRight(int index, int count, int start, const vector<vector<int>> &coef, vector<int> &cur, vector<int> &sum, map<vector<int>, vector<int>> &best) {
    if (index == count) {
        if (best.find(sum) == best.end())
            best[sum] = cur;
        return;
    }
    int molecule = start + index;
    for (int value = 1; value <= 9; ++value) {
        cur[index] = value;
        for (int atom = 0; atom < static_cast<int>(sum.size()); ++atom)
            sum[atom] += value * coef[molecule][atom];
        buildRight(index + 1, count, start, coef, cur, sum, best);
        for (int atom = 0; atom < static_cast<int>(sum.size()); ++atom)
            sum[atom] -= value * coef[molecule][atom];
    }
}

bool findLeft(int index, int count, int start, const vector<vector<int>> &coef, vector<int> &cur, vector<int> &sum, const map<vector<int>, vector<int>> &best, vector<int> &answer) {
    if (index == count) {
        vector<int> target(sum.size());
        for (int atom = 0; atom < static_cast<int>(sum.size()); ++atom)
            target[atom] = -sum[atom];
        auto iter = best.find(target);
        if (iter == best.end())
            return false;
        answer = cur;
        answer.insert(answer.end(), iter->second.begin(), iter->second.end());
        return true;
    }
    int molecule = start + index;
    for (int value = 1; value <= 9; ++value) {
        cur[index] = value;
        for (int atom = 0; atom < static_cast<int>(sum.size()); ++atom)
            sum[atom] += value * coef[molecule][atom];
        if (findLeft(index + 1, count, start, coef, cur, sum, best, answer))
            return true;
        for (int atom = 0; atom < static_cast<int>(sum.size()); ++atom)
            sum[atom] -= value * coef[molecule][atom];
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        string equation;
        cin >> equation;
        int equalPos = equation.find('=');
        string leftPart = equation.substr(0, equalPos), rightPart = equation.substr(equalPos + 1);
        vector<string> leftMolecules = splitSide(leftPart), rightMolecules = splitSide(rightPart), molecules = leftMolecules;
        molecules.insert(molecules.end(), rightMolecules.begin(), rightMolecules.end());
        vector<map<string, int>> formulas;
        map<string, int> atomId;
        for (const string &molecule : molecules) {
            formulas.push_back(parseFormula(molecule));
            for (const auto &item : formulas.back())
                if (atomId.find(item.first) == atomId.end())
                    atomId[item.first] = static_cast<int>(atomId.size());
        }
        int moleculeCount = molecules.size(), atomCount = atomId.size();
        int leftCount = moleculeCount / 2;
        vector<vector<int>> coef(moleculeCount, vector<int>(atomCount, 0));
        for (int molecule = 0; molecule < moleculeCount; ++molecule) {
            int sign = molecule < static_cast<int>(leftMolecules.size()) ? 1 : -1;
            for (const auto &item : formulas[molecule])
                coef[molecule][atomId[item.first]] = sign * item.second;
        }
        int rightCount = moleculeCount - leftCount;
        vector<int> rightCur(rightCount), rightSum(atomCount, 0);
        map<vector<int>, vector<int>> best;
        buildRight(0, rightCount, leftCount, coef, rightCur, rightSum, best);
        vector<int> leftCur(leftCount), leftSum(atomCount, 0), answer;
        bool possible = findLeft(0, leftCount, 0, coef, leftCur, leftSum, best, answer);
        if (!possible) {
            cout << "IMPOSSIBLE\n";
            continue;
        }
        for (int index = 0; index < static_cast<int>(answer.size()); ++index) {
            if (index > 0)
                cout << ' ';
            cout << answer[index];
        }
        cout << '\n';
    }
    return 0;
}
