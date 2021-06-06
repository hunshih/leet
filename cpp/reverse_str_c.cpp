void reverse_str(char *str){
    char *it2 = str + strlen(str) - 1;
    for (char *it1 = str; it1 < it2; ++it1, --it2) {
        *it1 ^= *it2;
        *it2 ^= *it1;
        *it1 ^= *it2;
    }
}
