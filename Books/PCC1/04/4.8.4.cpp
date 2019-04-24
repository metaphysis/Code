int partition(int data[], int n, int k)
{
    int left = 0, right = 0;

    for (int i = 0; i < n; i++) right += data[i];
    
    while (left <= right)
    {
        int middle = (left + right) / 2;
        int j = 0, p = 0, sum = 0, ok = 1;

        while (j < n && p <= k)
        {
            if (sum + data[j] <= middle)
            {
                sum += data[j];
                j++;
            }
            else
            {
                sum = 0;
                p++;
            }
        }

        if (sum > 0) p++;

        if (p > k)
            left = middle + 1;
        else
            right = middle - 1;
    }
    
    return left;
}
