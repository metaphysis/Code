// History of Languages
// UVa ID: 1671
// Verdict: Accepted
// Submission Date: 2026-08-01
// UVa Run Time: 0.080s

#include <bits/stdc++.h>
using namespace std;

struct Automaton {
    int stateCount;
    vector<int> acceptState;
    vector<vector<int>> transition;
};

Automaton readAutomaton(int alphabetSize) {
    Automaton automaton;
    cin >> automaton.stateCount;
    automaton.acceptState.resize(automaton.stateCount);
    automaton.transition.assign(automaton.stateCount, vector<int>(alphabetSize));
    for (int state = 0; state < automaton.stateCount; ++state) {
        cin >> automaton.acceptState[state];
        for (int symbol = 0; symbol < alphabetSize; ++symbol)
            cin >> automaton.transition[state][symbol];
    }
    return automaton;
}

bool isAcceptState(const Automaton& automaton, int state) {
    return state != automaton.stateCount && automaton.acceptState[state] == 1;
}

bool areEquivalent(const Automaton& automatonA, const Automaton& automatonB, int alphabetSize) {
    int deadStateA = automatonA.stateCount;
    int deadStateB = automatonB.stateCount;
    int stateSizeB = deadStateB + 1;
    long long totalStates = static_cast<long long>(deadStateA + 1) * stateSizeB;
    vector<char> visited(totalStates, 0);
    queue<int> stateQueue;
    int startCode = 0;
    visited[startCode] = 1;
    stateQueue.push(startCode);
    while (!stateQueue.empty()) {
        int code = stateQueue.front();
        stateQueue.pop();
        int stateA = code / stateSizeB;
        int stateB = code % stateSizeB;
        if (isAcceptState(automatonA, stateA) != isAcceptState(automatonB, stateB))
            return false;
        for (int symbol = 0; symbol < alphabetSize; ++symbol) {
            int nextStateA = stateA == deadStateA ? deadStateA : automatonA.transition[stateA][symbol];
            int nextStateB = stateB == deadStateB ? deadStateB : automatonB.transition[stateB][symbol];
            if (nextStateA == -1)
                nextStateA = deadStateA;
            if (nextStateB == -1)
                nextStateB = deadStateB;
            int nextCode = nextStateA * stateSizeB + nextStateB;
            if (!visited[nextCode]) {
                visited[nextCode] = 1;
                stateQueue.push(nextCode);
            }
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int alphabetSize;
    int caseNumber = 1;
    while (cin >> alphabetSize && alphabetSize != 0) {
        Automaton automatonA = readAutomaton(alphabetSize);
        Automaton automatonB = readAutomaton(alphabetSize);
        cout << "Case #" << caseNumber << ": ";
        cout << (areEquivalent(automatonA, automatonB, alphabetSize) ? "Yes" : "No") << '\n';
        ++caseNumber;
    }
    return 0;
}
