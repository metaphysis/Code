#include <bits/stdc++.h>

using namespace std;

int P[10240] = {};

void manacher(string &line)
{
    string modified = {'#'};
    for (int i = 0; i < line.length(); i++)
        modified.push_back(line[i]), modified.push_back('#');
    
    int center = 0, rightmost = 0, low = 0, high = 0;
    for (int i = 0; i < modified.length(); i++)
    {
        if (rightmost > i)
        {
            if (P[2 * center - i] < (rightmost - i)) P[i] = P[2 * center - i], high = low = -1;
            else P[i] = rightmost - i, high = rightmost + 1, low = 2 * i - high;
        }
        else P[i] = 0, low = i - 1, high = i + 1;

        while (low >= 0 && high < modified.length() && modified[low] == modified[high])
            P[i]++, low--, high++;

        if ((i + P[i]) > rightmost)
        {
            center = i;
            rightmost = i + P[i];
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
