#include <bits/stdc++.h>
using namespace std;

const int mod = 10000000;

struct AcNode {
    int next[62], fail, bMask, eMask, keep;
    bool isPrefix;
    AcNode() {
        fill(next, next + 62, -1);
        fail = bMask = eMask = keep = 0;
        isPrefix = false;
    }
};

void addPattern(vector<AcNode>& ac, string pattern, int ruleId, bool isEnd, const vector<int>& charId) {
    reverse(pattern.begin(), pattern.end());
    int u = 0;
    for (char ch : pattern) {
        ac[u].isPrefix = true;
        int c = charId[(unsigned char)ch];
        if (ac[u].next[c] == -1) {
            int v = ac.size();
            ac[u].next[c] = v;
            ac.push_back(AcNode());
        }
        u = ac[u].next[c];
    }
    if (isEnd) ac[u].eMask |= 1 << ruleId;
    else ac[u].bMask |= 1 << ruleId;
}

void buildAc(vector<AcNode>& ac, int alphabetSize) {
    queue<int> que;
    ac[0].isPrefix = true;
    for (int c = 0; c < alphabetSize; ++c) {
        int v = ac[0].next[c];
        if (v == -1) ac[0].next[c] = 0;
        else que.push(v);
    }
    while (!que.empty()) {
        int u = que.front(), f = ac[u].fail;
        que.pop();
        ac[u].bMask |= ac[f].bMask;
        ac[u].eMask |= ac[f].eMask;
        ac[u].keep = ac[u].isPrefix ? u : ac[f].keep;
        for (int c = 0; c < alphabetSize; ++c) {
            int v = ac[u].next[c];
            if (v == -1) ac[u].next[c] = ac[f].next[c];
            else {
                ac[v].fail = ac[f].next[c];
                que.push(v);
            }
        }
    }
}

int solve(int kabobSize, const string& alphabet, const string& rules) {
    vector<int> charId(256, -1);
    int alphabetSize = alphabet.size(), ruleCount = 0, left = 0;
    for (int i = 0; i < alphabetSize; ++i) charId[(unsigned char)alphabet[i]] = i;
    vector<AcNode> ac(1);
    while (left < (int)rules.size()) {
        int right = left, split = left;
        while (right < (int)rules.size() && rules[right] != '|') ++right;
        while (rules[split] != '>') ++split;
        addPattern(ac, rules.substr(left, split - left), ruleCount, false, charId);
        addPattern(ac, rules.substr(split + 1, right - split - 1), ruleCount, true, charId);
        ++ruleCount;
        left = right + 1;
    }
    buildAc(ac, alphabetSize);
    int nodeCount = ac.size(), maskCount = 1 << ruleCount;
    vector<int> stateId(nodeCount * maskCount, -1), stateNode(1, 0), stateMask(1, 0);
    vector<vector<pair<int, int>>> graph(1);
    stateId[0] = 0;
    for (int state = 0; state < (int)stateNode.size(); ++state) {
        int u = stateNode[state], mask = stateMask[state];
        vector<int> targets;
        for (int c = 0; c < alphabetSize; ++c) {
            int v = ac[u].next[c];
            if ((ac[v].bMask & ~mask) != 0) continue;
            int nextMask = mask | ac[v].eMask, nextNode = ac[v].keep;
            int key = nextMask * nodeCount + nextNode, nextState = stateId[key];
            if (nextState == -1) {
                nextState = stateNode.size();
                stateId[key] = nextState;
                stateNode.push_back(nextNode);
                stateMask.push_back(nextMask);
                graph.push_back(vector<pair<int, int>>());
            }
            targets.push_back(nextState);
        }
        sort(targets.begin(), targets.end());
        for (int i = 0; i < (int)targets.size();) {
            int j = i + 1;
            while (j < (int)targets.size() && targets[j] == targets[i]) ++j;
            graph[state].push_back(make_pair(targets[i], j - i));
            i = j;
        }
    }
    int stateCount = stateNode.size();
    vector<int> dp(stateCount, 0), nextDp(stateCount, 0);
    dp[0] = 1;
    for (int len = 0; len < kabobSize; ++len) {
        fill(nextDp.begin(), nextDp.end(), 0);
        for (int state = 0; state < stateCount; ++state) {
            if (dp[state] == 0) continue;
            for (const auto& edge : graph[state]) {
                int target = edge.first, count = edge.second;
                nextDp[target] = (nextDp[target] + 1LL * dp[state] * count) % mod;
            }
        }
        dp.swap(nextDp);
    }
    int answer = 0;
    for (int ways : dp) {
        answer += ways;
        if (answer >= mod) answer -= mod;
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int kabobSize;
    string alphabet, rules;
    while (cin >> kabobSize >> alphabet >> rules) cout << solve(kabobSize, alphabet, rules) << '\n';
    return 0;
}
