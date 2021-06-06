
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <list>
#include <queue>
#include <time.h>
#include <sstream>
#include <stack>
#include <memory>
#include <unistd.h>
#include <cmath>
#include <set>

using namespace std;

// For navigate inside binary indexed tree.
int lowbit(int k){
    return k&-k; // k shouldn't be zero. Thus the tree shouldn't use index 0.
}

// Add val to the number at index.
void modify(vector<int> &tree, int index, int val){
    for (; index < tree.size(); index += lowbit(index))
        tree[index] += val;
}

// Get the sum of all elements before endIndex (including endIndex).
int addSum(const vector<int> &tree, int endIndex){
    int result = 0;
    for (; endIndex > 0; endIndex -= lowbit(endIndex))
        result += tree[endIndex];
    return result;
}
// If want sum from index a to index b, could
// just do addSum(array, b) - addSum(array, a).

// To make a tree from an array.
vector<int> makeTree(const vector<int> &array){
    vector<int> tree(array.size(), 0);
    
    // Warning: the tree shouldn't use index zero.
    // Here we assume array[0] is not used.
    for (int i = 1; i < array.size(); ++i) {
        modify(tree, i, array[i]);
    }
    return tree;
}

int main(void)
{
    vector<int> array(12, 0);
    for (int i = 1; i < 12; i++) {
        modify(array, i, 1);
    }
    cout << addSum(array, 11) << endl;
    
    return 0;
}



















