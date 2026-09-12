#include <bits/stdc++.h>
using namespace std;

int getBase(string name) {
    if (name == "Do") return 0;
    if (name == "Re") return 2;
    if (name == "Mi") return 4;
    if (name == "Fa") return 5;
    if (name == "Sol") return 7;
    if (name == "La") return 9;
    return 11;
}

int getPitch(string note) {
    int p, octave, change;
    string name;
    p = 0;
    while (p < (int)note.size() && note[p] != '#' && note[p] != 'b' && !isdigit(note[p])) p++;
    name = note.substr(0, p);
    change = 0;
    if (p < (int)note.size() && note[p] == '#') {
        change = 1;
        p++;
    } else if (p < (int)note.size() && note[p] == 'b') {
        change = -1;
        p++;
    }
    octave = note[p] - '0';
    return octave * 12 + getBase(name) + change;
}

int solve() {
    int n, i, pitch, low, high;
    string note;
    while (cin >> n && n) {
        vector<int> pitches(n);
        low = INT_MAX;
        high = INT_MIN;
        for (i = 0; i < n; i++) {
            cin >> note;
            pitches[i] = getPitch(note);
            low = min(low, pitches[i]);
            high = max(high, pitches[i]);
        }
        vector<int> count(high - low + 1, 0);
        for (auto pitch : pitches) count[pitch - low]++;
        for (i = 0; i <= high - low; i++) {
            if (i) cout << ' ';
            cout << count[i];
        }
        cout << '\n';
    }
    return 0;
}

int main() {
    return solve();
}
