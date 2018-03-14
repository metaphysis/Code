// History Grading
// UVa ID: 111
// Verdict: Accepted
// Submission Date: 2016-05-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

vector<int> order, events;

int getScores()
{
    vector<int> length; length.push_back(events.front());
    for (auto it = events.begin() + 1; it != events.end(); it++)
        if (*it > length.back()) length.push_back(*it);
        else {
            auto location = upper_bound(length.begin(), length.end(), *it);
            *location = *it;
        }
    return length.size();
}

int main(int argc, char *argv[])
{
    int n, index; string line;

    cin >> n;
    order.resize(n); events.resize(n);
    for (int i = 1; i <= n; i++) {
        cin >> index;
        order[index - 1] = i;
    }

    cin.ignore(1024, '\n');
    while (getline(cin, line)) {
        istringstream iss(line);
        for (int i = 1; i <= n; i++) {
            iss >> index;
            events[index - 1] = find(order.begin(), order.end(), i) - order.begin();
        }
        cout << getScores() << '\n';
    }

    return 0;
}
