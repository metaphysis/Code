#include <bits/stdc++.h>
using namespace std;

unordered_map<string, int> wordCnt;
char buf[25];

int main() {
    string line;
    while (true) {
        wordCnt.clear();
        int total = 0;
        bool endFlag = false;
        while (getline(cin, line)) {
            if (line == "****END_OF_TEXT****") break;
            if (line == "****END_OF_INPUT****") { endFlag = true; break; }
            int pos = 0;
            for (char ch : line) {
                if (ch == ',' || ch == '.' || ch == ':' || ch == ';' || ch == '!' || ch == '?' || ch == '"' || ch == '(' || ch == ')' || isspace(ch)) {
                    if (pos > 0) {
                        buf[pos] = '\0';
                        string s(buf);
                        for (char &c : s) c = tolower(c);
                        wordCnt[s]++;
                        total++;
                        pos = 0;
                    }
                } else {
                    buf[pos++] = ch;
                }
            }
            if (pos > 0) {
                buf[pos] = '\0';
                string s(buf);
                for (char &c : s) c = tolower(c);
                wordCnt[s]++;
                total++;
            }
        }
        if (endFlag) break;
        double logLambda = log10(total);
        double et = 0.0;
        for (auto &p : wordCnt) et += p.second * (logLambda - log10(p.second));
        et /= total;
        int erel = round(et / logLambda * 100);
        printf("%d %.1f %d\n", total, et, erel);
    }
    return 0;
}
