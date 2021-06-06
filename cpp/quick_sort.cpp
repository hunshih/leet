// Quick sort
void ksort(int l, int h){
    if (h < l + 1) return;
    int e = h++, p = l; // h++ because we use --h in code below.
    while (l < h) {
        
        while (++l < e && myArray[l] <= myArray[p]); // ++l because we don't want the pivot to be considered.
        while (--h > p && myArray[h] >= myArray[p]); // --h because we need to start at the end of the array. (Why not h-- ? Because we then need to say ">= (p + 1)").
        if (l < h) swap(myArray[l], myArray[h]); // Why not <= ? Because there would be no need to swap if they are the same element.
    }
    swap(myArray[h], myArray[p]);
    ksort(p, h); ksort(l, e);
}

// =================== implementation 09.06.2013 ======================
// a is the beginning index, b is one past the end index.
void quickSort(vector<int> &array, int a, int b){
    if (a + 1 > b)
        return;
    int pivot = a, left = a, right = b;
    while (left < right) {
        while (++left < b && array[left] <= array[pivot]);
        while (--right > a && array[right] >= array[pivot]);
        if (left < right) swap(array[left], array[right]);
    }
    swap(array[pivot], array[right]);
    quickSort(array, a, right);
    quickSort(array, right + 1, b);
}

// Quick sort using iteration.
void quick_sort(int start, int end){
    
    struct Partition {
        int l;
        int r;
        Partition(){l = 0, r = 0;}
        Partition(int start, int end){l = start, r = end;}
    };
    
    stack<Partition> mystack;
    int i, j;
    mystack.push(Partition(start, end));
    
    while (!mystack.empty()) {
        
        Partition cur_part = mystack.top();
        i = cur_part.l;
        j = cur_part.r;
        mystack.pop();
        
        if (i >= j)
            continue;
        j++;
        
        while (i < j) {
            while (++i <= cur_part.r && myArray[i] <= myArray[cur_part.l]);
            while (--j > cur_part.l && myArray[j] >= myArray[cur_part.l]);
            if (i < j)
                swap(myArray[i], myArray[j]);
        }
        swap(myArray[cur_part.l], myArray[j]);
        mystack.push(Partition(cur_part.l, j));
        mystack.push(Partition(i, cur_part.r));
    }
}