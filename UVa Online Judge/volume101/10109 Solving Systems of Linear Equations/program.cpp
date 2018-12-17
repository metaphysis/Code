// Solving Systems of Linear Equations
// UVa ID: 10109
// Verdict: Accepted
// Submission Date: 2018-12-17
// UVa Run Time: 0.310s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

typedef long long int lli;

struct fraction
{
    lli numerator, denominator;

    void normalize()
    {
        if (denominator < 0LL) denominator *= -1LL, numerator *= -1LL;
        if (numerator == 0LL && denominator != 0LL) denominator = 1LL;
	    if (numerator != 0LL && denominator != 0LL)
        {
	        lli g = __gcd(abs(numerator), denominator);
            numerator /= g, denominator /= g;
        }
    }
    
    bool isZero()
    {
        return numerator == 0LL;
    }
    
    void setZero()
    {
        numerator = 0LL, denominator = 1LL;
    }
    
    void setOne()
    {
        numerator = 1LL, denominator = 1LL;
    }

    fraction operator+(const fraction &f)
    {
	    fraction r;
        lli g = __gcd(denominator, f.denominator);
        r.numerator = (f.denominator / g * numerator) + (denominator / g * f.numerator);
        r.denominator = denominator / g * f.denominator;
        r.normalize();
        return r;
    }
    
    fraction operator-(const fraction &f)
    {
        fraction r;
        lli g = __gcd(denominator, f.denominator);
        r.numerator = (f.denominator / g * numerator) - (denominator / g * f.numerator);
        r.denominator = denominator / g * f.denominator;
        r.normalize();
        return r;
    }
    
    fraction operator*(const fraction &f)
    {
        fraction r;
        lli g1 = __gcd(abs(numerator), f.denominator), g2 = __gcd(abs(f.numerator), denominator);
        r.numerator = (numerator / g1) * (f.numerator / g2);
        r.denominator = (denominator / g2) * (f.denominator / g1);
        r.normalize();
        return r;
    }
    
    fraction operator/(const fraction &f)
    {
        fraction r;
        lli g1 = __gcd(abs(numerator), abs(f.numerator)), g2 = __gcd(f.denominator, denominator);
        r.numerator = (numerator / g1) * (f.denominator / g2);
        r.denominator = (denominator / g2) * (f.numerator / g1);
        r.normalize();
        return r;
    }
};

ostream& operator<<(ostream &os, const fraction &f)
{
    if (f.denominator == 1) os << f.numerator;
    else os << f.numerator << '/' << f.denominator;
    return os;
}
    
fraction getFraction(string s)
{
    long long sign1 = 1LL, sign2 = 1LL;
    if (s.front() == '-')
    {
        sign1 = -1LL;
        s.erase(s.begin());
    }
    
    fraction f;
    if (s.find('/') != s.npos)
    {
        f.numerator = 0LL;
        for (int i = 0; i < s.length(); i++)
            if (s[i] != '/')
                f.numerator = f.numerator * 10LL + (long long)(s[i] - '0');
            else
            {
                int j = i + 1;
                if (s[j] == '-')
                {
                    sign2 = -1LL;
                    j++;
                }
                f.denominator = 0LL;
                for (; j < s.length(); j++)
                    f.denominator = f.denominator * 10LL + (long long)(s[j] - '0');
                break;
            }
    }
    else
    {
        f.numerator = 0LL;
        for (int i = 0; i < s.length(); i++)
            f.numerator = f.numerator * 10LL + (long long)(s[i] - '0');
        f.denominator = 1LL;
    }
    f.numerator *= sign1;
    f.denominator *= sign2;
    f.normalize();
    return f;
}

void show(vector<vector<fraction>> A)
{
    for (auto a : A)
    {
        for (auto f : a)
            cout << f << ' ';
        cout << '\n';
    }
    cout << '\n';
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
        // If the number of equations less than number of unknowns, add last equation untill
        // number of equations equal number of unknowns.
        //for (int i = E; i < U; i++) A.push_back(A.back());
        // Reset the number of equations.
        //E = max(E, U);

        for (int i = 0; i < min(U, E); i++)
        //for (int i = 0; i < E; i++)
        {
            if (A[i][i].isZero())
            {
                for (int j = i + 1; j < E; j++)
                    if (!A[j][i].isZero())
                    {
                        swap(A[i], A[j]);
                        break;
                    }
            }
            if (A[i][i].isZero()) continue;
            for (int j = i + 1; j <= U; j++)
                A[i][j] = A[i][j] / A[i][i];
            A[i][i].setOne();
            for (int j = 0; j < E; j++)
            {
                if (i != j)
                {
                    for (int k = i + 1; k <= U; k++)
                        A[j][k] = A[j][k] - (A[j][i] * A[i][k]);
                    A[j][i].setZero();
                }
            }
        }

        int Z = 0, impossible = 0;
        for (int i = 0; i < E; i++)
        {
            bool allZero = true;
            for (int j = 0; j < U; j++)
                if (!A[i][j].isZero())
                {
                    allZero = false;
                    break;
                }
            if (allZero)
            {
                if (!A[i][U].isZero())
                {
                    impossible = 1;
                    break;
                }
                else Z++;
            }
        }

        if (impossible) cout << "No Solution.\n";
        else
        {
            if (U <= E - Z)
            {
                for (int i = 0; i < U; i++)
                    cout << "x[" << i + 1 << "] = " << A[i][U] << '\n';
            }
            else
                cout << "Infinitely many solutions containing " << U + Z - E << " arbitrary constants.\n";
        }
    }

    return 0;
}
