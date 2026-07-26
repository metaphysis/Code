// Subway Timing
// UVa ID: 1088
// Verdict: Accepted
// Submission Date: 2026-07-25
// UVa Run Time: 0.020s
// https://blog.csdn.net/metaphysis/article/details/163183713

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    int timeValue;
};

struct State {
    int maxDown;
    int minDown;
};

class SubwaySolver {
private:
    int stationCount;
    vector<vector<Edge>> graph;

    vector<State> pruneStates(vector<State> states, int limit) {
        vector<State> validStates;
        for (const State &state : states)
            if (state.maxDown <= limit && state.minDown >= -limit)
                validStates.push_back(state);
        sort(validStates.begin(), validStates.end(), [](const State &firstState, const State &secondState) {
            if (firstState.maxDown != secondState.maxDown)
                return firstState.maxDown < secondState.maxDown;
            return firstState.minDown > secondState.minDown;
        });
        vector<State> result;
        int bestMinDown = -limit - 1;
        for (const State &state : validStates)
            if (state.minDown > bestMinDown) {
                result.push_back(state);
                bestMinDown = state.minDown;
            }
        return result;
    }

    vector<State> calculateStates(int currentNode, int parentNode, int limit) {
        vector<State> currentStates;
        currentStates.push_back({0, 0});
        for (const Edge &edge : graph[currentNode]) {
            if (edge.to == parentNode)
                continue;
            vector<State> childStates = calculateStates(edge.to, currentNode, limit);
            vector<State> nextStates;
            int remainder = edge.timeValue % 60;
            vector<int> errors;
            errors.push_back(-remainder);
            if (remainder != 0)
                errors.push_back(60 - remainder);
            for (const State &currentState : currentStates)
                for (const State &childState : childStates)
                    for (int edgeError : errors) {
                        int childMax = childState.maxDown + edgeError;
                        int childMin = childState.minDown + edgeError;
                        if (currentState.maxDown + childMax > limit)
                            continue;
                        if (currentState.minDown + childMin < -limit)
                            continue;
                        State nextState;
                        nextState.maxDown = max(currentState.maxDown, childMax);
                        nextState.minDown = min(currentState.minDown, childMin);
                        nextStates.push_back(nextState);
                    }
            currentStates = pruneStates(nextStates, limit);
            if (currentStates.empty())
                break;
        }
        return currentStates;
    }

    bool isFeasible(int limit) {
        vector<State> result = calculateStates(1, 0, limit);
        return !result.empty();
    }

public:
    void solve() {
        int caseNumber = 1;
        while (cin >> stationCount && stationCount != 0) {
            graph.assign(stationCount + 1, vector<Edge>());
            for (int i = 0; i < stationCount - 1; ++i) {
                int firstStation;
                int secondStation;
                int timeValue;
                cin >> firstStation >> secondStation >> timeValue;
                graph[firstStation].push_back({secondStation, timeValue});
                graph[secondStation].push_back({firstStation, timeValue});
            }
            int left = 0;
            int right = 59 * (stationCount - 1);
            while (left < right) {
                int middle = (left + right) / 2;
                if (isFeasible(middle))
                    right = middle;
                else
                    left = middle + 1;
            }
            cout << "Case " << caseNumber << ": " << left << '\n';
            ++caseNumber;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    SubwaySolver solver;
    solver.solve();
    return 0;
}
