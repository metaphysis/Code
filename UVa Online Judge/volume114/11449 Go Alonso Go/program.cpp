#include <bits/stdc++.h>
using namespace std;

const double inf = 1e100;
const double eps = 1e-9;

struct State {
    double time;
    int stops, initialFuel;
};

bool isBetter(const State &a, const State &b) {
    if (a.time < b.time - eps) return true;
    if (fabs(a.time - b.time) <= eps && a.stops < b.stops) return true;
    if (fabs(a.time - b.time) <= eps && a.stops == b.stops && a.initialFuel < b.initialFuel) return true;
    return false;
}

void updateState(State &target, const State &candidate) {
    if (isBetter(candidate, target)) target = candidate;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        cin.ignore(64, '\n');
        string name, token;
        getline(cin, name);
        int lapCount;
        double circuitLength;
        cin >> lapCount >> circuitLength;
        cin >> token;
        int initialFuel, capacity;
        cin >> initialFuel >> capacity;
        cin >> token;
        double fullLapTime, fuelFactor;
        cin >> fullLapTime >> fuelFactor;
        cin.ignore(64, '\n');
        getline(cin, token);
        double pitTime, refuelTime, pitLineTime;
        cin >> pitTime >> refuelTime >> pitLineTime;
        cin >> token;
        int consumption;
        cin >> consumption;
        vector<State> current(capacity + 1), next(capacity + 1);
        for (int fuel = 0; fuel <= capacity; fuel++) {
            current[fuel] = {inf, 0, -1};
            next[fuel] = {inf, 0, -1};
        }
        current[initialFuel] = {0.0, 0, initialFuel};
        for (int fuel = 0; fuel <= capacity; fuel++) {
            State candidate = {pitLineTime, 0, fuel};
            updateState(current[fuel], candidate);
        }
        State answer = {inf, 0, -1};
        for (int lap = 1; lap <= lapCount; lap++) {
            for (int fuel = 0; fuel <= capacity; fuel++)
                next[fuel] = {inf, 0, -1};
            for (int fuel = consumption; fuel <= capacity; fuel++) {
                if (current[fuel].time >= inf / 2) continue;
                double lapTime = fullLapTime - (capacity - fuel) * fuelFactor / 10.0;
                State base = current[fuel];
                base.time += lapTime;
                int remainFuel = fuel - consumption;
                if (lap == lapCount) {
                    updateState(answer, base);
                    continue;
                }
                updateState(next[remainFuel], base);
                for (int newFuel = remainFuel + 1; newFuel <= capacity; newFuel++) {
                    State candidate = base;
                    candidate.time += pitTime + (newFuel - remainFuel) * refuelTime;
                    candidate.stops++;
                    updateState(next[newFuel], candidate);
                }
            }
            current.swap(next);
        }
        cout << name << '\n';
        cout << "Estimated time\n";
        cout << fixed << setprecision(2) << answer.time << '\n';
        cout << "Initial fuel\n";
        cout << answer.initialFuel << '\n';
        cout << "Pit stops\n";
        cout << answer.stops << '\n';
    }
    return 0;
}
