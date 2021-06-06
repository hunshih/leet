
// Merge sort. 

// ======================= Implementation 11.17.2013 =======================
typedef vector<int> IntVector;

IntVector merge(const IntVector &list1, const IntVector &list2){
    IntVector ret;
    merge(list1.begin(), list1.end(), list2.begin(), list2.end(), back_inserter(ret));
    return ret;
}

IntVector mergeSort(IntVector &array, int a, int b){
    if (b - a <= 1)
        return IntVector{array[a]};
    int mid = (a + b) >> 1;
    return merge(mergeSort(array, a, mid), mergeSort(array, mid, b));
}

// ======================= Old Implementation =======================
vector<int> merge(const vector<int> &list1, const vector<int> &list2){
    vector<int> ret;
    auto iter1 = list1.begin(), iter2 = list2.begin();
    
    while (iter1 != list1.end() && iter2 != list2.end())
        ret.push_back(*iter1 <= *iter2 ? *iter1++ : *iter2++);
    
    ret.insert(ret.end(), iter1, list1.end());
    ret.insert(ret.end(), iter2, list2.end());
    return ret;
}

vector<int> merge_sort(const vector<int> &array, int a, int b){
    if (a + 2 > b)
        return vector<int>{array[a]};
    int mid = (a + b)/2;
    return merge(merge_sort(array, a, mid), merge_sort(array, mid, b));
}

int main(void){
    
    vector<int> array = {-1, 9, -1, 91, 93, 18, 9, 13, -1, -1, 0, -1, 0};
    array = merge_sort(array, 0, (int)array.size());
    printIntVector(array);

    return 0;
}

