const int MAXV = 1010;

vector<int> edges[MAXV];

void hierholzer(int u)
{
    stack<int> path;
    vector<int> circuit;

    int current = u;
    path.push(u);
    while (!path.empty())
    {
        if (edges[current].size())
        {
            path.push(current);
            int next = edges[current].front();
            edges[current].erase(edges[current].begin());
            current = next;
        }
        else
        {
            circuit.push_back(current);
            current = path.top();
            path.pop();
        }
    }
}
