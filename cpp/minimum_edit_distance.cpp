/*

Weighted Min Edit Distance
•  Initialization
    D(0,0) = 0
    D(i,0) = D(i-1,0) + del[x(i)]; 1 < i ≤ N
    D(0,j) = D(0,j-1) + ins[y(j)]; 1 < j ≤ M
•  Recurrence relation:

            / D(i-1,j) + del[x(i)]
D(i,j)= min - D(i,j-1) + ins[y(j)]
            \ D(i-1,j-1) + sub[x(i),y(j)]

•  Termination
D(N,M) is distance

*/
// minimum edit distance. Assume substitution, insertion and deletion all have
// a cost of 1. 

int EditDistance(string word1, string word2)
{
    int i, j, l1, l2, m;
    l1 = word1.length();
    l2 = word2.length();
    vector< vector<int> > t(l1 + 1, vector<int>(l2 + 1));
 
    for (i = 0; i <= l1; i++)
        t[i][0] = i;
    for (i = 1; i <= l2; i++)
        t[0][i] = i;
 
    for (i = 1; i <= l1; i++)
    {
        for (j = 1; j <= l2; j++)
        {
            m = min(t[i-1][j], t[i][j-1]) + 1;
            t[i][j] = min(m, t[i-1][j-1] + (word1[i-1] == word2[j-1] ? 0 : 1));
        }
    }
    return t[l1][l2];
}