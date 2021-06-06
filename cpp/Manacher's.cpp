// Manacher's Algorithm to find longest palindrome



// ================== Implementation 11.17.2013 ==================
string manacher(const string &str){
    
    string longStr;
    const char special_c = 1;
    
    for (auto c : str)
        longStr += special_c, longStr += c;
    longStr += special_c;
    
    IntVector p(longStr.size(), 0);
    int mx = 0, id = 0;
    for (int i = 0; i < longStr.size(); ++i) {
        p[i] = i > mx ? 1 : min(mx - i, p[2 * id - i]);
        while (i >= p[i] && longStr[i + p[i]] == longStr[i - p[i]]) {
            ++p[i];
        }
        if (p[i] + i > mx){
            mx = p[i] + i;
            id = i;
        }
    }
    
    int max_p = *max_element(p.begin(), p.end());
    auto max_ind = find(p.begin(), p.end(), max_p) - p.begin();
    --max_p;
    
    return str.substr((max_ind - max_p) / 2, max_p);
}

// ================== Oldest Implementation ==================

#define SPECIAL_SIGN 1
char r[maxn], s[2 * maxn];
int p[2 * maxn];

int manacher(char r[]){
    
    int n = (int)strlen(r), i, j, maxLen, mx, id;

    // Preprocess, add a special sign at begin and after every char.
    for (j = 0, i = 0; i < n; i++) {
        s[j++] = SPECIAL_SIGN;
        s[j++] = r[i];
    }
    s[j++] = SPECIAL_SIGN;
    
    // Manacher's algorithm.
    memset(p, 0, sizeof(p));
    mx = 0, id = 0;
    for (i = 1; i < j; i++) {   // j is the length of the string.
        p[i] = mx > i ? min(p[2 * id - i], mx - i) : 1; // 2 * id - i is i关于id的对称点.
        while ((s[i - p[i]] == s[i + p[i]]) && i >= p[i]) p[i]++;
        if (mx < i + p[i]){
            mx = i + p[i];  // mx is the farthest point we ever looked.
            id = i;         // id is the central of the palindrome that touches mx.
        }
    }
    
    // Return max_value - 1.
    maxLen = *max_element(p + 1, p + j);
    return maxLen - 1;
}

// ================== Implementation 8.27.2013 ==================
// This version is better.
int manacher(const string &str){
    
    // Preprocess, add a special sign at begin and after every char.
    string longStr;
    const char specialSign = 1;
    for (auto it = str.begin(); it != str.end(); ++it) {
        longStr += specialSign;
        longStr += *it;
    }
    longStr += specialSign;
    
    int mx = 0; // mx is the farthest point we ever looked.
    int id = 0; // id is the central of the palindrome that touches mx.
    vector<int> p(longStr.size(), 0);
    for (int i = 0; i < longStr.size(); ++i) {
        
        // [2 * id - i] is the symmetry point of i on the other side of id.
        p[i] = mx > i ? std::min(p[2 * id - i], mx - i) : 1;
        while (i >= p[i] && longStr[i - p[i]] == longStr[i + p[i]])
            ++p[i];
        if (i + p[i] > mx){
            id = i;
            mx = i + p[i];
        }
    }
    
    // Return max_value - 1.
    return *max_element(p.begin(), p.end()) - 1;
}

// ================== Implementation 10.7.2013 ==================
string manacher(const string &str){
    string longStr;
    const char special_sign_c = 1;
    for_each(str.begin(), str.end(), [&](char c){
        longStr += special_sign_c;
        longStr += c;
    });
    longStr += special_sign_c;
    
    vector<int> p(longStr.size(), 0);
    int mx = 0, id = 0;
    for (int i = 0; i < longStr.size(); ++i) {
        p[i] = mx > i ? min(p[2 * id - i], mx - i) : 1;
        while (i >= p[i] && longStr[i - p[i]] == longStr[i + p[i]]) {
            ++p[i];
        }
        if (i + p[i] > mx){
            mx = i + p[i];
            id = i;
        }
    }
    
    // Find the max element and its index. in p.
    int max_p = *max_element(p.begin(), p.end());
    int max_ind = int(find(p.begin(), p.end(), max_p) - p.begin());
    --max_p;
    
    return str.substr((max_ind - max_p)/2, max_p);
}
