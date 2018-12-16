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
        if (numerator == 0 && denominator != 0) denominator = 1;
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
};
