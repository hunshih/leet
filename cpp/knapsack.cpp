// knapsack

// Suppose you have infinite bills with different dominations. Ask the min
// number of bills you need to get total number of dollars. Note that 1 dollar 
// bill might not be provided. If it's not possible, return -1.
int unbounded_knapsack(const vector<int> &values, int total){
    vector<int> min_bills(total + 1);
    vector<bool> possible(total + 1, false);
    for (int i = 0; i < min_bills.size(); ++i)
        min_bills[i] = i;

    possible[0] = true;
    for (int i = 0; i < values.size(); ++i) {
        for (int j = values[i]; j <= total; ++j) {
            if (possible[j - values[i]]){
                min_bills[j] = min(min_bills[j], min_bills[j - values[i]] + 1);
                possible[j] = true;
            }
        }
    }

    if (possible[total])
        return min_bills[total];;
    return -1;
}

// Suppose you have infinite bills with different dominations. Ask the min
// number of bills you need to get total number of dollars. Here, 1 dollar 
// bill is available, so we can always add up to the total number. 
int unbounded_knapsack(const vector<int> &values, int total){

    vector<int> min_bills(total + 1);
    for (int i = 0; i < min_bills.size(); ++i)
        min_bills[i] = i;

    for (int i = 0; i < values.size(); ++i) 
        for (int j = values[i]; j <= total; ++j) 
                min_bills[j] = min(min_bills[j], min_bills[j - values[i]] + 1);
            
    return min_bills[total];;
}

// Knapsack. Suppose all the bills you have are already in values[]. Find out
// the least number of bills you need to have a total number of dollars. If
// it's not possible, return -1.
int knapsack(const vector<int> &values, int total){

    const int impossible_value_c = total + 1;
    vector<int> min_bills(total + 1, impossible_value_c);
    
    min_bills[0] = 0;
    for (int i = 0; i < values.size(); ++i)
        for (int j = total; j >= values[i]; --j)
            min_bills[j] = min(min_bills[j], min_bills[j - values[i]] + 1);

    if (min_bills[total] == impossible_value_c)
        return -1;
    return min_bills[total];;    
}
