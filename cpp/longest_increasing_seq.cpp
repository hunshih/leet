int find_lis(vector<int> &Array){
    
    vector<int> record(Array.size());
    int left, right, mid, len = 1;
    record[0] = Array[0];
    for (size_t i = 1; i < Array.size(); i++) {
        // Binary search to get the location of Array[i] in record.
        left = 0, right = len;
        while (left <= right) {
            mid = (left + right) >> 1;

            // If looking for non-decreasing sequence, use <= 
            // in the line below.
            if (record[mid] < Array[i])
                left = mid + 1;
            else
                right = mid - 1;
        }
        record[left] = Array[i];
        
        if (left > len)
            len++;
    }
    
    return len;
}

// =================== implementation 09.02.2013 ===================

// This binary search returns the index of the first element greater k.
// If k is greater than all elements in array, return one past last index.
size_t binarySearch(int k, const vector<int> &array){
    size_t left = 0, right(array.size());
    while (left < right) {
        size_t mid = (left + right) / 2;
        if (array[mid] < k)
            left = mid + 1;
        else
            right = mid;
    }
    return right;
}

int LIS(const vector<int> array){
    // dp[i] represents the smallest ending integer of LIS of
    // length i.
    vector<int> dp;
    for (int i = 0; i < array.size(); ++i) {
        auto loc = binarySearch(array[i], dp);
        if (loc == dp.size())
            dp.push_back(array[i]);
        else
            dp[loc] = array[i];
    }
    return (int)dp.size();
}


// =================== implementation 09.26.2013 ===================
// Return the first element >= target.
int binarySearch(const vector<int> &array, int target){
    int left = 0, right = (int)array.size();
    while (left < right) {
        int middle = (left + right) >> 1;
        if (array[middle] == target) return middle;
        array[middle] < target ? left = middle + 1 : right = middle;
    }
    return right;
}

// Use binary search and dynamic programming.
int LIS(const vector<int> &array){
    vector<int> dp;
    for (int i = 0; i < array.size(); ++i) {
        int ind = binarySearch(dp, array[i]);
        if (ind == (int)dp.size()) dp.push_back(array[i]);
        dp[ind] = array[i];
    }
    return (int)dp.size();
}

// =================== implementation 10.9.2013 ===================
// Use only dynamic programming. Complexity: O(n^2)
int LIS(const vector<int> &array){
    vector<int> dp(array.size(), 1);
    for (int i = 0; i < array.size() - 1; ++i) {
        for (int j = i + 1; j < array.size(); ++j) {
            if (array[i] < array[j]){
                dp[j] = max(dp[i] + 1, dp[j]);
            }
        }
    }
    return *max_element(dp.begin(), dp.end());
}

// =================== implementation 10.20.2013 ===================
// The power of standard library..
int LIS(const vector<int> &array){
    
    vector<int> dp;
    for (auto cur_num : array) {
        
        auto loc = lower_bound(dp.begin(), dp.end(), cur_num) - dp.begin();
        if (loc == dp.size())
            dp.push_back(cur_num);
        else
            dp[loc] = cur_num;
    }
    return (int)dp.size();
}

