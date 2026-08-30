#include <bits/stdc++.h>
using namespace std;

struct State {
    unsigned long long lo, hi;
    bool operator == (const State &x) const { return lo == x.lo && hi == x.hi; }
    bool operator != (const State &x) const { return !(*this == x); }
};

struct StateHash {
    size_t operator () (const State &x) const {
        return hash<unsigned long long>()(x.lo) ^ (hash<unsigned long long>()(x.hi) << 1);
    }
};

struct Result { int cost, guess; };

int n, m, codeCount;
string codeText[81];
int digit[81][4];
unsigned char feedback[81][81];

unordered_map<State, Result, StateHash> memo;

State emptyState() { return {0, 0}; }

State allState() {
    State state = emptyState();
    for (int i = 0; i < codeCount; i++) {
        if (i < 64) state.lo |= 1ULL << i;
        else state.hi |= 1ULL << (i - 64);
    }
    return state;
}

bool contains(const State &state, int id) {
    if (id < 64) return (state.lo >> id) & 1ULL;
    return (state.hi >> (id - 64)) & 1ULL;
}

void insertCode(State &state, int id) {
    if (id < 64) state.lo |= 1ULL << id;
    else  state.hi |= 1ULL << (id - 64);
}

int sizeOf(const State &state) { return __builtin_popcountll(state.lo) + __builtin_popcountll(state.hi); }

int singleCode(const State &state) {
    if (state.lo) return __builtin_ctzll(state.lo);
    if (state.hi) return 64 + __builtin_ctzll(state.hi);
    return -1;
}

int feedbackId(int black, int white) { return black * (n + 1) + white; }

void calculateFeedback(int guess, int secret, int &black, int &white) {
    int guessCount[10] = {0};
    int secretCount[10] = {0};
    black = 0;
    for (int i = 0; i < n; i++) {
        if (digit[guess][i] == digit[secret][i]) black++;
        guessCount[digit[guess][i]]++;
        secretCount[digit[secret][i]]++;
    }
    int common = 0;
    for (int d = 1; d <= m; d++) common += min(guessCount[d], secretCount[d]);
    white = common - black;
}

void buildFeedbackTable() {
    for (int guess = 0; guess < codeCount; guess++)
        for (int secret = 0; secret < codeCount; secret++) {
            int black, white;
            calculateFeedback(guess, secret, black, white);
            feedback[guess][secret] = (unsigned char)feedbackId(black, white);
        }
}

void split(const State &state, int guess, State bucket[64], unsigned char count[64]) {
    for (int i = 0; i < 64; i++) {
        bucket[i] = emptyState();
        count[i] = 0;
    }
    for (int secret = 0; secret < codeCount; secret++) {
        if (!contains(state, secret)) continue;
        int id = feedback[guess][secret];
        insertCode(bucket[id], secret);
        count[id]++;
    }
}

int solve(const State &state);

int costForGuess(const State &state, int guess) {
    State bucket[64];
    unsigned char count[64];
    split(state, guess, bucket, count);
    int total = sizeOf(state);
    for (int id = 0; id < 64; id++) {
        if (count[id] == 0) continue;
        if (count[id] == 1) {
            int secret = singleCode(bucket[id]);
            if (secret != guess) total++;
        } else if (bucket[id] != state) {
            total += solve(bucket[id]);
        }
    }
    return total;
}

int solve(const State &state) {
    auto it = memo.find(state);
    if (it != memo.end()) return it->second.cost;
    int stateSize = sizeOf(state);
    if (stateSize == 1) {
        int secret = singleCode(state);
        memo[state] = {1, secret};
        return 1;
    }
    int bestCost = INT_MAX, bestGuess = -1;
    for (int guess = 0; guess < codeCount; guess++) {
        State bucket[64];
        unsigned char count[64];
        split(state, guess, bucket, count);
        bool useful = false;
        for (int id = 0; id < 64; id++) {
            if (count[id] > 0 && bucket[id] != state) {
                useful = true;
                break;
            }
        }
        if (!useful) continue;
        int currentCost = costForGuess(state, guess);
        if (currentCost < bestCost) {
            bestCost = currentCost;
            bestGuess = guess;
        }
    }
    memo[state] = {bestCost, bestGuess};
    return bestCost;
}

void generateCodes(int pos, string &text) {
    if (pos == n) {
        codeText[codeCount] = text;
        for (int i = 0; i < n; i++) digit[codeCount][i] = text[i] - '0';
        codeCount++;
        return;
    }
    for (int d = 1; d <= m; d++) {
        text.push_back(char('0' + d));
        generateCodes(pos + 1, text);
        text.pop_back();
    }
}

string makeStep(int guess, int black, int white) {
    return codeText[guess] + ":" + to_string(black) + "," + to_string(white);
}

void buildPath(const State &state, int secret, vector<string> &path) {
    int guess = memo.find(state)->second.guess;
    // 必须针对当前实际猜测和该行真实密码重新生成反馈。
    int id = feedback[guess][secret];
    int black = id / (n + 1), white = id % (n + 1);
    path.push_back(makeStep(guess, black, white));
    if (guess == secret) return;
    State bucket[64];
    unsigned char count[64];
    split(state, guess, bucket, count);
    if (count[id] == 1) {
        path.push_back(makeStep(secret, n, 0));
        return;
    }
    buildPath(bucket[id], secret, path);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string firstGuess;
    while (cin >> n >> m >> firstGuess) {
        codeCount = 0;
        memo.clear();
        string text;
        generateCodes(0, text);
        buildFeedbackTable();
        State root = allState();
        int total;
        if (firstGuess == "0") total = solve(root);
        else {
            int rootGuess = 0;
            while (rootGuess < codeCount && codeText[rootGuess] != firstGuess) rootGuess++;
            total = costForGuess(root, rootGuess);
            memo[root] = {total, rootGuess};
        }
        cout << total << '\n';
        for (int secret = 0; secret < codeCount; secret++) {
            vector<string> path;
            buildPath(root, secret, path);
            for (int i = 0; i < (int)path.size(); i++) {
                if (i > 0) cout << ' ';
                cout << path[i];
            }
            cout << '\n';
        }
        cout << '\n';
    }
    return 0;
}
