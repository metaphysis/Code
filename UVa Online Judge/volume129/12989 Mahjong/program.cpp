#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;
const int maxRank = 200;
const int maxTile = 200;
const int maxState = 50;

unsigned long long oneNext[maxState][5];
vector<unsigned long long> stateMask;
vector<array<int, 5>> stateNext;
vector<vector<int>> answer;

int getStateId(unsigned long long mask) {
    for (int i = 0; i < (int)stateMask.size(); i++)
        if (stateMask[i] == mask) return i;
    stateMask.push_back(mask);
    stateNext.push_back(array<int, 5>());
    return (int)stateMask.size() - 1;
}

void buildOneNext() {
    for (int a = 0; a < 5; a++)
        for (int b = 0; b < 5; b++)
            for (int p = 0; p < 2; p++) {
                int from = (a * 5 + b) * 2 + p;
                for (int c = 0; c <= 4; c++) {
                    unsigned long long mask = 0;
                    for (int pairUse = 0; pairUse <= 1; pairUse++) {
                        if (pairUse && p) continue;
                        for (int pung = 0; pung <= 1; pung++)
                            for (int start = 0; start <= 4; start++) {
                                int used = a + b + 2 * pairUse + 3 * pung + start;
                                if (used != c) continue;
                                if (used > 4) continue;
                                int nextP = p | pairUse;
                                int to = (b * 5 + start) * 2 + nextP;
                                mask |= 1ULL << to;
                            }
                    }
                    oneNext[from][c] = mask;
                }
            }
}

void buildAutomaton() {
    stateMask.clear();
    stateNext.clear();
    getStateId(1ULL << 0);
    for (int index = 0; index < (int)stateMask.size(); index++)
        for (int c = 0; c <= 4; c++) {
            unsigned long long nextMask = 0;
            unsigned long long currentMask = stateMask[index];
            for (int state = 0; state < maxState; state++)
                if ((currentMask >> state) & 1ULL)
                    nextMask |= oneNext[state][c];
            int nextId = getStateId(nextMask);
            stateNext[index][c] = nextId;
        }
}

void buildAnswer() {
    int stateCount = (int)stateMask.size();
    vector<vector<int>> dp(stateCount, vector<int>(maxTile + 1, 0));
    vector<vector<int>> nextDp(stateCount, vector<int>(maxTile + 1, 0));
    answer.assign(maxRank + 1, vector<int>(maxTile + 1, 0));
    dp[0][0] = 1;
    for (int rank = 1; rank <= maxRank; rank++) {
        for (int state = 0; state < stateCount; state++)
            fill(nextDp[state].begin(), nextDp[state].end(), 0);
        for (int state = 0; state < stateCount; state++)
            for (int sum = 0; sum <= maxTile; sum++) {
                int current = dp[state][sum];
                if (current == 0) continue;
                for (int tile = 0; tile <= 4; tile++) {
                    if (sum + tile > maxTile) continue;
                    int nextState = stateNext[state][tile];
                    nextDp[nextState][sum + tile] += current;
                    if (nextDp[nextState][sum + tile] >= mod)
                        nextDp[nextState][sum + tile] -= mod;
                }
            }
        dp.swap(nextDp);
        for (int sum = 0; sum <= maxTile; sum++) {
            int total = 0;
            for (int state = 0; state < stateCount; state++)
                if ((stateMask[state] >> 1) & 1ULL) {
                    total += dp[state][sum];
                    if (total >= mod) total -= mod;
                }
            answer[rank][sum] = total;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    buildOneNext();
    buildAutomaton();
    buildAnswer();
    int testCount;
    cin >> testCount;
    for (int testCase = 1; testCase <= testCount; testCase++) {
        int k, m;
        cin >> k >> m;
        cout << "Case #" << testCase << ": " << answer[k][m] << '\n';
    }
    return 0;
}
