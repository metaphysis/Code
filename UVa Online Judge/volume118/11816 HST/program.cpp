// HST
// UVa ID: 11816
// Verdict: Accepted
// Submission Date: 2018-03-05
// UVa Run Time: 0.150s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct tax
{
    long long pst, gst, hst;
    tax (long long pst = 0, long long gst = 0, long long hst = 0): pst(pst), gst(gst), hst(hst) {}
};

long long ROUND(long long n)
{
     long long r = n % 10000LL;
     n /= 10000LL;
     if (r >= 5000LL) n++;
     return n;
}

long long STOI(string n)
{
    if (n.back() == '%') n.pop_back();
    long long before = 0, after = 0;
    for (int i = 0; i < n.length(); i++)
    {
        if (n[i] == '.')
        {
            int digits = 0;
            for (int j = i + 1; j < n.length(); j++)
            {
                after = after * 10LL + (n[j] - '0');
                digits++;
            }
            if (digits == 1) after *= 10LL;
            break;
        }
        else
        {
            before = before * 10LL + (n[i] - '0');
        }
    }
    return before * 100LL + after;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string name, pst, gst, hst, money;
    int cases, n, m;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        map<string, tax> taxes;

        cin >> n >> m;
        for (int i = 0; i < n; i++)
        {
            cin >> name >> pst >> gst >> hst;
            taxes.insert(make_pair(name, tax(STOI(pst), STOI(gst), STOI(hst))));
        }

        long long PST_GST = 0, HST = 0;
        for (int i = 0; i < m; i++)
        {
            cin >> name >> money;
            long long n = 0;
            for (auto d : money)
            {
                if (d == '$' || d == '.') continue;
                n = n * 10LL + d - '0';
            }
            tax t = taxes[name];
            PST_GST += ROUND(n * t.pst) + ROUND(n * t.gst);
            HST += ROUND(n * t.hst);
        }

        long long r = HST - PST_GST;
        if (r < 0) cout << '-';
        r = abs(r);
        cout << r / 100LL << '.' << setw(2) << right << setfill('0') << r % 100LL << '\n';
    }

    return 0;
}
