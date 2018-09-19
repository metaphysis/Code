#include <bits/stdc++.h>

using namespace std;

class item
{
public:
    int value, weight, id;
    char detail[100];

    item(int v = 0, int w = 0, char *s = NULL, int i = 0)
    {
        value = v;
        weight = w;
        memset(detail, 0, sizeof(detail));
        if (s)
            strcpy(detail, s);
        id = i;
    }

    bool operator() (item * a, item * b)
    {
        if (!a)
            return false;
        if (!b)
            return true;
        if (a->weight != b->weight)
            return a->weight < b->weight;
        if (a->value != b->value)
            return a->value > b->value;
        return strcmp(a->detail, b->detail) < 0;
    }
} obj;

class dp
{
public:
    int allValue, allWeight, evidence[100];

    dp()
    {
        allValue = allWeight = 0;
        memset(evidence, 0, sizeof(evidence));
    }

    bool operator<(const dp &cmp) const
    {
        return allValue < cmp.allValue;
    }

    dp operator+(item &add)
    {
        dp tmp = *this;
        tmp.allValue += add.value;
        tmp.allWeight += add.weight;
        for (int i = 0; ; ++i)
            if (!tmp.evidence[i])
            {
                tmp.evidence[i] = add.id;
                break;
            }
        return tmp;
    }
} matrix[101][241];

int main()
{
    int t, time, val, weight;
    char evi[100];

    for (scanf("%d", &t); t--;)
    {
        int qnt = 0, size = 0;
        item *all[101] = { NULL };
        scanf("%d\n", &time);
        while (cin.getline(evi, 100, '\n') && *evi)
        {
            sscanf(evi, "%d %d", &val, &weight);
            all[++size] = new item(val, weight, strchr(strchr(evi, ' ') + 1, ' ') + 1, ++qnt);
        }
        sort(all + 1, all + 1 + size, obj);
        for (int i = 1; i <= qnt; ++i)
            all[i]->id = i;
        for (int i = 1; i <= qnt; ++i)
            for (int j = 1; j <= time; ++j)
                if (all[i]->weight > j)
                    matrix[i][j] = matrix[i - 1][j];
                else
                    matrix[i][j] =
                        max(matrix[i - 1][j], matrix[i - 1][j - all[i]->weight] + *all[i]);
        if (matrix[qnt][time].evidence[0])
        {
            printf("Score  Time  Description\n-----  ----  -----------\n");
            for (int i = 0; matrix[qnt][time].evidence[i]; ++i)
                printf("%3d    %3d   %s\n", all[matrix[qnt][time].evidence[i]]->value,
                    all[matrix[qnt][time].evidence[i]]->weight,
                    all[matrix[qnt][time].evidence[i]]->detail);
            printf("\nTotal score: %d points\n Total time: %d hours", matrix[qnt][time].allValue,
                matrix[qnt][time].allWeight);
        }
        else
            printf("There is not enough time to present any evidence. Drop the charges.");
        puts(t ? "\n" : "");
    }

    return 0;
}
