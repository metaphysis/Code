// Intersecting Dates
// UVa ID: 1032
// Verdict: Accepted
// Submission Date: 2026-06-16
// UVa Run Time: 0.050s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

bool isLeap(int year) { return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0); }

int daysInMonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int dateToDays(int date) {
    int year = date / 10000;
    int month = (date / 100) % 100;
    int day = date % 100;
    
    int total = 0;
    for (int y = 1700; y < year; ++y) {
        total += isLeap(y) ? 366 : 365;
    }
    for (int m = 1; m < month; ++m) {
        if (m == 2) total += isLeap(year) ? 29 : 28;
        else total += daysInMonth[m];
    }
    total += day - 1;
    return total;
}

int daysToDate(int days) {
    int year = 1700;
    while (true) {
        int daysInYear = isLeap(year) ? 366 : 365;
        if (days < daysInYear) break;
        days -= daysInYear;
        ++year;
    }
    int month = 1;
    while (true) {
        int daysInMon = (month == 2) ? (isLeap(year) ? 29 : 28) : daysInMonth[month];
        if (days < daysInMon) break;
        days -= daysInMon;
        ++month;
    }
    int day = days + 1;
    return year * 10000 + month * 100 + day;
}

string formatDate(int date) {
    int year = date / 10000;
    int month = (date / 100) % 100;
    int day = date % 100;
    return to_string(month) + "/" + to_string(day) + "/" + to_string(year);
}

int main() {
    int maxDays = dateToDays(21001231) + 1;
    
    int NX, NR;
    int caseNo = 0;
    while (cin >> NX >> NR) {
        if (NX == 0 && NR == 0) break;
        
        vector<bool> flag(maxDays, false);
        vector<pair<int, int>> existing;
        
        for (int i = 0; i < NX; ++i) {
            int startDate, endDate;
            cin >> startDate >> endDate;
            int startDay = dateToDays(startDate);
            int endDay = dateToDays(endDate);
            existing.push_back({startDay, endDay});
        }
        
        for (int i = 0; i < NR; ++i) {
            int startDate, endDate;
            cin >> startDate >> endDate;
            int startDay = dateToDays(startDate);
            int endDay = dateToDays(endDate);
            for (int d = startDay; d <= endDay; ++d) flag[d] = true;
        }
        
        for (auto p : existing)
            for (int d = p.first; d <= p.second; ++d)
                flag[d] = false;
        
        vector<pair<int, int>> resultDays;
        int i = 0;
        while (i < maxDays) {
            while (i < maxDays && !flag[i]) ++i;
            if (i >= maxDays) break;
            int start = i;
            while (i < maxDays && flag[i]) ++i;
            int end = i - 1;
            resultDays.push_back({start, end});
        }
        
        vector<pair<int, int>> resultDates;
        for (auto p : resultDays) {
            int startDate = daysToDate(p.first);
            int endDate = daysToDate(p.second);
            resultDates.push_back({startDate, endDate});
        }
        
        if (caseNo) cout << '\n';
        cout << "Case " << ++caseNo << ":\n";
        if (resultDates.empty()) cout << "    No additional quotes are required.\n";
        else {
            for (size_t i = 0; i < resultDates.size(); ++i) {
                int l = resultDates[i].first, r = resultDates[i].second;
                cout << "    ";
                if (l == r) cout << formatDate(l);
                else cout << formatDate(l) << " to " << formatDate(r);
                cout << '\n';
            }
        }
    }
    return 0;
}
