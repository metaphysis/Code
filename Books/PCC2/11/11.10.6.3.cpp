#include <bits/stdc++.h>

using namespace std;

int P[10240] = {};

void manacher(string &line)
{
    string modified = {'$'};
    for (int i = 0; i < line.length(); i++)
        modified.push_back(line[i]), modified.push_back('#');
    modified.back() = '|';
    
    int rightmost = 0, center = 0;
    for (int i = 0; i < modified.size(); i++)
    {
        int x = 2 * center - i, y = rightmost - i;
        P[i] = (rightmost > i) ? (P[x] < y ? P[x] : y) : 1;
        while (modified[i - P[i]] == modified[i + P[i]]) P[i]++;        
        if (i + P[i] > rightmost)
        {
            rightmost = i + P[i] - 1;
            center = i;
        }
    }
    
    for (auto c : modified)
        cout << setw(3) << right << c;
    cout << '\n';
    for (int i = 0; i < modified.size(); i++)
        cout << setw(3) << right << P[i];
    cout << '\n';
}

int main(int argc, char *argv[])
{
    string line;
    while (getline(cin, line)) manacher(line);
    return 0;
}
