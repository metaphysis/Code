// Gears on a Board
// UVa ID: 407
// Verdict: Accepted
// Submission Date: 2016-08-06
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double epsilon = 1e-6;

struct gear
{
    int index;
    double x, y, gir, gor;
    bool is_rotate_left;
    double velocity;
};

struct adjacent
{
    int index;
    bool ir_touched, or_touched;
};

int cases = 0, ng;
vector<gear> gears;
vector<vector<adjacent>> edges;

void run()
{
    cout << "Simulation #" << ++cases << '\n';
    
    edges.assign(ng, vector<adjacent>());
        
    for (int i = 0; i < ng; i++)
        for (int j = i + 1; j < ng; j++)
        {
            adjacent edge;
            edge.index = j, edge.ir_touched = false, edge.or_touched = false;

            double d = sqrt(pow(gears[i].x - gears[j].x, 2) + pow(gears[i].y - gears[j].y, 2));
            
            if (d < gears[i].gir + gears[j].gir - epsilon ||
                d < gears[i].gor + gears[j].gor - epsilon)
            {
                cout << "Error -- Overlapping Gears\n\n";
                return;
            }
            
            if (fabs(d - gears[i].gir - gears[j].gir) < epsilon)
                edge.ir_touched = true;
            
            if (fabs(d - gears[i].gor - gears[j].gor) < epsilon)
                edge.or_touched = true;
            
            if (edge.ir_touched || edge.or_touched)
            {
                edges[i].push_back(edge);
                edge.index = i;
                edges[j].push_back(edge);
            }
        }
        
    vector<bool> visited(ng, false);
    
    queue<int> unvisited;
    unvisited.push(0);
    visited[0] = true;
    
    while (unvisited.empty() == false)
    {
        int current = unvisited.front();
        unvisited.pop();
        
        bool is_rotate_left = !gears[current].is_rotate_left;

        for (auto edge : edges[current])
        {
            double final_velocity, ir_velocity = -1.0, or_velocity = -1.0;
            if (edge.ir_touched)
            {
                ir_velocity = gears[current].gir / gears[edge.index].gir * gears[current].velocity;
                final_velocity = ir_velocity;
            }

            if (edge.or_touched)
            {
                or_velocity = gears[current].gor / gears[edge.index].gor * gears[current].velocity;
                final_velocity = or_velocity;
            }
            
            if (ir_velocity > 0 && or_velocity > 0 && fabs(ir_velocity - or_velocity) > epsilon)
            {
                cout << "Error -- Conflicting Gear Rotation\n\n";
                return;
            }
            
            if (visited[edge.index] == false)
            {
                gears[edge.index].is_rotate_left = is_rotate_left;
                gears[edge.index].velocity = final_velocity;
                visited[edge.index] = true;
                unvisited.push(edge.index);
            }
            else
            {
                if (gears[edge.index].is_rotate_left != is_rotate_left ||
                    fabs(gears[edge.index].velocity - final_velocity) > epsilon)
                {
                    cout << "Error -- Conflicting Gear Rotation\n\n";
                    return;
                }
            }
        }
    }
    
    for (int i = 1; i < ng; i++)
    {
        cout << ' ' << i << ": ";
        
        if (fabs(gears[i].velocity) < epsilon)
        {
            cout << "Warning -- Idle Gear\n";
            continue;
        }

        cout << (gears[i].is_rotate_left ? 'L' : 'R');
        cout << ' ' << fixed << setprecision(2) << gears[i].velocity;
        cout << '\n';
    }
    cout << '\n';
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    double x, y, gir, gor, velocity;
    gear motor;
    
    while (cin >> motor.x >> motor.y >> motor.gir >> motor.gor >> motor.velocity >> ng)
    {
        gears.clear();

        motor.is_rotate_left = motor.velocity < 0;
        motor.velocity = fabs(motor.velocity);
        gears.push_back(motor);

        for (int i = 1; i <= ng; i++)
        {
            cin >> x >> y >> gir >> gor;
            gears.push_back((gear){i, x, y, gir, gor, false, 0.0});
        }
        
        ng++;
        
        run();
    }
    
	return 0;
}
