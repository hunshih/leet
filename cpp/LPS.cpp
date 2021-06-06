// Find the longest palindrome subsequence

// Using DP. Another way to do this is to revert the string and find the longest
// common subsequence of both strings.
int longest_palindrome_subsequence(const string &str){
    int n = int(str.size());
    vector<vector<int>> dp(n, vector<int> (n, 0));
    for (int i = 0; i < str.size(); ++i){
        dp[i][i] = 1;
    }
    
    for (int gap = 1; gap < str.size(); ++gap){
        for (int i = 0, j = gap; j < str.size(); ++i, ++j){
            if (str[i] == str[j]){
                if (i + 1 == j)
                    dp[i][j] = 2;
                else
                    dp[i][j] = dp[i + 1][j - 1] + 2;
            }
            else
                dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
        }
    }
    return dp[0][str.size() - 1];
}