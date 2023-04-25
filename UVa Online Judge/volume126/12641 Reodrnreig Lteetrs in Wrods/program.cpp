// Reodrnreig Lteetrs in Wrods
// UVa ID: 12641
// Verdict: Accepted
// Submission Date: 2023-04-25
// UVa Run Time: 0.010s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
int T, cd, ct;
string dict[210][2];
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    cin >> T;
    cin.ignore(256, '\n');
    string line;
    for (int cs = 1; cs <= T; cs++) {
        getline(cin, line);
        istringstream iss(line);
        string w;
        cd = 0;
        while (iss >> dict[cd][0]) {
            dict[cd][1] = dict[cd][0];
            if (dict[cd][1].length() > 2)
                sort(dict[cd][1].begin() + 1, dict[cd][1].begin() + dict[cd][1].length() - 1);
            cd++;
        }
        getline(cin, line);
        iss.clear();
        iss.str(line);
        ct = 0;
        while (iss >> w) {
            if (ct++) cout << ' ';
            int flag = 0;
            string ww = w;
            if (ww.length() > 2) sort(ww.begin() + 1, ww.begin() + ww.length() - 1);
            for (int i = 0; i < cd && !flag; i++)
                if (ww == dict[i][1]) {
                    cout << dict[i][0];
                    flag = 1;
                }
            if (!flag) cout << w;
        }
        cout << '\n';
    }
    return 0;
}
