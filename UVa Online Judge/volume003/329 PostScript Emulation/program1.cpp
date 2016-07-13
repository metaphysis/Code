// PostScript Emulation
// UVa IDs: 329
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

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
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

const double PI = 2.0 * acos(0);
double M[3][3] = { 1, 0, 0, 0, 1, 0, 0, 0, 1}, R[3][3], T[3][3], S[3][3];
double last_x = 0, last_y, current_x = 0, current_y = 0, new_x = 0, new_y = 0;
double rotated_angle, translatex, translatey, scalex, scaley;

void multiplication(double A[3][3], double B[3][3])
{
    double temp[3][3] = {0.0};
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            temp[i][j] = 0.0;
    
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
                temp[i][j] += A[i][k] * B[k][j];
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    cout << "newpath\n0 setlinewidth\n";
    
    string line, parameter;
    while (getline(cin, line), line != "*")
    {
        vector<string> parameters;
        istringstream iss(line);
        while (iss >> parameter)
            parameters.push_back(parameter);

        if (parameters.back() == "rotate")
        {
            rotated_angle += stod(parameters[0]);
        }
        else if (parameters.back() == "translate")
        {
            double translate[3][3] = {1, 0, 0, 0, 1, 0, stod(parameters[0]), stod(parameters[1]), 1};
            multiplication(translate);
        }
        else if (parameters.back() == "scale")
        {
            scalex *= stod(parameters[0]), scaley *= stod(parameters[1]);
        }
        else if (parameters.back() == "moveto" || parameters.back() == "lineto")
        {
            new_x = stod(parameters[0]);
            new_y = stod(parameters[1]);
            
            current_x = matrix[0][0] * new_x + matrix[1][0] * new_y + matrix[2][0];
            current_y = matrix[0][1] * new_x + matrix[1][1] * new_y + matrix[2][1];
            
            cout << fixed << setprecision(6) << current_x << " ";
            cout << fixed << setprecision(6) << current_y << " ";
            cout << parameters.back() << endl;
        }
        else if (parameters.back() == "rmoveto" || parameters.back() == "rlineto")
        {
            new_x += stod(parameters[0]);
            new_y += stod(parameters[1]);
            
            last_x = current_x;
            last_y = current_y;
            
            current_x = matrix[0][0] * new_x + matrix[1][0] * new_y + matrix[2][0];
            current_y = matrix[0][1] * new_x + matrix[1][1] * new_y + matrix[2][1];
            
            cout << fixed << setprecision(6) << current_x - last_x << " ";
            cout << fixed << setprecision(6) << current_y - last_y << " ";
            cout << parameters.back() << endl;
        }
    }
    
    cout << "stroke\nshowpage\n";
    
	return 0;
}
