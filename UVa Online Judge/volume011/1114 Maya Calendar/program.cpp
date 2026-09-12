#include <bits/stdc++.h>
using namespace std;

int getPos(const vector<string>& a, const string& s) {
    for (int i = 0; i < (int)a.size(); i++)
        if (a[i] == s) return i;
    return -1;
}

bool matchDate(int off, int dayNum, int dayPos, int monNum, int monPos) {
    int curDayNum = (8 + off) % 13 + 1;
    int curDayPos = (19 + off) % 20;
    int haabPos = (42 + off) % 365;
    int curMonPos, curMonNum;
    if (haabPos < 360) {
        curMonPos = haabPos / 20;
        curMonNum = haabPos % 20 + 1;
    } else {
        curMonPos = 18;
        curMonNum = haabPos - 360 + 1;
    }
    return curDayNum == dayNum && curDayPos == dayPos && curMonNum == monNum && curMonPos == monPos;
}

void printDate(int total) {
    int baktun, katun, tun, winal, kin;
    baktun = total / 144000;
    total %= 144000;
    katun = total / 7200;
    total %= 7200;
    tun = total / 360;
    total %= 360;
    winal = total / 20;
    kin = total % 20;
    cout << baktun << '.' << katun << '.' << tun << '.' << winal << '.' << kin << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<string> dayName = {"Imix", "Ik", "Akbal", "Kan", "Chikchan", "Kimi", "Manik", "Lamat", "Muluk", "Ok", "Chuen", "Eb", "Ben", "Ix", "Men", "Kib", "Kaban", "Etznab", "Kawak", "Ajaw"};
    vector<string> monName = {"Pohp", "Wo", "Sip", "Zotz", "Sek", "Xul", "Yaxkin", "Mol", "Chen", "Yax", "Sak", "Keh", "Mak", "Kankin", "Muan", "Pax", "Kayab", "Kumku", "Wayeb"};
    int tc;
    cin >> tc;
    for (int cs = 0; cs < tc; cs++) {
        string dayStr, monStr;
        cin >> dayStr >> monStr;
        int dot = dayStr.find('.');
        int dayNum = stoi(dayStr.substr(0, dot));
        string day = dayStr.substr(dot + 1);
        dot = monStr.find('.');
        int monNum = stoi(monStr.substr(0, dot));
        string mon = monStr.substr(dot + 1);
        int dayPos = getPos(dayName, day);
        int monPos = getPos(monName, mon);
        int off = -1;
        for (int i = 0; i < 18980; i++)
            if (matchDate(i, dayNum, dayPos, monNum, monPos)) {
                off = i;
                break;
            }
        if (cs) cout << '\n';
        if (off == -1) {
            cout << "NO SOLUTION\n";
            continue;
        }
        for (int total = 8 * 144000 + off; total < 10 * 144000; total += 18980)
            printDate(total);
    }
    return 0;
}
