// Make Palindrome Checker
// UVa ID: 10848
// Verdict: Accepted
// Submission Date: 2023-04-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    string line;
    while (getline(cin, line)) {
        string a, c;
        int idx = 0;
        int p1 = true;
        while (idx < line.length()) {
            if (line[idx] == ' ') break;
            if (!islower(line[idx])) { p1 = false; break; }
            a += line[idx];
            idx++;
        }
        //cout << a << '\n';
        if (p1) p1 = a.length() <= 1000;
        if (!p1 || line[idx] != ' ') { cout << "FFFFFFF The solution is not accepted\n"; continue; }

        int b = 0;
        string digits;
        idx++;
        while (idx < line.length()) {
            if (line[idx] == ' ') break;
            if (!isdigit(line[idx])) { p1 = false; break; };
            digits += line[idx];
            b = b * 10 + line[idx] - '0';
            if (b > 1000) { p1 = false; break; }
            idx++;
        }
        //cout << b << '\n';
        if (!digits.size() || digits.size() >= 2 && digits.front() == '0') p1 = false;
        if (p1) p1 = 0 <= b && b <= 1000;
        if (!p1 || line[idx] != ' ') { cout << "FFFFFFF The solution is not accepted\n"; continue; }

        idx++;
        while (idx < line.length()) {
            if (!islower(line[idx])) { p1 = false; break; }
            c += line[idx];
            idx++;
        }
        //cout << c << '\n';
        if (p1) p1 = c.length() <= 2000;
        if (!p1) { cout << "FFFFFFF The solution is not accepted\n"; continue; }

        cout << 'T';

        int p2 = true;
        for (int i = 0, j = c.length() - 1; i <= j; i++, j--)
            if (c[i] != c[j]) {
                p2 = false;
                break;
            }
        cout << (p2 ? 'T' : 'F');
        
        int cnt1[26] = {0}, cnt2[26] = {0};
        for (auto ch : a) cnt1[ch - 'a']++;
        for (auto ch : c) cnt2[ch - 'a']++;
        int p3 = true;
        for (int i = 0; i < 26; i++)
            if (cnt1[i] && !cnt2[i]) {
                p3 = false;
                break;
            }
        cout << (p3 ? 'T' : 'F');
        
        int p4 = true;
        for (int i = 0; i < 26; i++)
            if (cnt1[i] > cnt2[i]) {
                p4 = false;
                break;
            }
        cout << (p4 ? 'T' : 'F');
        
        int p5 = true;
        int k1 = 0, k2 = 0;
        for (k1 = 0, k2 = 0; k1 < a.length() && k2 < c.length(); ) {
            if (a[k1] == c[k2]) k1++, k2++;
            else k2++;
        }
        p5 = k1 == a.length();
        cout << (p5 ? 'T' : 'F');
        
        int p6 = a.length() + b == c.length();
        cout << (p6 ? 'T' : 'F');
        
        int p7 = b < a.length();
        cout << (p7 ? 'T' : 'F');
        
        if (p1 && p2 && p3 && p4 && p5 && p6 && p7) cout << " The solution is accepted\n";
        else cout << " The solution is not accepted\n";
    }
    return 0;
}
