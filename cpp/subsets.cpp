


// Print all subsets of a vector.
void add_subs(vector<vector<int>> &old_subs, int cur_num){
    int old_size = int(old_subs.size());
    old_subs.push_back(vector<int>{cur_num});
    for (int i = 0; i < old_size; ++i) {
        old_subs.push_back(old_subs[i]);
        old_subs[old_subs.size() - 1].push_back(cur_num);
    }
}

void print_all_subsets(const vector<int> &array){
    vector<vector<int>> all_subs;
    for (int i = 0; i < array.size(); ++i) {
        add_subs(all_subs, array[i]);
    }
    
    for (int i = 0; i < all_subs.size(); ++i) {
        for (int j = 0; j < all_subs[i].size(); ++j) {
            cout << all_subs[i][j] << " ";
        }
        cout << endl;
    }
}

// Implementation without duplicates
// input: 1, 2, 2
// output:
/*
 
 1
 1 2
 1 2 2
 2
 2 2
 
 */

void sub(vector<int> &s, int begin, vector<int> &path,
         vector<vector<int> > &result) {
    result.push_back(path);
    
    for (int i = begin; i < s.size(); ++i) {
        if (i != begin && s[i] == s[i - 1]) continue;
        
        path.push_back(s[i]);
        sub(s, i + 1, path, result);
        path.pop_back();
    }
}


vector<vector<int> > subsetsWithDup(vector<int> &S) {
    vector<int> path;
    vector<vector<int> > result;
    
    sort(S.begin(), S.end());
    sub(S, 0, path, result);
    return result;
}


// Get all subsets of length k without duplicates

void sub(vector<int> &s, int begin, vector<int> &path,
         vector<vector<int> > &result, int k) {
    if (path.size() == k){
        result.push_back(path);
        return;
    }
    
    for (int i = begin; i < s.size(); ++i) {
        if (i != begin && s[i] == s[i - 1]) continue;
        
        path.push_back(s[i]);
        sub(s, i + 1, path, result, k);
        path.pop_back();
    }
}


vector<vector<int> > subsetsWithDup(vector<int> &S, int k) {
    vector<int> path;
    vector<vector<int> > result;
    
    sort(S.begin(), S.end());
    sub(S, 0, path, result, k);
    return result;
}
