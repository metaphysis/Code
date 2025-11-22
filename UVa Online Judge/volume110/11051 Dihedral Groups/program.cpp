// Dihedral Groups
// UVa ID: 11051
// Verdict: Accepted
// Submission Date: 2025-11-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n && n) {
        string line;
        getline(cin, line);
        getline(cin, line);
        
        long long a = 0;
        int b = 0;
        stringstream ss(line);
        string token;
        
        while (ss >> token) {
            char op = token[0];
            int num = stoi(token.substr(1));
            if (op == 'r') b ? a -= num : a += num;
            else b = (b + num) % 2;
        }
        
        a %= n;
        if (a < 0) a += n;
        
        vector<pair<int, string>> candidates;
        if (b == 0) {
            if (a == 0) candidates.push_back({0, ""});
            else candidates.push_back({a, "r" + to_string(a)});
            if (n - a > 0) candidates.push_back({n - a + 2, "m1 r" + to_string(n - a) + " m1"});
        } else {
            if (a == 0) candidates.push_back({1, "m1"});
            else candidates.push_back({a + 1, "r" + to_string(a) + " m1"});
            if (n - a == 0) candidates.push_back({1, "m1"});
            else candidates.push_back({n - a + 1, "m1 r" + to_string(n - a)});
        }
        
        auto best = candidates[0];
        for (size_t i = 1; i < candidates.size(); i++)
            if (candidates[i].first < best.first) best = candidates[i];
        
        cout << (best.second.empty() ? "\n" : best.second + "\n");
    }
    
    return 0;
}
