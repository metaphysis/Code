// Solving Systems of Linear Equations
// UVa ID: 10109
// Verdict: Accepted
// Submission Date: 2018-12-17
// UVa Run Time: 0.320s
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
        if (denominator < 0) denominator *= -1, numerator *= -1;
        if (numerator == 0 && denominator != 0) denominator = 1;
	    if (numerator != 0 && denominator != 0)
        {
	        lli g = __gcd(abs(numerator), denominator);
            numerator /= g, denominator /= g;
        }
    }
    
    bool isZero()
    {
        return numerator == 0;
    }
    
    void setZero()
    {
        numerator = 0, denominator = 1;
    }
    
    void setOne()
    {
        numerator = 1, denominator = 1;
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
    long long sign1 = 1, sign2 = 1;
    if (s.front() == '-')
    {
        sign1 = -1;
        s.erase(s.begin());
    }
    
    fraction f;
    if (s.find('/') != s.npos)
    {
        f.numerator = 0;
        for (int i = 0; i < s.length(); i++)
            if (s[i] != '/')
                f.numerator = f.numerator * 10 + (s[i] - '0');
            else
            {
                int j = i + 1;
                if (s[j] == '-')
                {
                    sign2 = -1;
                    j++;
                }
                f.denominator = 0;
                for (; j < s.length(); j++)
                    f.denominator = f.denominator * 10 + (s[j] - '0');
                break;
            }
    }
    else
    {
        f.numerator = 0;
        for (int i = 0; i < s.length(); i++)
            f.numerator = f.numerator * 10 + (s[i] - '0');
        f.denominator = 1;
    }
    f.numerator *= sign1;
    f.denominator *= sign2;
    f.normalize();
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

        for (int i = 0, j = 0; i < E && j < U; )
        {
            if (A[i][j].isZero())
            {
                for (int m = i + 1; m < E; m++)
                    if (!A[m][j].isZero())
                    {
                        swap(A[i], A[m]);
                        break;
                    }
            }
            if (A[i][j].isZero())
            {
                j++;
                continue;
            }
            for (int n = U; n >= j; n--)
                A[i][n] = A[i][n] / A[i][j];
            for (int m = 0; m < E; m++)
            {
                if (i != m)
                    for (int n = U; n >= j; n--)
                        A[m][n] = A[m][n] - (A[m][j] * A[i][n]);
            }
            i++, j++;
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
