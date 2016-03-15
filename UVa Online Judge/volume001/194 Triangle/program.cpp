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

const double EPSILON = 10E-6;
const double PI = 3.141592653589793;

map < char, double > paras;
map < char, bool > defined;
string variable = "aAbBcC";

bool calculate()
{
    // sum of length of two sides is bigger than length of third side
    string sides[] = {"abc", "acb", "bca"};
    for (int i = 0; i <= 2; i++)
    {
        char x = sides[i][0], y = sides[i][1], z = sides[i][2];
        if (defined[x] && defined[y] && defined[z])
        {
            if ((paras[x] + paras[y] - paras[z]) <= EPSILON )
                return false;
        }
    }
    
    // two angles defined
    string angles[] = {"ABC", "ACB", "BCA"};
    for (int i = 0; i <= 2; i++)
    {
        char x = angles[i][0], y = angles[i][1], z = angles[i][2];
        if (defined[x] && defined[y] && !defined[z])
        {
            if ((paras[x] + paras[y] - PI) >= EPSILON )
                return false;
            
            paras[z] = PI - paras[x] - paras[y];
            defined[z] = true;
            break;
        }
    }

    // three sides defined
    if (defined['a'] && define['b'] && defined['c'])
    {
        // Law of Cosines
        double temp = (paras['b'] * paras['b'] + paras['c'] + paras['c']
            - paras['a'] * paras['a']) / (2 * paras['b'] * paras['c']);
        if (fabs(temp - 1.0) <= EPSILON)
            return false;
            
        double temp = acos(temp);
        if (defined['A'] && fabs(temp - paras['A']) >= EPSILON)
            return false;
        else
            paras['A'] = temp;
    }
    
    // three angles defined
    if (defined['A'] && defined['B'] && defined['C'])
    {
        if (fabs(paras['A'] + paras['B'] + paras['C'] - PI) >= EPSILON )
            return false;
        
        if (!defined['a'] && !defined['b'] && !defined['c'])
            return false;
        
        string sideAngles[] = {"aABCbc", "bBACac", "cCABab"};
        for (int i = 0; i <= 2; i++)
        {
            if (defined[sideAngles[i][0]] && defined[sideAngles[i][1]] && defined[sideAngles[i][2]])
            {
                double temp = paras[sideAngles[i][0]] / sin(paras[sideAngles[i][1]]) * sin(paras[sideAngles[i][2]]);
                if (defined[sideAngles[i][4]] && fabs(temp - paras[sideAngles[i][4]]) >= EPSILON)
                    return false;
                else
                    paras[sideAngles[i][4]] = temp;
                    
                temp = paras[sideAngles[i][0]] / sin(paras[sideAngles[i][1]]) * sin(paras[sideAngles[i][3]]);
                if (defined[sideAngles[i][5]] && fabs(temp - paras[sideAngles[i][5]]) >= EPSILON)
                    return false;
                else
                    paras[sideAngles[i][5]] = temp;
                    
                for (int i = 0; i < variable.length(); i++)
                    cout << (i > 0 ? " " : "") << fixed << setprecision(8) << paras[variable[i]];
                
                cout << "\n";
                return true;
            }
        }
        
        return false;
    }
        
    // calculate by Law of Cosines
    string cosines[] = {"abCcAB", "acBbAC", "bcAaBC"};
    for (int i = 0; i <= 2; i++)
    {
        if (defined[cosines[i][0]] && defined[cosines[i][1]] && defined[cosines[i][2]])
        {
            double d[6];
            for (int j = 0; j < cosines[i].length(); j++)
                d[j] = paras[cosines[i][j]];
            
            if (d[2] - PI >= EPSILON) 
                return false;
            
            // Law of Cosines
            double temp = sqrt(d[0] * d[0] + d[1] * d[1] - 2 * d[0] * d[1] * cos(d[2]));
            if (defined[cosines[i][3]] && fabs(temp - d[3]) >= EPSILON)
                return false;
            else
                paras[cosines[i][3]] = temp;
            
            // Law fo Sines
            temp = asin(paras[cosines[i][0]] / paras[cosines[i][3]] * sin(paras[cosines[i][2]]));
            if (defined[cosines[i][4]] && fabs(temp - d[4]) >= EPSILON)
                return false;
            else
                paras[cosines[i][4]] = temp;
                
            // Law fo Sines
            temp = asin(paras[cosines[i][1]] / paras[cosines[i][3]] * sin(paras[cosines[i][2]]));
            if (defined[cosines[i][5]] && fabs(temp - d[5]) >= EPSILON)
                return false;
            else
                paras[cosines[i][5]] = temp;
                
            for (int i = 0; i < variable.length(); i++)
                cout << (i > 0 ? " " : "") << fixed << setprecision(8) << paras[variable[i]];
            
            cout << "\n";
            return true;
        }
    }
    
    // calculate by Law of Sines
    string sines[] = {"abABCc", "baBACc", "acACBb", "caCABb", "bcBCAa", "cbCBAa"};
    for (int i = 0; i <= 2; i++)
    {
        double d[6];
        for (int j = 0; j < sines[i].length(); j++)
            d[j] = paras[sines[i][j]];
            
        if (defined[sines[i][0]] && defined[sines[i][1]] && defined[sines[i][2]])
        {
            // Law fo Sines
            double temp = asin(paras[sines[i][1]] / paras[sines[i][0]] * sin(paras[sines[i][2]]));
            if (defined[sines[i][3]] && fabs(temp - d[3]) >= EPSILON)
                return false;
            else
                paras[sines[i][3]] = temp;
            
            // PI
            temp = PI - paras[sines[i][2]] - paras[sines[i][3]];
            if (defined[sines[i][4]] && fabs(temp - d[4]) >= EPSILON)
                return false;
            else
                paras[sines[i][4]] = temp;
                
            // Law fo Sines
            temp = paras[sines[i][0]] / sin(paras[sines[i][2]]) * sin(paras[sines[i][4]]);
            if (defined[sines[i][5]] && fabs(temp - d[5]) >= EPSILON)
                return false;
            else
                paras[sines[i][5]] = temp;
                
            for (int i = 0; i < variable.length(); i++)
                cout << (i > 0 ? " " : "") << fixed << setprecision(8) << paras[variable[i]];
            
            cout << "\n";    
            return true;
        }
    }
        
    return false;
}

int main(int argc, char *argcosines[])
{
    int n;
    cin >> n;
    
    while (n--)
    {
        bool isValid = true;
        for (int i = 0; i < variable.length(); i++)
        {
            char c = variable[i];
            
            double temp;
            cin >> temp;
            
            paras[c] = temp;
            
            if (temp > 0)
                defined[c] = true;
            else
            {
                if ((fabs(temp) - 1.0) <= EPSILON)
                    defined[c] = false;
                else
                    isValid = false;
            }
        }
        
        if (isValid == false)
        {
            cout << "Invalid input.\n";
            continue;
        }
        
        if(calculate() == false)
            cout << "Invalid input.\n";
    }
    
	return 0;
}
