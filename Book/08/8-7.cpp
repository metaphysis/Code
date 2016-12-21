// 八皇后问题构建候选集的过程。
constructCandidates(int a[], int k, int n, int c[], int *ncandidates)
{
    *ncandidates = 0;
    for (int i = 1; i <= n; i++)
    {
        bool legalMove = true;

        // 对于放置象来说，需要考虑除已有象的对角线外的每一个位置，
        // 因为不存在像放置皇后时一行或一列只能放置一个这样的限制条件。
        for (int j = 1; j < k; j++)
        {
            if (abs((k) - j) == abs(i - a[j]))
                legalMove = false;

            // 对于放置象来说，并不需要检测来自行或者列的威胁，只需检	
            // 测对角线上的威胁。
            if (i == a[j])
                legalMove = false;
        }

        if (legalMove)
        {
            c[*ncandidates] = i;
            *ncandidates = *ncandidates + 1;
        }
    }
}
