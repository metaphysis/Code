// Polynomial Factorization
// UVa ID: 463
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct polynomial
{
    vector<int> coefficients;

    polynomial() {}

    polynomial(int a1, int a0)
    {
        coefficients.clear();
        coefficients.push_back(a1);
        coefficients.push_back(a0);
    }

    bool operator<(const polynomial &poly) const
    {
        if (coefficients.size() != poly.coefficients.size())
            return coefficients.size() < poly.coefficients.size();

        for (int i = 0; i < coefficients.size(); i++)
            if (coefficients[i] != poly.coefficients[i])
                return coefficients[i] < poly.coefficients[i];
    }
};

int gcd(int a, int b)
{
    if (b == 0) return a;
    else return gcd(b, a % b);
}

bool isRoot(polynomial &poly, pair<int, int> &root)
{
    //int size = poly.coefficients.size();
    //vector <long long> ps(size + 1, 1), qs(size + 1, 1);
    //for (int i = 1; i <= size; i++)
    //{
    //    ps[i] = ps[i - 1] * root.first;
    //    qs[i] = qs[i - 1] * root.second;
    //}

    //long long value = 0;
    //for (int i = 0; i < size; i++)
    //    value += poly.coefficients[i] * ps[size - i] * qs[i];
    //return value == 0;
    
    double quotient = (double)root.first / (double)root.second;
    double multiple = 1.0;
    double value = 0.0;
    for (int i = poly.coefficients.size() - 1; i >= 0; i--)
    {
        value += poly.coefficients[i] * multiple;
        multiple *= quotient;
    }
    
    return fabs(value) < 1e-7;
}

// 根据有理数根定理找到方程的解。
vector<pair<int, int>> findRoots(polynomial &poly)
{
    vector<pair<int, int>> roots;
    vector<int> p, q;

    int pp = abs(poly.coefficients.back());
    int qq = abs(poly.coefficients.front());

    for (int i = 1; i <= pp; i++)
        if ((pp % i) == 0)
            p.push_back(i);

    for (int i = 1; i <= qq; i++)
        if ((qq % i) == 0)
            q.push_back(i);

    for (int j = 0; j < q.size(); j++)
        for (int i = 0; i < p.size(); i++)
            if (gcd(p[i], q[j]) == 1)
            {
                pair<int, int> root1 = make_pair(p[i], q[j]);
                if (isRoot(poly, root1))
                    roots.push_back(root1);

                pair<int, int> root2 = make_pair(-p[i], q[j]);
                if (isRoot(poly, root2))
                    roots.push_back(root2);
            }
            
    return roots;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        polynomial poly;

        int c;
        istringstream iss(line);
        while (iss >> c) poly.coefficients.push_back(c);
        
        vector<polynomial> polys;
        
        while (poly.coefficients.size() > 2 && poly.coefficients.back() == 0)
        {
            polys.push_back(polynomial{1, 0});
            poly.coefficients.erase(poly.coefficients.end() - 1);
        }
        
        if (poly.coefficients.size() > 2)
        {
            vector<pair<int, int>> roots = findRoots(poly);
            
            if (roots.size() > 0)
            {
                for (int i = 0; i < roots.size(); i++)
                {
                    if (poly.coefficients.size() <= 2) break;
                    
                    pair<int, int> root = roots[i];
                    polys.push_back(polynomial{root.second, -root.first});
                    int c1 = root.second, c2 = -root.first;
                    polynomial quotient;

                    for (int j = 0; j < poly.coefficients.size() - 1; j++)
                    {
                        int factor = poly.coefficients[j] / c1;
                        quotient.coefficients.push_back(factor);
                        poly.coefficients[j + 1] -= factor * c2;
                    }
                    
                    if (quotient.coefficients.front() == 0) { while (true) {} }
                    
                    poly.coefficients.swap(quotient.coefficients);
                }
            }
        }
        polys.push_back(poly);

        sort(polys.begin(), polys.end());

        for (int i = 0; i < polys.size(); i++)
        {
            for (int j = 0; j < polys[i].coefficients.size(); j++)
            {
                if (j > 0) cout << ' ';
                cout << polys[i].coefficients[j];
            }
            cout << '\n';
        }
        cout << '\n';
    }

    return 0;
}
