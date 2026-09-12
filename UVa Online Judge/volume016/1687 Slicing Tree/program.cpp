#include <bits/stdc++.h>
using namespace std;

using State = pair<int, int>;

int recW[1005], recH[1005];

void prune(vector<State> &states) {
    sort(states.begin(), states.end());
    vector<State> result;
    int bestHeight = INT_MAX;
    for (const State &state : states) {
        if (state.second < bestHeight) {
            result.push_back(state);
            bestHeight = state.second;
        }
    }
    states.swap(result);
}

vector<State> mergeStates(const vector<State> &leftStates, const vector<State> &rightStates, char type) {
    vector<State> states;
    states.reserve(leftStates.size() * rightStates.size());
    for (const State &leftState : leftStates) {
        for (const State &rightState : rightStates) {
            int width, height;
            if (type == 'H') {
                width = max(leftState.first, rightState.first);
                height = leftState.second + rightState.second;
            } else {
                width = leftState.first + rightState.first;
                height = max(leftState.second, rightState.second);
            }
            states.push_back({width, height});
        }
    }
    prune(states);
    return states;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCases, n;
    cin >> testCases;
    while (testCases--) {
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> recW[i] >> recH[i];
        vector<State> stateStack[2005];
        int top = 0;
        for (int i = 0; i < 2 * n - 1; i++) {
            string token;
            cin >> token;
            if (token == "H" || token == "V") {
                vector<State> rightStates = move(stateStack[--top]);
                vector<State> leftStates = move(stateStack[--top]);
                stateStack[top++] = mergeStates(leftStates, rightStates, token[0]);
            } else {
                int id = stoi(token);
                stateStack[top++] = {{recW[id], recH[id]}, {recH[id], recW[id]}};
                prune(stateStack[top - 1]);
            }
        }
        long long answer = LLONG_MAX;
        for (const State &state : stateStack[0]) {
            long long area = 1LL * state.first * state.second;
            answer = min(answer, area);
        }
        cout << answer << '\n';
    }
    return 0;
}
