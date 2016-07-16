// PostScript Emulation
// UVa ID: 329
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
double matrix[3][3] = { 1, 0, 0, 0, 1, 0, 0, 0, 1};
double last_x = 0, last_y, current_x = 0, current_y = 0, new_x = 0, new_y = 0;
double rotated_angle, translatex, translatey, scalex, scaley;

void display(double number[3][3])
{
    cout << "CTM start: ---------------------------------" << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            cout << setw(10) << right << number[i][j];
        cout << endl;
    }
    cout << "CTM end: ---------------------------------" << endl;
}

void multiplication(double transformation[3][3])
{
    double temp[3][3] = { 0.0 };    
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
            {
                temp[i][j] += transformation[i][k] * matrix[k][j];
                if (fabs(temp[i][j]) == 0.0)
                    temp[i][j] = 0.0;
            }

    memcpy(matrix, temp, sizeof(temp));
}

void getInserse()
{
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

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
            double radian = stod(parameters[0]) * PI / 180.0;
            double rotate[3][3] = {cos(radian), sin(radian), 0, -sin(radian), cos(radian), 0, 0, 0, 1};
            multiplication(rotate);
        }
        else if (parameters.back() == "translate")
        {
            double translate[3][3] = {1, 0, 0, 0, 1, 0, -stod(parameters[0]), -stod(parameters[1]), 1};
            multiplication(translate);
        }
        else if (parameters.back() == "scale")
        {
            double scale[3][3] = {stod(parameters[0]), 0, 0, 0, stod(parameters[1]), 0, 0, 0, 1};
            multiplication(scale);
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
            double offset_x = stod(parameters[0]);
            double offset_y = stod(parameters[1]);
            
            new_x = matrix[0][0] * offset_x + matrix[1][0] * offset_y + matrix[2][0];
            new_y = matrix[0][1] * offset_x + matrix[1][1] * offset_y + matrix[2][1];
            
            //last_x = current_x;
            //last_y = current_y;
            
            current_x += new_x;
            current_y += new_x;
            
            cout << fixed << setprecision(6) << new_x << " ";
            cout << fixed << setprecision(6) << new_y << " ";
            
            cout << parameters.back() << endl;
        }
    }
    
    cout << "stroke\nshowpage\n";
    
	return 0;
}
