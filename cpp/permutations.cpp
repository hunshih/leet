
// Print all permutations of a vector.
void add_perm(vector<vector<int>> &perms, int cur_num){
    if (perms.empty()){
        perms.push_back(vector<int>{cur_num});
        return;
    }
    
    int old_size = int(perms.size());
    for (int i = 0; i < old_size; ++i) {
        for (int j = 0; j <= perms[i].size(); ++j) {
            perms.push_back(perms[i]);
            (perms.end() - 1)->insert(perms[perms.size() - 1].begin() + j, cur_num);
        }
    }
    
    perms.erase(perms.begin(), perms.begin() + old_size);
    return;
}


void print_all_perm(const vector<int> &array){
    vector<vector<int>> all_perms;
    for (int i = 0; i < array.size(); ++i) {
        add_perm(all_perms, array[i]);
    }
    for (int i = 0; i < all_perms.size(); ++i) {
        for (int j = 0; j < all_perms[i].size(); ++j) {
            cout << all_perms[i][j] << " ";
        }
        cout << endl;
    }
}


// ============== implementation 10.15.2013 ==============

vector<string> add_perms(const vector<string> &old_perms, const string &ele){
    if (old_perms.empty())
        return vector<string> {ele};
    vector<string> new_perms;
    for (auto &old_perm : old_perms){
        for (int i = 0; i <= old_perm.size(); ++i){
            new_perms.push_back(old_perm);
            new_perms.back().insert(i, ele);
        }
    }
    return new_perms;
}

void get_perms(const string &str){
    vector<string> all_perms;
    for (int i = 0; i < str.size(); ++i)
        all_perms = add_perms(all_perms, str.substr(i, 1));
    for (auto &perm : all_perms)
        cout << perm << endl;
}


// ============== implementation 10.19.2013 ==============
// Permutation without duplicates.

void add_permutations(vector<int> &array, vector<bool> &used,
                      vector<int> &path, vector<vector<int>> &perms){
    if (path.size() == array.size()){
        perms.push_back(path);
        return;
    }
    
    for (int i = 0; i < array.size(); ++i){
        if (used[i] || (i && used[i - 1] && array[i] == array[i - 1]))
            continue;
        used[i] = true;
        path.push_back(array[i]);
        add_permutations(array, used, path, perms);
        path.pop_back();
        used[i] = false;
    }
}

vector<vector<int>> get_permutations(vector<int> &array){
    auto n = array.size();
    vector<bool> used(n, false);
    vector<int> path;
    vector<vector<int>> perms;
    sort(array.begin(), array.end());
    
    add_permutations(array, used, path, perms);
    return perms;
}

// ============== implementation 10.19.2013 ==============
// Get all permutations with length k and without duplicates.
void add_permutations(vector<int> &array, vector<bool> &used,
                      vector<int> &path, vector<vector<int>> &perms, int k){
    if (path.size() == k){
        perms.push_back(path);
        return;
    }
    
    for (int i = 0; i < array.size(); ++i){
        // Here we have !used[i - 1] since the only time we want to
        // skip a duplicate number if its previous duplicate
        // is not in the path.
        if (used[i] || (i && !used[i - 1] && array[i] == array[i - 1])) continue;
        used[i] = true;
        path.push_back(array[i]);
        add_permutations(array, used, path, perms, k);
        path.pop_back();
        used[i] = false;
    }
}

vector<vector<int>> get_permutations_of_length_k(vector<int> &array, int k){
    auto n = array.size();
    vector<bool> used(n, false);
    vector<int> path;
    vector<vector<int>> perms;
    sort(array.begin(), array.end());
    
    add_permutations(array, used, path, perms, k);
    return perms;
}

