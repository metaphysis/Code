// Demerit Points
// UVa ID: 10028
// Verdict: Accepted
// Submission Date: 2021-12-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct DATE
{
    int year, month, day;
    DATE (int year = 0, int month = 0, int day = 0): year(year), month(month), day(day) {}
    DATE (string s)
    {
        year = stoi(s.substr(0, 4));
        month = stoi(s.substr(4, 2));
        day = stoi(s.substr(6, 2));
    }
    bool operator<=(const DATE &dt) const
    {
        if (year != dt.year) return year < dt.year;
        if (month != dt.month) return month < dt.month;
        return day <= dt.day;
    }
    DATE addYear(int y) { return DATE(year + y, month, day); }
    friend ostream& operator<<(ostream &out, const DATE &dt)
    {
        out << dt.year << '-';
        out << setfill('0') << setw(2) << dt.month << '-';
        out << setw(2) << dt.day;
        return out;
    }
};

void printInfo(DATE dt, int demerit, int merit)
{
    cout << dt << ' ';
    if (!demerit && !merit) { cout << "No merit or demerit points.\n"; return; }
    if (demerit) { cout << demerit << " demerit point(s).\n"; return; }
    if (merit) { cout << merit << " merit point(s).\n"; return; }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    cin.ignore(256, '\n');
    string line;
    getline(cin, line);
    for (int cs = 0; cs < cases; cs++)
    {
        if (cs) cout << '\n';
        getline(cin, line);
        DATE lastDate(line);
        int demerit = 0, merit = 0;
        printInfo(lastDate, demerit, merit);
        while (getline(cin, line))
        {
            if (!line.length()) break;
            int pos = line.find(' ');
            DATE nowDate(line.substr(0, pos));
            int points = stoi(line.substr(pos + 1));
            while (lastDate.addYear(1) <= nowDate)
            {
                if (demerit)
                {
                    lastDate = lastDate.addYear(1);
                    demerit = max(0, min(demerit / 2, demerit - 2));
                    printInfo(lastDate, demerit, merit);
                }
                else break;
            }
            while (lastDate.addYear(2) <= nowDate)
            {
                lastDate = lastDate.addYear(2);
                merit += 1;
                printInfo(lastDate, demerit, merit);
            }
            lastDate = nowDate;
            demerit += points;
            if (demerit <= 2 * merit) demerit = 0, merit /= 2;
            else demerit -= 2 * merit, merit = 0;
            printInfo(lastDate, demerit, merit);
        }
        while (demerit)
        {
            lastDate = lastDate.addYear(1);
            demerit = max(0, min(demerit / 2, demerit - 2));
            printInfo(lastDate, demerit, merit);
        }
        while (merit < 5)
        {
            lastDate = lastDate.addYear(2);
            merit += 1;
            printInfo(lastDate, demerit, merit);
        }
    }
    
    return 0;
}
