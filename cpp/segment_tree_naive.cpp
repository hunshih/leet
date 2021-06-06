
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

struct TreeNode {
    int left, right;
    int mid;
    int cover;
    TreeNode *leftChild;    // leftChild covers left <= x <= mid,
    TreeNode *rightChild;   // rightChild covers mid < x <= right,
    TreeNode(int left_, int right_):
        left(left_),
        right(right_),
        mid((left_ + right_) >> 1),
        cover(0),
        leftChild(nullptr),
        rightChild(nullptr){};
};

// Build a tree that spans the entire range.
TreeNode *build(int left_, int right_){
    TreeNode *root = new TreeNode(left_, right_);
    
    // If the segment is still bigger than 1, continue dividing.
    if (left_ < right_){
        // Here make sure left child represents [left_, root->mid],
        // not [left_, root->mid-1]. In case of [3, 4], the latter would
        // call build(3, 2), which screws up everything.
        root->leftChild = build(left_, root->mid);
        root->rightChild = build(root->mid + 1, right_);
    }
    return root;
}

// Insert a segment into the tree, increasing the count of the segment by 1.
void insert(int left_, int right_, TreeNode *root)
{
    // If this tree all under the segment, update its cover count.
    if (left_ <= root->left && right_ >= root->right){
        root->cover++;
        return;
    }
    
    if (left_ <= root->mid) insert(left_, right_, root->leftChild);
    if (right_ > root->mid) insert(left_, right_, root->rightChild);
}

// How many segments covered the point i.
int query(int i, TreeNode *root)
{
    if (!root)
        return 0;
    if (i <= root->mid){
        return root->cover + query(i, root->leftChild);
    }
    if (i > root->mid){
        return root->cover + query(i, root->rightChild);
    }
    return 0;
}

int main(void)
{
    TreeNode * tree = build(1, 10);
    insert(2, 4, tree);
    insert(3, 6, tree);
    insert(4, 5, tree);
    insert(7, 7, tree);
    insert(5, 9, tree);
    cout << query(3, tree)<< endl;
    return 0;
}



// ============== Implementation 8.26.2013 ==============

struct SegTreeNode {
    int left, right, mid, cnt;
    SegTreeNode *leftChild, *rightChild;
    SegTreeNode(int left_, int right_): left(left_), right(right_),
    mid((left_ + right_) / 2), cnt(0), leftChild(nullptr), rightChild(nullptr){}
};

SegTreeNode *buildTree(int a, int b){
    SegTreeNode *root = new SegTreeNode(a, b);
    if (a < b){
        root->leftChild = buildTree(a, root->mid);
        root->rightChild = buildTree(root->mid + 1, b);
    }
    return root;
}

void addCount(int a, int b, SegTreeNode *root){
    if (a <= root->left && b >= root->right){
        ++root->cnt;
        return;
    }
    if (a <= root->mid)
        addCount(a, b, root->leftChild);
    if (b > root->mid)
        addCount(a, b, root->rightChild);
}

int getCount(int k, SegTreeNode *root){
    if (!root) return 0;
    if (k <= root->mid)
        return root->cnt + getCount(k, root->leftChild);
    else
        return root->cnt + getCount(k, root->rightChild);
}

void freeTree(SegTreeNode *root){
    if (root->leftChild) freeTree(root->leftChild);
    if (root->rightChild) freeTree(root->rightChild);
    delete root;
}









