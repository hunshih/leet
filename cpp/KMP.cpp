#include <vector>
#include <string>
#include <iostream>
using std::vector;
using std::string;

// KMP string matching.
vector<int> KMPnext(string str){
    vector<int> next(str.size());
    int i = 0, j = -1;
    next[i] = j;
    while (i < str.size()) {
        while (j >= 0 && str[i] != str[j]) {
            j = next[j];
        }
        i++;
        j++;
        next[i] = j;
    }
    return next;
}

bool KMP(string nstr, string pat, vector<int> & next){
    int i = 0, j = 0;
    while (i < nstr.size()) {
        while (nstr[i] != pat[j] && j >= 0) {
            j = next[j];
        }
        i++;
        j++;
        if (j == pat.size())
            return true;
    }
    return false;
}

// ==================== implementation 10.11.2013 ====================

vector<int> get_next(const string &str){
    vector<int> next(str.size(), -1);
    int i = 0, j = -1;
    while (i < str.size()) {
        while (j >= 0 && str[i] != str[j])
            j = next[j];
        
        ++i, ++j;
        next[i] = j;
    }
    return next;
}

bool KMP(const string &str, const string &pat){
    vector<int> next = get_next(pat);
    int i = 0, j = 0;
    while (i < str.size()) {
        
        while (j >= 0 && str[i] != pat[j])
            j = next[j];
        
        ++i, ++j;
        if (j == pat.size())
            return true;
    }
    return false;
}

// KMP Demo
int main(){
    
    string str = "aaaabaab";
    vector<string> pat{"aaaab", "aaabc"};
    
    for (int i = 0; i < pat.size(); i++) {
        
        vector<int> next = KMPnext(pat[i]);
        bool is_substr = KMP(str, pat[i], next);
        
        std::cout << pat[i] << " is a substring of " << str << "? ";
        std::cout << (is_substr ? "Yes" : "No") << std::endl;
    }
    
}