// Mouse Clicks
// UVa IDs: 142
// Verdict: Accepted
// Submission Date: 2016-01-21
// UVa Run Time: 0.012s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

struct icon
{
    int leftX, topY;
    int label;
    int distance;
    int visible;
};
    
struct region
{
    int leftX, topY, rightX, bottomY;
    char label;
};

// 图标排序比较规则
bool operator<(const icon& a, const icon& b)
{
    if (a.visible == b.visible)
        if (a.distance == b.distance)
            return a.label < b.label;
        else
            return a.distance < b.distance;
    else
        return a.visible > b.visible;
}

int main(int argc, char *argv[])
{
    string line;
    string category;
    int leftX, topY, rightX, bottomY;
    vector < icon > icons;
    vector < region > regions;
    
    int indexI = 1;
    int indexR = 1;
    
    while (getline(cin, line), line != "#")
    {
        istringstream iss(line);
        iss >> category;
        iss >> leftX >> topY;
        
        if (line.find('I') != line.npos)
        {
            icons.push_back((icon) { leftX, topY, indexI++, 0, 0 });
        }
        else if (line.find('R') != line.npos)
        {
            iss >> rightX >> bottomY;
            regions.push_back(
                (region) { leftX, topY, rightX, bottomY, ('A' + indexR++ - 1) });
        }
        else
        {
            // 检查鼠标事件是否落在矩形内
            bool inRegion = false;
            for (int i = regions.size() - 1; i >= 0; i--)
            {
                region r = regions[i];
                if (leftX >= r.leftX && leftX <= r.rightX
                    && topY >= r.topY && topY <= r.bottomY)
                {
                    cout << r.label << endl;
                    inRegion = true;
                    break;
                }
            }
            
            // 落在矩形内，不需处理后续图标
            if (inRegion)
                continue;
            
            // 计算鼠标和图标的距离
            for (int i = 0; i < icons.size(); i++)
                icons[i].distance =
                    pow(icons[i].leftX - leftX, 2) + pow(icons[i].topY - topY, 2);
            
            // 设置图标可见性
            for (int i = 0; i < icons.size(); i++)
            {
                icons[i].visible = 1;
                for (int j = 0; j < regions.size(); j++)
                {
                    region r = regions[j];
                    if (icons[i].leftX >= r.leftX && icons[i].leftX <= r.rightX
                        && icons[i].topY >= r.topY && icons[i].topY <= r.bottomY)
                    {
                        icons[i].visible = 0;
                        break;
                    }
                }
            }
            
            // 排序
            sort(icons.begin(), icons.end());
            
            // 按要求输出图标序号
            for (int i = 0; i < icons.size(); i++)
                if (icons[i].distance == icons[0].distance && icons[i].visible)
                    cout << setw(3) << right << icons[i].label;
                else
                    break;
                    
            cout << endl;
        }
    }
    
	return 0;
}
