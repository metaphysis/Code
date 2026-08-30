#include <bits/stdc++.h>
using namespace std;

struct DpResult {
    int modCount;
    vector<string> seq;
};

class Solver {
private:
    const int inf = 1000000000;
    vector<string> names;
    vector<string> tokens;
    vector<int> notePos;
    vector<int> notePitch;
    vector<vector<vector<DpResult>>> memo;
    vector<vector<vector<bool>>> visited;
    int noteCount, budget;

    int modValue(int value) {
        value %= 12;
        if (value < 0) value += 12;
        return value;
    }

    bool isBar(const string &token) {
        return token == "|" || token == "||";
    }

    int parseLabel(const string &token) {
        int sign = 0, number = 0;
        if (token[0] == '#') {
            sign = 1;
            number = token[1] - '0';
        } else if (token[0] == 'b') {
            sign = -1;
            number = token[1] - '0';
        } else number = token[0] - '0';
        int base[8] = {0, 0, 2, 4, 5, 7, 9, 11};
        return modValue(base[number] + sign);
    }

    int accidental(int label) {
        return label == 1 || label == 3 || label == 6 || label == 8 || label == 10 ? 1 : 0;
    }

    vector<string> addFront(const string &value, const vector<string> &suffix) {
        vector<string> result;
        result.reserve(suffix.size() + 1);
        result.push_back(value);
        result.insert(result.end(), suffix.begin(), suffix.end());
        return result;
    }

    DpResult solveDp(int pos, int last, int rest) {
        if (pos == static_cast<int>(tokens.size())) return {0, vector<string>()};
        if (visited[pos][last][rest]) return memo[pos][last][rest];
        visited[pos][last][rest] = true;
        if (isBar(tokens[pos])) {
            DpResult next = solveDp(pos + 1, last, rest);
            if (next.modCount == inf) return memo[pos][last][rest] = next;
            memo[pos][last][rest] = {next.modCount, addFront(tokens[pos], next.seq)};
            return memo[pos][last][rest];
        }
        int currentIndex = notePos[pos], previousIndex = currentIndex - 1;
        int delta = modValue(notePitch[currentIndex] - notePitch[previousIndex]);
        int oldLabel = modValue(last + delta);
        DpResult best = {inf, vector<string>()};
        int use = accidental(oldLabel);
        if (use <= rest) {
            DpResult next = solveDp(pos + 1, oldLabel, rest - use);
            if (next.modCount != inf) best = {next.modCount, addFront(names[oldLabel], next.seq)};
        }
        for (int newLabel = 0; newLabel < 12; ++newLabel) {
            use = accidental(oldLabel) + accidental(newLabel);
            if (use > rest) continue;
            DpResult next = solveDp(pos + 1, newLabel, rest - use);
            if (next.modCount == inf) continue;
            DpResult candidate = {next.modCount + 1, addFront(names[oldLabel] + "=" + names[newLabel], next.seq)};
            if (candidate.modCount < best.modCount || candidate.modCount == best.modCount && candidate.seq < best.seq) best = candidate;
        }
        memo[pos][last][rest] = best;
        return best;
    }

public:
    vector<string> solveCase(int maxAccidental, const vector<string> &input) {
        names = {"1", "#1", "2", "#2", "3", "4", "#4", "5", "#5", "6", "#6", "7"};
        tokens = input;
        notePos.assign(tokens.size(), -1);
        notePitch.clear();
        noteCount = 0;
        int keyOffset = 0;
        for (int i = 0; i < static_cast<int>(tokens.size()); ++i) {
            if (isBar(tokens[i])) continue;
            size_t equalPos = tokens[i].find('=');
            string oldToken = tokens[i], newToken;
            if (equalPos != string::npos) {
                oldToken = tokens[i].substr(0, equalPos);
                newToken = tokens[i].substr(equalPos + 1);
            }
            int oldLabel = parseLabel(oldToken);
            notePos[i] = noteCount++;
            notePitch.push_back(modValue(keyOffset + oldLabel));
            if (equalPos != string::npos) {
                int newLabel = parseLabel(newToken);
                keyOffset = modValue(keyOffset + oldLabel - newLabel);
            }
        }
        budget = min(maxAccidental, 2 * noteCount);
        memo.assign(tokens.size() + 1, vector<vector<DpResult>>(12, vector<DpResult>(budget + 1)));
        visited.assign(tokens.size() + 1, vector<vector<bool>>(12, vector<bool>(budget + 1, false)));
        int firstPos = 0;
        while (firstPos < static_cast<int>(tokens.size()) && isBar(tokens[firstPos])) ++firstPos;
        vector<string> prefix(tokens.begin(), tokens.begin() + firstPos);
        if (firstPos == static_cast<int>(tokens.size())) return prefix;
        DpResult best = {inf, vector<string>()};
        for (int firstLabel = 0; firstLabel < 12; ++firstLabel) {
            int use = accidental(firstLabel);
            if (use > budget) continue;
            DpResult next = solveDp(firstPos + 1, firstLabel, budget - use);
            if (next.modCount == inf) continue;
            DpResult candidate = {next.modCount, addFront(names[firstLabel], next.seq)};
            if (candidate.modCount < best.modCount || candidate.modCount == best.modCount && candidate.seq < best.seq) best = candidate;
        }
        prefix.insert(prefix.end(), best.seq.begin(), best.seq.end());
        return prefix;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int caseId = 1; caseId <= testCount; ++caseId) {
        int maxAccidental;
        cin >> maxAccidental;
        vector<string> input;
        string token;
        while (cin >> token) {
            input.push_back(token);
            if (token == "||") break;
        }
        Solver solver;
        vector<string> answer = solver.solveCase(maxAccidental, input);
        cout << "Case " << caseId << ":";
        for (const string &value : answer) cout << " " << value;
        cout << '\n';
    }
    return 0;
}
