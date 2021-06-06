
// Return the index of value in array. If not exist, return -1.
int binarySearch(const vector<int> &array, int target){

    int left = 0, right = (int)array.size();

    while (left < right) {

        int middle = (left + right) >> 1;

        if (array[middle] == target) return middle;

        array[middle] < target ? left = middle + 1 : right = middle;
    }

    return -1;
}

// Return the index of first element >= target.
int binarySearch(const vector<int> &array, int target){
    int left = 0, right = (int)array.size();
    while (left < right) {
        int middle = (left + right) >> 1;
        if (array[middle] == target) return middle;
        array[middle] < target ? left = middle + 1 : right = middle;
    }
    return right;
}

// Find the first or last occurrence of the target in the array.
// find_first == true -> find first occurrence
// find_first == false -> find last occurrence
int find_occurrence(const vector<int> &array, int target, bool find_first){
    int left = 0, right = int(array.size());
    int result = -1;
    while (left < right) {
        int middle = (left + right) >> 1;
        if (array[middle] == target){
            result = middle;
            if (find_first)
                right = middle;
            else
                left = middle + 1;
        }
        else if (array[middle] < target)
            left = middle + 1;
        else
            right = middle;
    }
    return result;
}