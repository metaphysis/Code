// Doing Windows
// UVa ID: 618
// Verdict: Accepted
// Submission Date: 2017-08-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct rectangle
{
    int width, height;
};

rectangle screen, input[4], windows[4];
vector<int> indexer;

int gcd(int a, int b)
{
    if (a < b) swap(a, b);
    return b ? gcd(b, a % b) : a;
}

bool validate()
{
    // type 1
    int scale = 1;
    while (true)
    {
        int width1 = windows[0].width * scale;
        if ((width1 + windows[1].width) > screen.width) break;
        int height1 = windows[0].height * scale;
        if (height1 + windows[2].height > screen.height) break;

        int width2 = screen.width - width1;
        int height3 = screen.height - height1;

        if (width2 % windows[1].width == 0 && height3 % windows[2].height == 0)
        {
            int height2 = windows[1].height * (width2 / windows[1].width);
            int width3 = windows[2].width * (height3 / windows[2].height);
            
            if (height2 < screen.height && width3 < screen.width)
            {
                if (width1 == width3)
                {
                    int width4 = screen.width - width1;
                    int height4 = screen.height - height2;
                    
                    if (windows[3].width * height4 == width4 * windows[3].height) return true;
                }
                if (height1 == height2)
                {
                    int width4 = screen.width - width3;
                    int height4 = screen.height - height2;
                    
                    if (windows[3].width * height4 == width4 * windows[3].height) return true;
                }
            }
        }
        
        scale++;
    }

    int width = 0, height = 0, used = 0;
    
    // type 2
    height = 0;
    for (used = 0; used < 4; used++)
    {
        if (screen.width % windows[used].width != 0) break;
        height += (screen.width / windows[used].width) * windows[used].height;
    }
    if (used == 4 && height == screen.height) return true;

    // type 3
    height = 0;
    for (used = 0; used < 2; used++)
    {
        if (screen.width % windows[used].width != 0) break;
        height += (screen.width / windows[used].width) * windows[used].height;
    }
    if (used == 2 && height < screen.height)
    {
        height = screen.height - height, width = 0;
        for (; used < 4; used++)
        {
            if (height % windows[used].height != 0) break;
            width += (height / windows[used].height) * windows[used].width;
        }
        if (used == 4 && width == screen.width) return true;
    }

    // type 4
    height = 0;
    for (used = 0; used < 1; used++)
    {
        if (screen.width % windows[used].width != 0) break;
        height += (screen.width / windows[used].width) * windows[used].height;
    }
    if (used == 1 && height < screen.height)
    {
        height = screen.height - height, width = 0;
        for (; used < 4; used++)
        {
            if (height % windows[used].height != 0) break;
            width += (height / windows[used].height) * windows[used].width;
        }
        if (used == 4 && width == screen.width) return true;
    }

    // type 5
    height = 0;
    for (used = 0; used < 1; used++)
    {
        if (screen.width % windows[used].width != 0) break;
        height += (screen.width / windows[used].width) * windows[used].height;
    }
    if (used == 1 && height < screen.height)
    {
        height = screen.height - height, width = 0;
        for (; used < 2; used++)
        {
            if (height % windows[used].height != 0) break;
            width += (height / windows[used].height) * windows[used].width;
        }
        if (used == 2 && width < screen.width)
        {
            width = screen.width - width;
            int next_height = 0;
            for (; used < 4; used++)
            {
                if (width % windows[used].width != 0) break;
                next_height += (width / windows[used].width) * windows[used].height;
            }
            if (used == 4 && next_height == height) return true; 
        }
    }

    // type 6
    width = 0;
    for (used = 0; used < 4; used++)
    {
        if (screen.height % windows[used].height != 0) break;
        width += (screen.height / windows[used].height) * windows[used].width;
    }
    if (used == 4 && width == screen.width) return true;

    // type 7
    width = 0;
    for (used = 0; used < 2; used++)
    {
        if (screen.height % windows[used].height != 0) break;
        width += (screen.height / windows[used].height) * windows[used].width;
    }
    if (used == 2 && width < screen.width)
    {
        width = screen.width - width, height = 0;
        for (; used < 4; used++)
        {
            if (width % windows[used].width != 0) break;
            height += (width / windows[used].width) * windows[used].height;
        }
        if (used == 4 && height == screen.height) return true;
    }

    // type 8
    width = 0;
    for (used = 0; used < 1; used++)
    {
        if (screen.height % windows[used].height != 0) break;
        width += (screen.height / windows[used].height) * windows[used].width;
    }
    if (used == 1 && width < screen.width)
    {
        width = screen.width - width, height = 0;
        for (; used < 4; used++)
        {
            if (width % windows[used].width != 0) break;
            height += (width / windows[used].width) * windows[used].height;
        }
        if (used == 4 && height == screen.height) return true;
    }

    // type 9
    width = 0;
    for (used = 0; used < 1; used++)
    {
        if (screen.height % windows[used].height != 0) break;
        width += (screen.height / windows[used].height) * windows[used].width;
    }
    if (used == 1 && width < screen.width)
    {
        width = screen.width - width, height = 0;
        for (; used < 2; used++)
        {
            if (width % windows[used].width != 0) break;
            height += (width / windows[used].width) * windows[used].height;
        }
        if (used == 2 && height < screen.height)
        {
            height = screen.height - height;
            int next_width = 0;
            for (; used < 4; used++)
            {
                if (height % windows[used].height != 0) break;
                next_width += (height / windows[used].height) * windows[used].width;
            }
            if (used == 4 && next_width == width) return true; 
        }
    }
    
    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0;
    while (cin >> screen.width >> screen.height)
    {
        if (screen.width == 0 && screen.height == 0) break;
        
        indexer.clear();
        for (int i = 0; i < 4; i++)
            indexer.push_back(i);
        
        for (int i = 0; i < 4; i++)
        {
            cin >> input[i].width >> input[i].height;
            int divisor = gcd(input[i].width, input[i].height);
            if (divisor > 1)
            {
                input[i].width /= divisor;
                input[i].height /= divisor;
            }
        }

        bool yes = false;
        do
        {
            for (int i = 0; i < 4; i++)
            {
                windows[i].width = input[indexer[i]].width;
                windows[i].height = input[indexer[i]].height;
            }

            yes = validate();
            if (yes) break;
        } while (next_permutation(indexer.begin(), indexer.end()));
        
        cout << "Set " << ++cases << ": ";
        cout << (yes ? "Yes" : "No");
        cout << '\n';
    }
    
	return 0;
}
