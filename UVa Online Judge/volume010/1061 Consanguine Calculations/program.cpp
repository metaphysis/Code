// Consanguine Calculations
// UVa ID: 1061
// Verdict: Accepted
// Submission Date: 2017-12-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

set<string> combine(string b1, string b2)
{
    vector<string> blood = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};
    string alleles[8][2][2] = {
        {{"A", "O"}, {"+", "-"}}, {{"A", "O"}, {"-", "-"}},
        {{"B", "O"}, {"+", "-"}}, {{"B", "O"}, {"-", "-"}},
        {{"A", "B"}, {"+", "-"}}, {{"A", "B"}, {"-", "-"}},
        {{"O", "O"}, {"+", "-"}}, {{"O", "O"}, {"-", "-"}},
    };
    
    int k1 = find(blood.begin(), blood.end(), b1) - blood.begin();
    int k2 = find(blood.begin(), blood.end(), b2) - blood.begin();
    
    set<string> abo;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
        {
            string factor = alleles[k1][0][i] + alleles[k2][0][j];
            sort(factor.begin(), factor.end());
            factor.erase(unique(factor.begin(), factor.end()), factor.end());
            if (factor == "AO") factor = "A";
            if (factor == "BO") factor = "B";
            abo.insert(factor);
        }
        
    set<string> rh;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
        {
            string factor = alleles[k1][1][i] + alleles[k2][1][j];
            if (factor.find('+') != factor.npos) factor = "+";
            else factor = "-";
            rh.insert(factor);
        }

    set<string> r;
    for (auto a1 : abo)
        for (auto a2 : rh)
            r.insert(a1 + a2);
    return r;
}

set<string> find(string b1, string b2)
{
    vector<string> blood = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};
    set<string> r;
    for (auto b : blood)
        if (combine(b, b1).count(b2) > 0)
            r.insert(b);
    return r;
}

void print(set<string> r)
{
    if (r.size() == 0) cout << "IMPOSSIBLE";
    else
    {
        if (r.size() == 1) cout << *r.begin();
        else
        {
            cout << "{";
            int cnt = 0;
            for (auto b : r)
            {
                if (cnt++ > 0) cout << ", ";
                cout << b;
            }
            cout << "}";
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string parent1, parent2, child;
    int cases = 0;

    while (cin >> parent1 >> parent2 >> child)
    {
        if (parent1 == "E") break;
        cout << "Case " << ++cases << ":";
        if (child == "?")
        {
            cout << ' ' << parent1 << ' ' << parent2 << ' ';
            print(combine(parent1, parent2));
            cout << '\n';
        }
        else
        {
            if (parent1 == "?")
            {
                cout << ' ';
                print(find(parent2, child));
                cout << ' ' << parent2 << ' ' << child << '\n';
            }
            else
            {
                cout << ' ' << parent1 << ' ';
                print(find(parent1, child));
                cout << ' ' << child << '\n';
            }
        }
    }

    return 0;
}
