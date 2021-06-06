// Find the k-th smallest number, counting from 0.
int find_kth(vector<int> array, int k){
    // Left is the index of the first element.
    int left = 0;
    // Right is the index of one past the last element.
    int right = (int)array.size();
    
    while (left < right) {
        // This part is identical with quick sort partition.
        int pivot = left, i = left, j = right;
        while (i < j){
            while (++i < right && array[pivot] >= array[i]);
            while (--j > left && array[pivot] <= array[j]);
            if (i < j) swap(array[i], array[j]);
        }
        swap(array[pivot], array[j]);
        if (k == j) return array[k];
        // Select which subrange to partition next.
        // Note that right is one past the last element index.
        k > j ? left = j + 1: right = j;
    }
    return array[k];
}

int main(){
    vector<int> array{-5, -19, -2818, 3, 1, 0, 0, -1, -19, 91};
    for (int i = 0; i < array.size(); ++i) {
        cout << find_kth(array, i) << endl;
    }
    return 0;
}