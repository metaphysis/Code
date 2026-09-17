#include <bits/stdc++.h>
using namespace std;

vector<string> getRotations(const string &state) {
    int len = static_cast<int>(state.size());
    string doubled = state + state;
    vector<string> rotations;
    for (int start = 0; start < len; ++start) rotations.push_back(doubled.substr(start, len));
    sort(rotations.begin(), rotations.end());
    rotations.erase(unique(rotations.begin(), rotations.end()), rotations.end());
    return rotations;
}

vector<vector<int>> getOverlaps(const string &state, const vector<string> &curRotations, const vector<string> &nextRotations) {
    int curLen = static_cast<int>(state.size()), curCount = static_cast<int>(curRotations.size()), nextCount = static_cast<int>(nextRotations.size());
    string text = state + state;
    vector<int> rowAt(curLen);
    vector<vector<int>> overlaps(curCount, vector<int>(nextCount));
    for (int start = 0; start < curLen; ++start) {
        string rotation = text.substr(start, curLen);
        rowAt[start] = static_cast<int>(lower_bound(curRotations.begin(), curRotations.end(), rotation) - curRotations.begin());
    }
    for (int nextId = 0; nextId < nextCount; ++nextId) {
        const string &pattern = nextRotations[nextId];
        int patternLen = static_cast<int>(pattern.size()), matched = 0;
        vector<int> prefix(patternLen), bounded(patternLen + 1);
        for (int index = 1; index < patternLen; ++index) {
            int length = prefix[index - 1];
            while (length > 0 && pattern[index] != pattern[length]) length = prefix[length - 1];
            if (pattern[index] == pattern[length]) ++length;
            prefix[index] = length;
        }
        for (int length = 1; length <= patternLen; ++length) {
            if (length <= curLen) bounded[length] = length;
            else bounded[length] = bounded[prefix[length - 1]];
        }
        for (int index = 0; index < static_cast<int>(text.size()); ++index) {
            while (matched > 0 && (matched == patternLen || text[index] != pattern[matched])) matched = prefix[matched - 1];
            if (matched < patternLen && text[index] == pattern[matched]) ++matched;
            if (index >= curLen - 1 && index < curLen * 2 - 1) {
                int start = index - curLen + 1;
                overlaps[rowAt[start]][nextId] = bounded[matched];
            }
        }
    }
    return overlaps;
}

vector<string> splitLocks(const string &line) {
    vector<string> locks;
    string current;
    for (char ch : line) {
        if (ch == ';') {
            locks.push_back(current);
            current.clear();
        } else {
            current += ch;
        }
    }
    locks.push_back(current);
    return locks;
}

bool isTailLess(const string &first, int firstStart, const string &second, int secondStart) {
    return first.compare(firstStart, string::npos, second, secondStart, string::npos) < 0;
}

string solve(const vector<string> &locks) {
    int lockCount = static_cast<int>(locks.size());
    vector<vector<string>> rotations(lockCount);
    for (int index = 0; index < lockCount; ++index) rotations[index] = getRotations(locks[index]);
    vector<string> nextAnswers = rotations[lockCount - 1];
    for (int index = lockCount - 2; index >= 0; --index) {
        vector<vector<int>> overlaps = getOverlaps(locks[index], rotations[index], rotations[index + 1]);
        int curCount = static_cast<int>(rotations[index].size()), nextCount = static_cast<int>(rotations[index + 1].size());
        vector<string> curAnswers(curCount);
        for (int curId = 0; curId < curCount; ++curId) {
            int bestId = -1, bestOverlap = 0;
            size_t bestLen = numeric_limits<size_t>::max();
            for (int nextId = 0; nextId < nextCount; ++nextId) {
                int overlap = overlaps[curId][nextId];
                size_t candidateLen = rotations[index][curId].size() + nextAnswers[nextId].size() - overlap;
                if (candidateLen < bestLen) {
                    bestId = nextId;
                    bestOverlap = overlap;
                    bestLen = candidateLen;
                } else if (candidateLen == bestLen && isTailLess(nextAnswers[nextId], overlap, nextAnswers[bestId], bestOverlap)) {
                    bestId = nextId;
                    bestOverlap = overlap;
                }
            }
            curAnswers[curId] = rotations[index][curId] + nextAnswers[bestId].substr(bestOverlap);
        }
        nextAnswers.swap(curAnswers);
    }
    string answer = nextAnswers[0];
    for (const string &candidate : nextAnswers) {
        if (candidate.size() < answer.size() || (candidate.size() == answer.size() && candidate < answer)) answer = candidate;
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    string line;
    cin >> testCount;
    getline(cin, line);
    while (testCount--) {
        getline(cin, line);
        if (!line.empty() && line.back() == '\r') line.pop_back();
        vector<string> locks = splitLocks(line);
        cout << solve(locks) << '\n';
    }
    return 0;
}
