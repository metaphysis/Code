// Calories from Fat
// UVa ID: 10554
// Verdict: Accepted
// Submission Date: 2017-12-29
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

pair<double, double> getC(string line)
{
    double fatC = 0.0, totalC = 0.0;
    bool fatIsPercent = false;
    double fatPercent = 0, percent = 0;
    double energy[5] = {9, 4, 4, 4, 7};
    double calories[5];

    string ingredient;
    istringstream iss(line);
    for (int i = 0; i < 5; i++)
    {
        iss >> ingredient;
        calories[i] = 0;

        double k = stoi(ingredient.substr(0, ingredient.length() - 1));
        if (ingredient.back() == 'g') 
        {
            calories[i] = k * energy[i];
            totalC += calories[i];
        }
        else if (ingredient.back() == 'C')
        {
            calories[i] = k;
            totalC += calories[i];
        }
        else
        {
            percent += k;
            if (i == 0)
            {
                fatPercent = k;
                fatIsPercent = true;
            }
        }
    }

    totalC = totalC * 100.0 / (100.0 - percent);
    if (fatIsPercent) fatC = totalC * fatPercent / 100.0;
    else fatC = calories[0];

    return make_pair(fatC, totalC);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line), line != "-")
    {
        double fatC = 0, totalC = 0;
        pair<double, double> c = getC(line);
        fatC += c.first, totalC += c.second;
        while (getline(cin, line))
        {
            if (line == "-") break;
            c = getC(line);
            fatC += c.first, totalC += c.second;
        }
        cout << fixed << setprecision(0) << (fatC / totalC * 100.0) << "%\n";
    }

    return 0;
}
