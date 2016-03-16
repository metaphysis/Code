// Triangle
// UVa IDs: 194
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <iomanip>
#include <map>
#include <cmath>

using namespace std;

const double EPSILON = 1E-7;
const double PI = 3.14159265358979323846;
const double HALF_PI = PI / 2.0;

map < char, double > paras;
map < char, bool > defined;
string variable = "aAbBcC";
bool multiSolution = false;

double acos(double a, double b, double c)
{
    return acos((a * a + b * b - c * c) / (2 * a * b));
}

bool calculate()
{
    if (defined['a'] && defined['b'] && defined['c'])
    {
        if (paras['a'] + paras['b'] <= paras['c'] ||
            paras['b'] + paras['c'] <= paras['a'] ||
            paras['a'] + paras['c'] <= paras['b'])
            return false;

        double temp = acos(paras['b'], paras['c'], paras['a']);
        if (defined['A'] == false)
            paras['A'] = temp;
        else if (abs(temp - paras['A']) > EPSILON)
            return false;
        
        temp = acos(paras['a'], paras['c'], paras['b']);
        if (defined['B'] == false)
            paras['B'] = temp;
        else if (abs(temp - paras['B']) > EPSILON)
            return false;

        temp = acos(paras['a'], paras['b'], paras['c']);
        
        if (defined['C'] == false)
            paras['C'] = temp;
        else if (abs(temp - paras['C']) > EPSILON)
            return false;

        return true;
    }
    
    if (defined['A'] && defined['B'] && defined['C'])
    {
        if (abs(paras['A'] + paras['B'] + paras['C'] - PI) > 1E-4)
            return false;
    }
    else
    {
        string angles[] = {"ABC", "ACB", "BCA"};
        for (int i = 0; i < 3; i++)
        {
            string v = angles[i];
            
            if (defined[v[0]] && paras[v[0]] >= PI ||
                defined[v[1]] && paras[v[1]] >= PI ||
                defined[v[2]] && paras[v[2]] >= PI)
                return false;
                               
            if (defined[v[0]] && defined[v[1]] && !defined[v[2]])
            {
                if (paras[v[0]] + paras[v[1]] >= PI)
                    return false;
                    
                paras[v[2]] = PI - paras[v[0]] - paras[v[1]];
                defined[v[2]] = true;
                break;
            }
        }
    }
    

    if (defined['A'] && defined['B'] && defined['C'])
    {
        if (!defined['a'] && !defined['b'] && !defined['c'])
            return false;

        string sideAngles[] = {"aABCbc", "bBACac", "cCABab"};
        for (int i = 0; i < 3; i++)
        {
            string v = sideAngles[i];
            if (defined[v[0]])
            {
                double temp = paras[v[0]] / sin(paras[v[1]]) * sin(paras[v[2]]);
                
                if (defined[v[4]] == false)
                    paras[v[4]] = temp;
                else if (abs(temp - paras[v[4]]) > EPSILON)
                    return false;

                temp = paras[v[0]] / sin(paras[v[1]]) * sin(paras[v[3]]);
                if (defined[v[5]] == false)
                    paras[v[5]] = temp;
                else if (abs(temp - paras[v[5]]) > EPSILON)
                    return false;

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
            double temp = sqrt(paras[v[0]] * paras[v[0]] +
                paras[v[1]] * paras[v[1]] - 2 * paras[v[0]] * paras[v[1]] * cos(paras[v[2]]));
            
            if (defined[v[3]] == false)
                paras[v[3]] = temp;
            else if (abs(temp - paras[v[3]]) > EPSILON)
                return false;

            temp = asin(paras[v[0]] / paras[v[3]] * sin(paras[v[2]]));
            if (defined[v[4]] == false)
                paras[v[4]] = temp;
            else if (abs(temp - paras[v[4]]) > EPSILON)
                return false;
                
            temp = PI - paras[v[2]] - paras[v[4]];
            if (defined[v[5]] == false)
                paras[v[5]] = temp;
            else if (abs(temp - paras[v[5]]) > EPSILON)
                return false;
            
            return true;
        }
    }

    string sines[] = { "abABCc", "baBACc", "acACBb", "caCABb", "bcBCAa", "cbCBAa" };
    for (int i = 0; i < 6; i++)
    {
        string v = sines[i];
        if (defined[v[0]] && defined[v[1]] && defined[v[2]])
        {
            if (paras[v[2]] >= HALF_PI && paras[v[0]] < paras[v[1]])
                return false;
                
            if (paras[v[2]] < HALF_PI && paras[v[0]] < (paras[v[1]] * sin(paras[v[2]])))
                return false;
            
            if (paras[v[2]] < HALF_PI &&
                paras[v[0]] < paras[v[1]] &&
                paras[v[0]] > (paras[v[1]] * sin(paras[v[2]])))
            {
                multiSolution = true;
                return true;
            }
  
            paras[v[3]] = asin(paras[v[1]] / paras[v[0]] * sin(paras[v[2]]));
            paras[v[4]] = PI - paras[v[2]] - paras[v[3]];
            paras[v[5]] = paras[v[0]] / sin(paras[v[2]]) * sin(paras[v[4]]);
                           
            return true;
        }
    }
    
    return false;
}

int main(int argc, char *argv[])
{
    int n;
    double temp;
    
    cin >> n;
    while (n--)
    {
        bool valid = true;
        int counter = 0;
        multiSolution = false;
        
        for (int i = 0; i < variable.length(); i++)
        {
            cin >> temp;
            paras[variable[i]] = temp;
            if (temp > 0.0)
            {
                defined[variable[i]] = true;
                counter++;
            }
            else if (temp == -1.0)
            {
                defined[variable[i]] = false;
            }
            else
            {
                valid = false;
            }
        }

        if (counter <= 2)
            valid = false;
            
        if (valid == false || calculate() == false)
        {
            cout << "Invalid input.\n";
        }
        else if (multiSolution == true)
        {
            cout << "More than one solution.\n";
        }
        else
        {
            for (int i = 0; i < variable.length(); i++)
                cout << (i > 0 ? " " : "") << fixed << setprecision(6) << paras[variable[i]];
            cout << "\n";
        }
    }

    return 0;
}
