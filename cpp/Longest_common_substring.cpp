// Longest common substring using suffix array.
struct CompStruct {
    int nr[2];
    int p;
};

bool comp(const CompStruct &a, const CompStruct &b){
    if (a.nr[0] == b.nr[0])
        return a.nr[1] < b.nr[1];
    return a.nr[0] < b.nr[0];
}

vector<int> getSA(const string &str){
    int n = (int) str.size();
    vector<vector<int>>daArray(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        daArray[0][i] = str[i] - 'a';
    }
    
    int cnt = 1, stp = 1;
    vector<CompStruct> compArray(n);
    for (; cnt <= str.size(); ++stp, cnt <<= 1) {
        for (int i = 0; i < n; ++i) {
            compArray[i].nr[0] = daArray[stp - 1][i];
            compArray[i].nr[1] = i + cnt < n ? daArray[stp - 1][i + cnt] : -1;
            compArray[i].p = i;
        }
        sort(compArray.begin(), compArray.end(), comp);
        for (int i = 0; i < n; ++i) {
            if (i > 0 && compArray[i].nr[0] == compArray[i - 1].nr[0] &&
                compArray[i].nr[1] == compArray[i - 1].nr[1]){
                daArray[stp][compArray[i].p] = daArray[stp][compArray[i - 1].p];
            }
            else
                daArray[stp][compArray[i].p] = i;
        }
    }
    --stp;
    vector<int> sa(n);
    for (int i = 0; i < n; ++i) {
        sa[daArray[stp][i]] = i;
    }
    return sa;
}

vector<int> getHeights(const vector<int> &sa, const string &str){
    int n = (int)str.size();
    vector<int> rank(n), heights(n);
    for (int i = 0; i < n; ++i) {
        rank[sa[i]] = i;
    }
    
    for (int i = 0, k = 0; i < n; ++i) {
        k ? k-- : 0;
        int j = sa[rank[i] - 1];
        while (str[i + k] == str[j + k]) {
            ++k;
        }
        heights[rank[i]] = k;
    }
    
    return heights;
}

string longestCommonSubstring(const string &str1, const string &str2){
    
    if (str1.empty() || str2.empty())
        return "";
    
    string str = str1 + char(0) + str2;
    auto sa = getSA(str);
    auto heights = getHeights(sa, str);
    
    int cur_max = INT_MIN;
    int location;
    
    // Find biggest element in heights where i and i - 1 are in different strings.
    for (int i = 1; i < heights.size(); ++i) {
        
        if (heights[i] > cur_max){
            if ((sa[i] < str1.size() &&  sa[i - 1] > str1.size()) ||
                (sa[i - 1] < str1.size() &&  sa[i] > str1.size())){
                cur_max = heights[i];
                location = sa[i];
            }
            else
                continue;
        }
    }
    return str.substr(location, cur_max);
}