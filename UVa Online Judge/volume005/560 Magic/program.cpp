// Magic
// UVa ID: 560
// Verdict: Accepted
// Submission Date: 2017-05-13
// UVa Run Time: 0.010s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

bool bigger(string &n1, string &n2)
{
    if (n1.length() != n2.length()) return n1.length() > n2.length();
    for (int i = 0; i < n1.length(); i++)
        if (n1[i] != n2[i])
            return n1[i] > n2[i];
    return false;
}

pair<bool, string> mod3(string &n)
{
    int remainder = 0;
    string quotient;

    for (auto c : n) remainder += (c - '0');
    if (remainder % 3 != 0) return make_pair(false, quotient);
    
    remainder = 0;
    for (auto c : n)
    {
        remainder *= 10;
        remainder += (c - '0');
        if (quotient.size() == 0 && remainder < 3) continue;
        quotient += (char)('0' + remainder / 3);
        remainder %= 3;
    }

    return make_pair(true, quotient);
}

pair<bool, string> modK(string &n, int k)
{
    int remainder = 0;
    string quotient;

    for (auto c : n)
    {
        remainder *= 10;
        remainder += (c - '0');
        if (quotient.size() == 0 && remainder < k) continue;
        quotient += (char)('0' + remainder / k);
        remainder %= k;
    }

    return make_pair(remainder == 0, quotient);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0, times[2] = {3, 7};
    cin >> cases;
    
    unordered_set<string> visited;
    queue<string> unvisited;
    
    string number;
    for (int c = 1; c <= cases; c++)
    {
        cin >> number;

        visited.clear();
        unvisited.push(number);
        string maxNumber = "0";

        while (!unvisited.empty())
        {
            string current = unvisited.front();
            unvisited.pop();

            if (!bigger(current, maxNumber)) continue;

            bool added = false;
            pair<bool, string> r = mod3(current);
            if (r.first && visited.find(r.second) == visited.end())
            {
                visited.insert(r.second);
                unvisited.push(r.second);
            }
            if (r.first) added = true;

            r = modK(current, 7);
            if (r.first && visited.find(r.second) == visited.end())
            {
                visited.insert(r.second);
                unvisited.push(r.second);
            }
            if (r.first) added = true;

            for (int i = 0; i < current.size(); i++)
                if (current[i] == '3' || current[i] == '7')
                {
                    string next(current);
                    next.erase(next.begin() + i);
                    while (next.size() > 0 && next.front() == '0') next.erase(next.begin());
                    if (visited.find(next) == visited.end()) 
                    {
                        visited.insert(next);
                        unvisited.push(next);
                    }
                    added = true;
                }

            for (int i = 0; i < current.size(); i++)
                for (int k = 0; k <= 1; k++)
                {
                    bool same = true;
                    for (int j = 0; j < times[k]; j++)
                        if ((i + j) >= current.size() || current[i + j] != current[i])
                        {
                            same = false;
                            break;
                        }

                    if (same)
                    {
                        string next(current);
                        next.erase(next.begin() + i, next.begin() + i + times[k]);
                        while (next.size() > 0 && next.front() == '0') next.erase(next.begin());
                        if (visited.find(next) == visited.end())
                        {
                            visited.insert(next);
                            unvisited.push(next);
                        }
                        added = true;
                    }
                }

            if (!added && bigger(current, maxNumber)) maxNumber = current;
        }

        cout << maxNumber << '\n';
    }
    
    return 0;
}
