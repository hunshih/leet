// Partition an array with only numbers 1, 2, 3.
// 231123231333222 -> 1112222233...
void partition_3_way(vector<int> &array){
    
    if (array.size() <= 1) return;
    int ptr_1 = 0, ptr_2 = 0, ptr_3 = (int)array.size() - 1;
    
    // Note here we have "<=".
    while (ptr_2 <= ptr_3) {
        if (array[ptr_2] == 1)
            swap(array[ptr_1++], array[ptr_2++]);
        
        else if (array[ptr_2] == 3)
            swap(array[ptr_2], array[ptr_3--]);
        
        else
            ++ptr_2;
    }
}
