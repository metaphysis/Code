struct rectangle { int height, left; };
int m, n, matrix[110][110];

int getMaxArea()
{
    int area = 0;
    stack<rectangle> s;
    for (int i = 0; i < m; i++) {
        // 在每行末尾添加一个高度为0的直方图，保证结果的正确性。
        matrix[i][n] = 0;
        for (int j = 0; j <= n; j++) {
            rectangle rect = rectangle{matrix[i][j], j};
            if (s.empty() || s.top().height < rect.height) s.push(rect);
            else {
                if (s.top().height > rect.height) {
                    int last = j;
                    while (!s.empty() && s.top().height >= rect.height) {
                        rectangle previous = s.top(); s.pop();
                        area = max(area, previous.height * (j - previous.left));
                        last = previous.left;
                    }
                    rect.left = last;
                    s.push(rect);
                }
            }
        }
    }
    return area;
}
