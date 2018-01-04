// Triangle
// UVa ID: 194
// Verdict: Accepted
// Submission Date: 2016-03-24
// UVa Run Time: 0.006s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <iomanip>
#include <map>
#include <cmath>

using namespace std;

const double EPSILON = 1E-6, PI = 2.0 * acos(0.0), HALF_PI = PI / 2.0;

map<char, double> p, old;
map<char, bool> defined;
string variable = "aAbBcC";
bool multiSolution = false;

double acos(double x, double y, double z)
{
    return acos((x * x + y * y - z * z) / (2 * x * y));
}

bool calculate()
{
    if (defined['a'] && defined['b'] && defined['c'])
    {
        if (p['a'] + p['b'] <= p['c'] ||
            p['b'] + p['c'] <= p['a'] || p['a'] + p['c'] <= p['b'])
            return false;
            
        p['A'] = acos(p['b'], p['c'], p['a']);
        p['B'] = acos(p['a'], p['c'], p['b']);
        p['C'] = acos(p['a'], p['b'], p['c']);
        
        return true;
    }
    
    string angles[] = { "ABC", "ACB", "BCA" };
    for (int i = 0; i < 3; i++)
    {
        string v = angles[i];
        if (defined[v[0]] && defined[v[1]] && !defined[v[2]])
        {
            if (p[v[0]] + p[v[1]] >= PI)
                return false;
            old[v[2]] = p[v[2]] = PI - p[v[0]] - p[v[1]];
            defined[v[2]] = true;
            break;
        }
    }
    
    if (defined['A'] && defined['B'] && defined['C'])
    {
        if (abs(p['A'] + p['B'] + p['C'] - PI) > EPSILON)
            return false;
           
        if (!defined['a'] && !defined['b'] && !defined['c'])
            return false;

        string sideAngles[] = {"aABCbc", "bBACac", "cCABab"};
        for (int i = 0; i < 3; i++)
        {
            string v = sideAngles[i];
            if (defined[v[0]])
            {
                p[v[4]] = p[v[0]] / sin(p[v[1]]) * sin(p[v[2]]);
                p[v[5]] = p[v[0]] / sin(p[v[1]]) * sin(p[v[3]]);
                
                return true;
            }
        }
    }

    string cosines[] = {"abCcAB", "acBbAC", "bcAaBC"};
    for (int i = 0; i < 3; i++)
    {
        string v = cosines[i];
        
        if (defined[v[0]] && defined[v[1]] && defined[v[2]])
        {
            if (p[v[2]] >= PI)
                return false;
                
            p[v[3]] = sqrt(p[v[0]] * p[v[0]] + p[v[1]] * p[v[1]] -
                2 * p[v[0]] * p[v[1]] * cos(p[v[2]]));
            p[v[4]] = acos(p[v[1]], p[v[3]], p[v[0]]);
            p[v[5]] = acos(p[v[0]], p[v[3]], p[v[1]]);
            
            return true;
        }
    }

    string sines[] = { "abABCc", "baBACc", "acACBb", "caCABb", "bcBCAa", "cbCBAa" };
    for (int i = 0; i < 6; i++)
    {
        string v = sines[i];
        if (defined[v[0]] && defined[v[1]] && defined[v[2]])
        {
            if (p[v[2]] >= PI)
                return false;
                
            if (p[v[2]] >= HALF_PI && p[v[0]] <= p[v[1]])
                return false;
                
            double temp = p[v[1]] * sin(p[v[2]]);
            if (p[v[2]] < HALF_PI && p[v[0]] < temp)
                return false;
            
            if (p[v[2]] < HALF_PI && p[v[0]] < p[v[1]] && p[v[0]] > temp)
            {
                multiSolution = true;
                return true;
            }
  
            p[v[3]] = asin(p[v[1]] * sin(p[v[2]]) / p[v[0]]);
            p[v[4]] = PI - p[v[2]] - p[v[3]];
            p[v[5]] = p[v[0]] * sin(p[v[4]]) / sin(p[v[2]]);
                           
            return true;
        }
    }
}

int main(int argc, char *argv[])
{
    int n;
    double temp;
    
    cout.precision(6);
    
    cin >> n;
    while (n--)
    {
        bool valid = true;
        int counter = 0;

        for (int i = 0; i < variable.length(); i++)
        {
            cin >> temp;
            old[variable[i]] = p[variable[i]] = temp;
            
            defined[variable[i]] = false;
            if (temp <= 0 && temp != -1.0)
                valid = false;
            else if (temp > 0)
            {
                defined[variable[i]] = true;
                counter++;
            }
        }
 
        multiSolution = false;
        if (counter <= 2 || !valid || !calculate())
            cout << "Invalid input.\n";
        else if (multiSolution)
            cout << "More than one solution.\n";
        else
        {
            valid = true;
            for (int i = 0; i < variable.length(); i++)
                if (defined[variable[i]] && abs(p[variable[i]] - old[variable[i]]) > EPSILON)
                {
                    cout << "Invalid input.\n";
                    valid = false;
                    break;
                }
            
            if (valid)
            {
                for (int i = 0; i < variable.length(); i++)
                    cout << (i > 0 ? " " : "") << fixed << p[variable[i]];
                cout << "\n";
            }       
        }
    }

    return 0;
}
