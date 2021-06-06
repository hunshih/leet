// Counting sort a string.
string cnt_sort(string const &str){
    int cnt[256];
    string result;
    memset(cnt, 0, sizeof(cnt));
    for (size_t i = 0; i < str.size(); i++) {
        cnt[str[i]]++;
    }
    for (size_t i = 0; i < 256; i++) {
        if (!cnt[i]) continue;
        while (cnt[i]--) {
            result += i;
        }
    }
    return result;
}