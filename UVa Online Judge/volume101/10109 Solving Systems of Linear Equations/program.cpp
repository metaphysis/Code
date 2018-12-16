// Solving Systems of Linear Equations
// UVa ID: 10109
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct fraction
{
    ll numerator, denominator;

    void normalize()
    {
	    if (numerator != 0 && denominator != 0)
        {
	        ll g = __gcd(abs(numerator), abs(denominator));
            numerator /= g, denominator /= g;
        }
        if (numerator == 0 && denominator != 0) denominator = 1LL;
        if (denominator < 0) denominator *= -1LL, numerator *= -1LL;
    }
    
    fraction operator+(const fraction &f)
    {
	    fraction r;
        ll g = __gcd(denominator, f.denominator);
        r.numerator = f.denominator / g * numerator + denominator / g * f.numerator;
        r.denominator = denominator / g * f.denominator;
        r.normalize();
        return r;
    }
    
    fraction operator-(const fraction &f)
    {
        fraction r;
        ll g = __gcd(denominator, f.denominator);
        r.numerator = f.denominator / g * numerator - denominator / g * f.numerator;
        r.denominator = denominator / g * f.denominator;
        r.normalize();
        return r;
    }
    
    fraction operator*(const fraction &f)
    {
        fraction r;
        ll g1 = __gcd(abs(numerator), f.denominator), g2 = __gcd(abs(f.numerator), denominator);
        r.numerator = (numerator / g1) * (f.numerator / g2);
        r.denominator = (denominator / g2) * (f.denominator / g1);
        r.normalize();
        return r;
    }
    
    fraction operator/(const fraction &f)
    {
        fraction r;
        ll g1 = __gcd(abs(numerator), abs(f.numerator)), g2 = __gcd(f.denominator, denominator);
        r.numerator = (numerator / g1) * (f.denominator / g2);
        r.denominator = (denominator / g2) * (f.numerator / g1);
        r.normalize();
        return r;
    }
    
    friend ostream& operator<<(ostream& os, const fraction &f)
    {
        if (f.denominator == 1) os << f.numerator;
        else os << f.numerator << '/' << f.denominator;
        return os;
    }
};

fraction getFraction(string s)
{
    long long sign = 1;
    if (s.front() == '-')
    {
        sign = -1;
        s.erase(s.begin());
    }
    
    fraction f;
    if (s.find('/') != s.npos)
    {
        f.numerator = 0;
        for (int i = 0; i < s.length(); i++)
            if (s[i] != '/')
                f.numerator = f.numerator * 10 + s[i] - '0';
            else
            {
                f.denominator = 0;
                for (int j = i + 1; j < s.length(); j++)
                    f.denominator = f.denominator * 10 + s[j] - '0';
                break;
            }
    }
    else
    {
        f.numerator = 0;
        for (int i = 0; i < s.length(); i++)
            f.numerator = f.numerator * 10 + s[i] - '0';
        f.denominator = 1;
    }
    f.numerator *= sign;
    return f;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string s;
    int cases = 0, N, U, E;

    while (cin >> N)
    {
        if (N == 0) break;
        if (cases++) cout << '\n';
        cout << "Solution for Matrix System # " << N << '\n';

        cin >> U >> E;
        vector<vector<fraction>> A;
        for (int i = 0; i < E; i++)
        {
            vector<fraction> a;
            for (int j = 0; j <= U; j++)
            {
                cin >> s;
                a.push_back(getFraction(s));
            }
            A.push_back(a);
        }

        int Z = 0, impossible = 0;
        for (int i = 0; i < E; i++)
        {
            if (A[i][i].numerator == 0)
            {
                bool allZero = true;
                for (int j = 0; j < U; j++)
                    if (A[i][j].numerator != 0)
                    {
                        allZero = false;
                        break;
                    }
                if (allZero)
                {
                    if (A[i][U].numerator != 0)
                    {
                        impossible = 1;
                        break;
                    }
                    else Z++;
                }
                continue;
            }
            for (int j = i + 1; j <= U; j++)
                A[i][j] = A[i][j] / A[i][i];
            A[i][i].numerator = A[i][i].denominator = 1;
            for (int j = 0; j < E; j++)
            {
                if (i != j)
                {
                    for (int k = i + 1; k <= U; k++)
                        A[j][k] = A[j][k] - (A[j][i] * A[i][k]);
                    A[j][i].numerator = 0, A[j][i].denominator = 1;
                }
            }
        }
        if (impossible) cout << "No Solution.\n";
        else
        {
            if (U <= E - Z)
            {
                for (int i = 0; i < U; i++)
                {
                    cout << "X[" << i + 1 << "] = ";
                    for (int j = 0; j < E; j++)
                        if (A[j][i].numerator != 0)
                        {
                            cout << A[j][U] << '\n';
                            break;
                        }
                }
            }
            else
            {
                cout << "Infinitely many solutions containing " << U + Z - E << " arbitrary constants.\n";
            }
        }
    }

    return 0;
}
