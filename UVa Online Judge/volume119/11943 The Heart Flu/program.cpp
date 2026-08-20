#include <bits/stdc++.h>
using namespace std;

bool isPass(const vector<double>& vals) {
    int n = vals.size(), valley = 0;
    if ((n - 1) * 10 < 60 || (n - 1) * 10 > 100)
        return false;
    for (double val : vals)
        if (fabs(val) > 35)
            return false;
    for (int i = 1; i + 1 < n; i++)
        if (vals[i] < vals[i - 1] && vals[i] < vals[i + 1])
            valley++;
    return valley <= 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    int cases = 0;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        size_t first = line.find('*'), second = line.find('*', first + 1);
        string name = line.substr(0, first), age = line.substr(first + 1, second - first - 1);
        string data = line.substr(second + 1);
        vector<double> vals;
        string item;
        stringstream ss(data);
        while (getline(ss, item, ',')) vals.push_back(stod(item));
        if (cases++) cout << "---\n";
        cout << name << '\n';
        cout << age << '\n';
        cout << "Triage " << (isPass(vals) ? "PASS" : "NO PASS") << '\n';
    }
    return 0;
}
