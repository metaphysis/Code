// Long Multiplication
// UVa ID: 338
// Verdict: Accepted
// Submission Date: 2016-07-05
// UVa Run Time: 0.090s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

string multiplication(long long x, long long y)
{
    if (x == 0 || y == 0)
        return "0";

    if (x <= 999999999 && y <= 999999999)
        return to_string(x * y);

    vector<string> lines;
    for (int rightSpace = 0; y > 0; y /= 10, rightSpace++)
    {
        long long temp = x * (y % 10);
        string zz = to_string(temp) + string(rightSpace, '0');
        reverse(zz.begin(), zz.end());
        lines.push_back(zz);
    }

    string z;
    int carray = 0;
    for (int i = 0; i < lines.back().length(); i++)
    {
        int sum = 0;
        for (int j = 0; j < lines.size(); j++)
            if (i < lines[j].length())
                sum += lines[j][i] - '0';
        sum += carray;
        carray = sum / 10;
        z.push_back(sum % 10 + '0');
    }
    
    z.push_back(carray + '0');
    reverse(z.begin(), z.end());
    while (z.front() == '0') z.erase(z.begin());

    return z;
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    long long x, y;
    string z;

    while (cin >> x >> y)
    {
        z = multiplication(x, y);

        int maxXYLength = max(to_string(x).length(), to_string(y).length());
        int maxLength = max((int)(z.length()), maxXYLength);

        cout << setw(maxLength) << right << x << endl;
        cout << setw(maxLength) << right << y << endl;
        cout << setw(maxLength) << right << string(maxXYLength, '-') << endl;
        
        if (y <= 9 || x == 0)
            cout << setw(maxLength) << right << z << endl;
        else
        {
            vector<pair<int, string>> lines;
            for (int rightSpace = 0; y > 0; y /= 10, rightSpace++)
            {
                long long temp = x * (y % 10);
                if (temp == 0) continue;
                lines.push_back(make_pair(rightSpace, to_string(temp)));
            }

            if (lines.size() > 1)
            {
                for (auto line : lines)
                    cout << setw(maxLength - line.first) << right << line.second << endl;
                cout << setw(maxLength) << right << string(z.length(), '-') << endl;
            }
            cout << z << endl;
        }
        cout << endl;
    }

	return 0;
}
