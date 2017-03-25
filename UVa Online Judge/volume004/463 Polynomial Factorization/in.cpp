#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_CASES = 100, DEGREE = 4, BASE = 50;

struct polynominal
{
    vector<int> coefficients;

    polynominal() {}

    polynominal(int a1, int a0)
    {
        coefficients.clear();
        coefficients.push_back(a1);
        coefficients.push_back(a0);
    }
    
    bool operator<(const polynominal &poly) const
    {
        if (coefficients.size() != poly.coefficients.size())
            return coefficients.size() < poly.coefficients.size();

        for (int i = 0; i < coefficients.size(); i++)
            if (coefficients[i] != poly.coefficients[i])
                return coefficients[i] < poly.coefficients[i];
    }
};

polynominal multiple(polynominal p1, polynominal p2)
{
    polynominal r;
    r.coefficients.assign(p1.coefficients.size() + p2.coefficients.size() - 1, 0);
        for (int i = 0; i < p1.coefficients.size(); i++)
            for (int j = 0; j < p2.coefficients.size(); j++)
                r.coefficients[i + j] += p1.coefficients[i] * p2.coefficients[j];
    return r;
}

int main(int argc, char *argv[])
{
    //srand(time(NULL));

    for (int c = 1; c <= MAX_CASES; c++)
    {
        polynominal poly;
        poly.coefficients.push_back(1);

        vector<polynominal> answer;
        for (int i = 1; i <= DEGREE; i++)
        {
            int a = rand() % BASE + 1;
            int b = rand() % BASE;
            
            if (rand() % 2 == 1) b *= (-1);
            
            poly = multiple(poly, polynominal{a, b});
            answer.push_back(polynominal{a, b});
        }
        
        for (int i = 0; i < poly.coefficients.size(); i++)
        {
            if (i > 0) cout << ' ';
            cout << poly.coefficients[i];
        }
        cout << '\n';
        
        //sort(answer.begin(), answer.end());
        //for (int i = 0; i < answer.size(); i++)
        //{
        //    for (int j = 0; j < answer[i].coefficients.size(); j++)
        //    {
        //        if (j > 0) cout << ' ';
        //        cout << answer[i].coefficients[j];
        //    }
        //    cout << '\n';
        //}
        //cout << '\n';
    }
    
    return 0;
}
