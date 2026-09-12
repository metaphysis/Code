// Decoding the Hallway
// UVa ID: 12681
// Verdict: Accepted
// Submission Date: 2026-08-06
// UVa Run Time: 0.040s

#include <bits/stdc++.h>
using namespace std;

string transformString(string value) {
    reverse(value.begin(), value.end());
    for (char &ch : value) ch = ch == 'L' ? 'R' : 'L';
    return value;
}

string takePrefix(string value, int limit) {
    if ((int)value.size() > limit) value.resize(limit);
    return value;
}

string takeSuffix(string value, int limit) {
    if ((int)value.size() > limit) value = value.substr(value.size() - limit);
    return value;
}

bool containsString(const string &text, const string &pattern) {
    return text.find(pattern) != string::npos;
}

bool solve(int n, const string &target) {
    int length = target.size();
    string other = transformString(target), prefix = "L", suffix = "L";
    bool foundTarget = target == "L", foundOther = other == "L";
    for (int level = 2; level <= n; level++) {
        string otherPrefix = transformString(suffix), otherSuffix = transformString(prefix);
        string border = suffix + "L" + otherPrefix;
        bool crossTarget = containsString(border, target), crossOther = containsString(border, other);
        bool nextTarget = foundTarget || foundOther || crossTarget, nextOther = foundOther || foundTarget || crossOther;
        string nextPrefix = prefix;
        if ((int)nextPrefix.size() < length) nextPrefix = takePrefix(prefix + "L" + otherPrefix, length);
        string nextSuffix = takeSuffix(suffix + "L" + otherSuffix, length);
        prefix = nextPrefix;
        suffix = nextSuffix;
        foundTarget = nextTarget;
        foundOther = nextOther;
    }
    return foundTarget;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int caseId = 1; caseId <= testCount; caseId++) {
        int n;
        string target;
        cin >> n >> target;
        cout << "Case " << caseId << ": " << (solve(n, target) ? "Yes" : "No") << '\n';
    }
    return 0;
}
