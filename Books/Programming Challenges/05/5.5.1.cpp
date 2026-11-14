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
