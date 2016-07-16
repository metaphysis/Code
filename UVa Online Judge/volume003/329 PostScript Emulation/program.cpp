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

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    cout << "newpath\n0 setlinewidth\n";
    
    string line, parameter;
    double last_x = 0, last_y = 0, current_x = 0, current_y = 0;
    double new_x = 0, new_y = 0;
    double tx = 0, ty = 0, total_angle = 0, scalex = 1, scaley = 1;
    while (getline(cin, line), line != "*")
    {
        vector<string> parameters;
        istringstream iss(line);
        while (iss >> parameter)
            parameters.push_back(parameter);

        if (parameters.back() == "rotate")
        {
            double rotate_angle = stod(parameters[0]);
            double radian = rotate_angle * PI / 180.0;

            double last_new_x = new_x, last_new_y = new_y;
            new_x = last_new_x * cos(radian) + last_new_y * sin(radian);
            new_y = -last_new_x * sin(radian) + last_new_y * cos(radian);

            total_angle += rotate_angle;
            
            //cout << "after rotate " << rotate_angle << " new_x = " << new_x << " new_y = " << new_y << endl;
        }
        else if (parameters.back() == "translate")
        {
            double old_tx = stod(parameters[0]) * scalex;
            double old_ty = stod(parameters[1]) * scaley;

            double radian = total_angle * PI / 180.0;
            tx = old_tx * cos(radian) - old_ty * sin(radian) + tx;
            ty = old_tx * sin(radian) + old_ty * cos(radian) + ty;
            
            new_x -= old_tx;
            new_y -= old_ty;
        }
        else if (parameters.back() == "scale")
        {
            scalex *= stod(parameters[0]);
            scaley *= stod(parameters[1]);
            
            //cout << "scalex = " << scalex << " parameters[0] = " << parameters[0] << " stod(parameters[0]) = " << stod(parameters[0]);
            //cout << " scalex *= stod(parameters[0]) = " << scalex << endl;
            //cout << "scaley = " << scaley << " parameters[1] = " << parameters[1] << " stod(parameters[1]) = " << stod(parameters[1]);
            //cout << " scaley *= stod(parameters[1]) = " << scaley << endl;
        }
        else if (parameters.back() == "moveto" || parameters.back() == "lineto")
        {
            double radian = total_angle * PI / 180.0;
            
            new_x = stod(parameters[0]);
            new_y = stod(parameters[1]);
            
            //cout << "new_x = " << new_x << " new_y = " << new_y << endl;

            current_x = (new_x * cos(radian) - new_y * sin(radian)) * scalex + tx;
            current_y = (new_x * sin(radian) + new_y * cos(radian)) * scaley + ty;
            
            //cout << "current_x = " << current_x << " current_y = " << current_y << endl;
            
            cout << fixed << setprecision(6) << current_x << " ";
            cout << fixed << setprecision(6) << current_y << " ";
            cout << parameters.back() << endl;
        }
        else if (parameters.back() == "rmoveto" || parameters.back() == "rlineto")
        {
            //cout << "scalex = " << scalex << " scaley = " << scaley << endl;
            //cout << "offset_x = " << stod(parameters[0]) * scalex << " offset_y = " << stod(parameters[1]) * scaley << endl;
            
            new_x += stod(parameters[0]) * scalex;
            new_y += stod(parameters[1]) * scaley;
            
            //cout << "new_x = " << new_x << " new_y = " << new_y << endl;
            
            double radian = total_angle * PI / 180.0;

            last_x = current_x;
            last_y = current_y;
            
            current_x = new_x * cos(radian) - new_y * sin(radian) + tx;
            current_y = new_x * sin(radian) + new_y * cos(radian) + ty;

            //cout << "current_x = " << current_x << " current_y = " << current_y << endl;

            cout << fixed << setprecision(6) << current_x - last_x << " ";
            cout << fixed << setprecision(6) << current_y - last_y << " ";
            cout << parameters.back() << endl;
        }
    }
    
    cout << "stroke\nshowpage\n";
    
	return 0;
}
