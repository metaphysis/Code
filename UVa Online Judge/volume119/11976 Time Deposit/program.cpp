#include <bits/stdc++.h>
using namespace std;

struct Date {
    int y, m, d;
};

bool isLeap(int y) {
    return y % 4 == 0;
}

int getDays(int y, int m) {
    int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (m == 2 && isLeap(y)) return 29;
    return days[m];
}

Date parseDate(string s) {
    Date date;
    date.y = stoi(s.substr(0, 4));
    date.m = stoi(s.substr(5, 2));
    date.d = stoi(s.substr(8, 2));
    return date;
}

int getKey(Date date) {
    return date.y * 10000 + date.m * 100 + date.d;
}

bool lessEq(Date a, Date b) {
    if (a.y != b.y) return a.y < b.y;
    if (a.m != b.m) return a.m < b.m;
    return a.d <= b.d;
}

void nextDay(Date &date) {
    date.d++;
    if (date.d > getDays(date.y, date.m)) {
        date.d = 1;
        date.m++;
        if (date.m > 12) {
            date.m = 1;
            date.y++;
        }
    }
}

int getWeek(Date date) {
    int days = 0;
    for (int y = 1975; y < date.y; y++) days += isLeap(y) ? 366 : 365;
    for (int m = 1; m < date.m; m++) days += getDays(date.y, m);
    days += date.d - 1;
    return (days + 2) % 7;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n;
    cin >> t;
    for (int cs = 1; cs <= t; cs++) {
        unordered_map<int, char> ex;
        cin >> n;
        for (int i = 0; i < n; i++) {
            string s;
            char type;
            cin >> s >> type;
            ex[getKey(parseDate(s))] = type;
        }
        string s1, s2;
        cin >> s1 >> s2;
        Date cur = parseDate(s1), end = parseDate(s2);
        int week = getWeek(cur), ans = 0;
        while (lessEq(cur, end)) {
            int key = getKey(cur);
            if (ex.count(key)) {
                if (ex[key] == 'W') ans++;
            } else if (week < 5) ans++;
            nextDay(cur);
            week = (week + 1) % 7;
        }
        cout << "Case " << cs << ": " << ans << '\n';
    }
    return 0;
}
