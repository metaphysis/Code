// Polynomial Factorization
// UVa ID: 463
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct polynominal
{
    vector<int> coefficients;
    
    polynominal() {}
    
    polynominal(int a4, int a3, int a2, int a1, int a0)
    {
        coefficients.clear();
        coefficients.push_back(a4);
        coefficients.push_back(a3);
        coefficients.push_back(a2);
        coefficients.push_back(a1);
        coefficients.push_back(a0);
    }
    
    bool operator<(const polynominal &poly) const
    {
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

int isRoot(polynominal poly, pair<int, int> root)
{
    int value = 0;
    for (int i = 0; i < poly.coefficients.size(); i++)
    {
        for (int j = 0; j < poly.coefficients.size() - i; j++)
            poly.coefficients[i] *= root.first;
        for (int j = 0; j < i; j++)
            poly.coefficients[i] *= root.second;
        value += poly.coefficients[i];
    }
    return value == 0;
}

// 根据有理数根定理找到方程的解。
void findRoots(polynominal &poly, vector<pair<int, int>> &roots)
{
    if (poly.coefficients.back() == 0)
    {
        roots.push_back(make_pair(0, 1));
        return;
    }

    vector<int> p, q;

    int pp = abs(poly.coefficients.front());
    int qq = abs(poly.coefficients.back());

    for (int i = 1; i <= pp; i++)
        if (pp % i == 0)
            p.push_back(i);

    for (int i = 1; i <= qq; i++)
        if (qq % i == 0)
            q.push_back(i);

    
    for (int i = 0; i < p.size(); i++)
        for (int j = 0; j < q.size(); j++)
            if (gcd(p[i], q[j]) == 1)
            {
                pair<int, int> root1 = make_pair(p[i], q[j]);
                if (isRoot(poly, root1)) roots.push_back(root1);
                
                pair<int, int> root2 = make_pair(-p[i], q[j]);
                if (isRoot(poly, root2)) roots.push_back(root2);
            }
}

int main(int argc, char *argv[])
{
    //cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        polynominal poly;
        
        int number;
        istringstream iss(line);
        while (iss >> number)
            poly.coefficients.push_back(number);

        vector<polynominal> polys;
        
        int highestDegree = 4;
        
        while (true)
        {
            vector<pair<int, int>> roots;
            
            findRoots(poly, roots);
             
            if (roots.size() == 0)
            {
                polys.push_back(poly);
                break;
            }

            // 多项式的长除法。
            for (int i = 0; i < roots.size(); i++)
            {
                pair<int, int> root = roots[i];
                cout << "root: " << root.first << ' ' << root.second << '\n';
                
                polys.push_back(polynominal{0, 0, 0, root.second, -root.first});
                
                int c1 = root.second, c2 = -root.first;
                
                polynominal quotient;

                for (int j = 0; j < 4; j++)
                {
                    int factor = poly.coefficients[j] / c1;
                    quotient.coefficients.push_back(factor);
                    poly.coefficients[j + 1] -= factor * c2;
                }

                poly.coefficients.swap(quotient.coefficients);
                for (int j = 0; j < poly.coefficients.size(); j++)
                    cout << poly.coefficients[j] << ' ';
                cout << '\n';
                
                highestDegree--;
            }

            if (highestDegree == 0) break;
        }
        
        sort(polys.begin(), polys.end());
        
        for (int i = 0; i < polys.size(); i++)
        {
            int start = 0;
            while (polys[i].coefficients[start] == 0) start++;
            
            for (int j = start; j < polys[i].coefficients.size(); j++)
            {
                if (j > start) cout << ' ';
                cout << polys[i].coefficients[j];
            }
            cout << '\n';
        }
        cout << '\n';
    }
    
    return 0;
}
