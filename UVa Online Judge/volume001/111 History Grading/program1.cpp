// History Grading
// UVa ID: 111
// Verdict: Accepted
// Submission Date: 2016-02-29
// UVa Run Time: 0.003s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 25;

int order[MAXN], events[MAXN], length[MAXN], n;

int lis() {
    for (int i = 1; i <= n; i++) length[i] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j < i; j++)
            if (events[j] < events[i] && (length[j] + 1) > length[i])
                length[i] = length[j] + 1;
    int maxLength = 1;
    for (int i = 1; i <= n; i++)
        maxLength = max(maxLength, length[i]);
    return maxLength;
}

int main(int argc, char *argv[]) {
    string line;
    int index;
    order[0] = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> index;
        order[index] = i;
    }
    cin.ignore(1024, '\n');
    while (getline(cin, line)) {
        istringstream iss(line);
        for (int i = 1; i <= n; i++) {
            iss >> index;
            events[index] = find(order, order + n, i) - order;
        }
        cout << lis() << endl;
    }
    return 0;
}
