// Swamp County Roofs
// UVa ID: 428
// Verdict: Accepted
// Submission Date: 2016-08-04
// UVa Run Time: 0.000s
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
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

const double PI = 2 * acos(0);

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    double total_lot_area = 0, total_roof_area = 0, total_floor_area = 0;
    double lot = 0, base = 0, ridge = 0, distances = 0, angle = 0;
    
    cout << "Roof Area     Floor Area     % Covered\n";
    cout << "---------     ----------     ---------\n";

    string line, block;
    while (true)
    {
        vector<string> datas;
        while (getline(cin, line))
        {
            if (line.length() == 0 && datas.size() % 4 == 1)
                break;

            istringstream iss(line);
            while (iss >> block)
                datas.push_back(block);
        }
        
        if (datas.size() == 0)
            break;

        double roof, floor, lot_area = 0, roof_area = 0, floor_area = 0;
        
        lot_area = stod(datas.front());
        total_lot_area += lot_area;
        lot++;
        
        for (int i = 1; i < datas.size(); i += 4)
        {
            base = stod(datas[i]); ridge = stod(datas[i + 1]);
            distances = stod(datas[i + 2]); angle = stod(datas[i + 3]);

            roof = (base + ridge) * distances / 2;
            floor = roof * cos(angle / 180 * PI);
            
            roof_area += roof;
            floor_area += floor;

            total_roof_area += roof;
            total_floor_area += floor;
        }
        
        cout << fixed << setprecision(2) << setw(9) << right << roof_area;
        cout << setw(15) << right << floor_area;
        cout << setw(13) << right << (floor_area / lot_area * 100);
        cout << "%\n";
    }
    
    cout << '\n';
    cout << "Total surface area of roofs" << setw(12) << right << total_roof_area << '\n';
    cout << "Total area covered by roofs" << setw(12) << right << total_floor_area << '\n';
    cout << "Percentage of total area covered by roofs" << setw(8) << right << (total_floor_area / total_lot_area * 100) << "%\n";
    cout << "Average roof surface area per lot" << setw(16) << right << total_roof_area / lot << '\n';
    cout << "Average floor space covered per lot" << setw(14) << right << total_floor_area / lot << '\n';
    
	return 0;
}
