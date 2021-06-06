
struct Interval {
    int head, tail;
    Interval(int a_, int b_): head(a_), tail(b_){}
    Interval(): head(INT_MAX), tail(INT_MAX){}
};

// ========================= Merge =========================

// Merge two arrays of intervals. Assuming each array's intervals are sorted 
// and are not overlaped between each other.
vector<Interval> merge_interval(const vector<Interval> &list_1, const vector<Interval> &list_2){
    vector<Interval> sorted;
    vector<Interval> ret;
    auto iter1 = list_1.begin(), iter2 = list_2.begin();
    
    // Merge list.
    while (iter1 != list_1.end() && iter2 != list_2.end()) {
        if (iter1->head < iter2->head)
            sorted.push_back(*iter1++);
        else
            sorted.push_back(*iter2++);
    }
    if (iter1 != list_1.end())
        sorted.insert(sorted.end(), iter1, list_1.end());
    if (iter2 != list_2.end())
        sorted.insert(sorted.end(), iter2, list_2.end());
    
    // Process merge.
    for (int i = 0; i < sorted.size(); ++i) {
        if (ret.size() && sorted[i].head <= ret.back().tail)
            ret.back().tail = max(ret.back().tail, sorted[i].tail);
        else
            ret.push_back(sorted[i]);
    }
    
    return ret;
}

// ========================= Find intersection =========================
// There should be an easier way.

vector<Interval> find_intersection(const vector<Interval> &list_1,
                                   const vector<Interval> &list_2){
    
    vector<Interval> sorted;
    vector<Interval> ret;
    vector<bool> confirmed;
    auto iter1 = list_1.begin(), iter2 = list_2.begin();
    
    // Merge list.
    while (iter1 != list_1.end() && iter2 != list_2.end()) {
        if (iter1->head < iter2->head)
            sorted.push_back(*iter1++);
        else
            sorted.push_back(*iter2++);
    }
    if (iter1 != list_1.end())
        sorted.insert(sorted.end(), iter1, list_1.end());
    if (iter2 != list_2.end())
        sorted.insert(sorted.end(), iter2, list_2.end());
    
    // Process merge.
    for (int i = 0; i < sorted.size(); ++i) {
        if (ret.size() && sorted[i].head <= ret.back().tail){
            ret.back().head = sorted[i].head;
            if (sorted[i].tail < ret.back().tail){
                ret.back().tail = sorted[i].tail;
            }
            confirmed.back() = true;
        }
        else if (ret.size() && !confirmed.back()){
            ret.pop_back();
            confirmed.pop_back();
        }
        ret.push_back(sorted[i]);
        confirmed.push_back(false);
    }
    
    if (ret.size() && !confirmed.back()){
        ret.pop_back();
        confirmed.pop_back();
    }
    
    return ret;
}

// ========================= Find intersection =========================
// Merge two arrays of intervals. Assuming each array's intervals are sorted 
// and are not overlaped between each other.

void increment(bool &is_head, vector<Interval>::const_iterator &iter, int &count){
    if (is_head){
        is_head = false;
        ++count;
        return;
    }
    ++iter;
    is_head = true;
    --count;
}

vector<Interval> find_intersection(const vector<Interval> &list_1,
                                   const vector<Interval> &list_2){
    
    bool is_head_1 = true, is_head_2 = true;
    
    vector<Interval>::const_iterator iter_1 = list_1.begin();
    vector<Interval>::const_iterator iter_2 = list_2.begin();
    
    int count = 0;
    Interval cur_interval;
    vector<Interval> ret;
    
    while (iter_1 != list_1.end() && iter_2 != list_2.end()) {
        
        int a = is_head_1 ? iter_1->head : iter_1->tail;
        int b = is_head_2 ? iter_2->head : iter_2->tail;
        int min = std::min(a, b);
        
        if (count == 2){
            cur_interval.tail = min;
            ret.push_back(cur_interval);
        }
        
        if (count == 1){
            cur_interval.head = min;
        }
        
        if (count == 0){}
        
        if (a == b)
            is_head_1 ? increment(is_head_1, iter_1, count) : increment(is_head_2, iter_2, count);
        else
            min == a ? increment(is_head_1, iter_1, count) : increment(is_head_2, iter_2, count);
    }
    
    return ret;
}