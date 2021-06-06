// Rotate a string by k positions.
void reverse_array(char *k, int n){
    // reverse k in its first n positions.
    
    n--;
    for (size_t i = 0; i <= (n >> 1); i++) {
        
        // if k[i] == k[n - i], ^= will set k[i] to null,
        // which will change the string length.
        
        if (k[i] != k[n - i]){
            k[i] ^= k[n - i];
            k[n - i] ^= k[i];
            k[i] ^= k[n - i];
        }
    }
    return;
}

void rotate_arr(char a[], int k){
// Rotate a forword k positions.
    
    // If k > n, result is the same as k % n.
    int n = (int)strlen(a);
    k %= n;
    if (!k)
        return;
    reverse_array(a, k);
    reverse_array(a + k, n - k);
    reverse_array(a, n);
}
