#include <bits/stdc++.h>
using namespace std;

string normalizeLine(const string &line) {
    int left = 0;
    int right = static_cast<int>(line.size()) - 1;
    while (left <= right && line[left] == ' ')
        ++left;
    while (right >= left && line[right] == ' ')
        --right;
    if (left > right)
        return "";
    string result;
    bool previousSpace = false;
    for (int i = left; i <= right; ++i) {
        if (line[i] == ' ') {
            if (!previousSpace)
                result.push_back(' ');
            previousSpace = true;
        } else {
            result.push_back(line[i]);
            previousSpace = false;
        }
    }
    return result;
}

struct SamState {
    int link;
    int length;
    unordered_map<int, int> next;
    SamState() : link(-1), length(0) {}
};

class SuffixAutomaton {
private:
    vector<SamState> states;
    int last;
public:
    explicit SuffixAutomaton(const vector<int> &sequence) {
        states.reserve(max(1, static_cast<int>(sequence.size()) * 2));
        states.emplace_back();
        last = 0;
        for (int value : sequence)
            extend(value);
    }
    void extend(int value) {
        int current = static_cast<int>(states.size());
        states.emplace_back();
        states[current].length = states[last].length + 1;
        int p = last;
        while (p != -1 && states[p].next.find(value) == states[p].next.end()) {
            states[p].next[value] = current;
            p = states[p].link;
        }
        if (p == -1) {
            states[current].link = 0;
        } else {
            int q = states[p].next[value];
            if (states[p].length + 1 == states[q].length) {
                states[current].link = q;
            } else {
                int clone = static_cast<int>(states.size());
                states.push_back(states[q]);
                states[clone].length = states[p].length + 1;
                while (p != -1) {
                    auto iterator = states[p].next.find(value);
                    if (iterator == states[p].next.end() || iterator->second != q)
                        break;
                    iterator->second = clone;
                    p = states[p].link;
                }
                states[q].link = clone;
                states[current].link = clone;
            }
        }
        last = current;
    }
    int longestCommonSubstring(const vector<int> &sequence) const {
        int state = 0;
        int currentLength = 0;
        int answer = 0;
        for (int value : sequence) {
            while (state != 0 && states[state].next.find(value) == states[state].next.end()) {
                state = states[state].link;
                currentLength = states[state].length;
            }
            auto iterator = states[state].next.find(value);
            if (iterator != states[state].next.end()) {
                state = iterator->second;
                ++currentLength;
            } else {
                state = 0;
                currentLength = 0;
            }
            answer = max(answer, currentLength);
        }
        return answer;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int fragmentCount;
    while (cin >> fragmentCount) {
        string line;
        getline(cin, line);
        unordered_map<string, int> tokenIds;
        int nextTokenId = 1;
        vector<string> fileNames(fragmentCount);
        vector<vector<int>> fragments(fragmentCount);
        for (int i = 0; i < fragmentCount; ++i) {
            getline(cin, fileNames[i]);
            while (getline(cin, line) && line != "***END***") {
                string normalized = normalizeLine(line);
                if (normalized.empty())
                    continue;
                auto iterator = tokenIds.find(normalized);
                if (iterator == tokenIds.end()) {
                    tokenIds[normalized] = nextTokenId;
                    fragments[i].push_back(nextTokenId);
                    ++nextTokenId;
                } else {
                    fragments[i].push_back(iterator->second);
                }
            }
        }
        vector<int> target;
        while (getline(cin, line) && line != "***END***") {
            string normalized = normalizeLine(line);
            if (normalized.empty())
                continue;
            auto iterator = tokenIds.find(normalized);
            if (iterator == tokenIds.end()) {
                tokenIds[normalized] = nextTokenId;
                target.push_back(nextTokenId);
                ++nextTokenId;
            } else {
                target.push_back(iterator->second);
            }
        }
        SuffixAutomaton automaton(target);
        int best = 0;
        vector<int> matches(fragmentCount);
        for (int i = 0; i < fragmentCount; ++i) {
            matches[i] = automaton.longestCommonSubstring(fragments[i]);
            best = max(best, matches[i]);
        }
        if (best == 0) {
            cout << 0 << '\n';
            continue;
        }
        cout << best;
        for (int i = 0; i < fragmentCount; ++i)
            if (matches[i] == best)
                cout << ' ' << fileNames[i];
        cout << '\n';
    }
    return 0;
}
