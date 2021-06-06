// Simple hash table
struct HashStruct {
    int num;
    int cnt;
    HashStruct(): num(0), cnt(0){}
    HashStruct(int num_, int cnt_): num(num_), cnt(cnt_){}
};

int get_hash(int k){
    int hash = 0;
    while (k) {
        hash <<= 7;
        hash ^= k % 10;
        k /= 10;
    }
    return hash;
}

int find_entry(const vector<HashStruct> &array, int key){
    for (int i = 0; i < array.size(); ++i) {
        if (array[i].num == key){
            return i;
        }
    }
    return -1;
}


// find one character that appears only once in the arary.
int find_non_duplicates(const vector<int> &array){
    vector<vector<HashStruct>> table(array.size() * 2);
    
    for (int i = 0; i < array.size(); ++i) {
        int hash = get_hash(array[i]) % table.size();
        int loc = find_entry(table[hash], array[i]);
        if (loc < 0){
            table[hash].push_back(HashStruct(array[i], 1));
        }
        else
            table[hash][loc].cnt++;
    }
    
    for (int i = 0; i < table.size(); ++i) {
        for (int j = 0; j < table[i].size(); ++j) {
            if (table[i][j].cnt == 1)
                return table[i][j].num;
        }
    }
    return -1;
}
