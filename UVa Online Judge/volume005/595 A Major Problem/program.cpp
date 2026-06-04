// A Major Problem
// UVa ID: 595
// Verdict: Accepted
// Submission Date: 2026-06-04
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

map<string, vector<string>> scales;

void trick() {
    scales["C"]  = {"C", "D", "E", "F", "G", "A", "B"};
    scales["C#"] = {"C#", "D#", "E#", "F#", "G#", "A#", "B#"};
    scales["Db"] = {"Db", "Eb", "F", "Gb", "Ab", "Bb", "C"};
    scales["D"]  = {"D", "E", "F#", "G", "A", "B", "C#"};
    scales["Eb"] = {"Eb", "F", "G", "Ab", "Bb", "C", "D"};
    scales["E"]  = {"E", "F#", "G#", "A", "B", "C#", "D#"};
    scales["F"]  = {"F", "G", "A", "Bb", "C", "D", "E"};
    scales["F#"] = {"F#", "G#", "A#", "B", "C#", "D#", "E#"};
    scales["Gb"] = {"Gb", "Ab", "Bb", "Cb", "Db", "Eb", "F"};
    scales["G"]  = {"G", "A", "B", "C", "D", "E", "F#"};
    scales["Ab"] = {"Ab", "Bb", "C", "Db", "Eb", "F", "G"};
    scales["A"]  = {"A", "B", "C#", "D", "E", "F#", "G#"};
    scales["Bb"] = {"Bb", "C", "D", "Eb", "F", "G", "A"};
    scales["B"]  = {"B", "C#", "D#", "E", "F#", "G#", "A#"};
    scales["Cb"] = {"Cb", "Db", "Eb", "Fb", "Gb", "Ab", "Bb"};
}

int main() {
    trick();
    string line;
    bool firstCase = true;
    while (getline(cin, line)) {
        if (line == "*") break;
        stringstream ss(line);
        string srcKey, dstKey;
        ss >> srcKey >> dstKey;
        vector<string> notes;
        string note;
        while (ss >> note && note != "*") notes.push_back(note);
        if (!firstCase) cout << "\n";
        firstCase = false;
        bool srcValid = scales.count(srcKey), dstValid = scales.count(dstKey);
        if (!srcValid || !dstValid) {
            if (!srcValid) cout << "Key of " << srcKey << " is not a valid major key\n";
            else cout << "Key of " << dstKey << " is not a valid major key\n";
            continue;
        }
        vector<string>& src = scales[srcKey], dst = scales[dstKey];
        cout << "Transposing from " << srcKey << " to " << dstKey << ":\n";
        for (const string& m : notes) {
            cout << "  " << m;
            int idx = find(src.begin(), src.end(), m) - src.begin();
            if (idx >= src.size()) cout << " is not a valid note in the " << srcKey << " major scale\n";
            else cout << " transposes to " << dst[idx] << '\n';
        }
    }
    return 0;
}
