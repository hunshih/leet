//
//  union-find_algorithm.cpp
//  poj 1308 Is It A Tree?
//
//  Created by Shu Lin on 7/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#define maxNode 100

using namespace std;

int parent[maxNode], // Keep the parent of each node.
    rank[maxNode];  //  Keep track of the height of each node.

// Looking for the parent of x.
int find_parent(int x){
    
    // Do path compression.
    if (x != parent[x]) // base case is x == parent[x]
        parent[x] = find_parent(parent[x]);
    
    return parent[x];
}

// Merge two set together.
void make_union(int x, int y){
    
    // First find the parent of each node. 
    // *** This step is necessary! ***
    x = find_parent(x);
    y = find_parent(y);
    
    if (rank[x] > rank[y])
        parent[y] = x;
    else if (rank[y] > rank[x]) {
        parent[x] = y;
    }
    else {
        parent[y] = x;
        rank[x]++;
    }
    
    return;
}

// Set the parent of each node to be itself.
void init(int total){
    
    memset(rank, 0, sizeof(rank));
    for (int i = 0; i < total; i++) {
        parent[i] = i;
    }
    return;
}



// ==================== implementation 9.1.2013 ====================

int findParent(int x, vector<int> &parent){
    if (x != parent[x])
        parent[x] = findParent(parent[x], parent);
    return parent[x];
}

void makeUnion(int x, int y, vector<int> &parent, vector<int> &rank){
    int xParent = findParent(x, parent);
    int yParent = findParent(y, parent);
    if (rank[xParent] > rank[yParent])
        parent[yParent] = xParent;
    else
        parent[xParent] = yParent;
    if (rank[xParent] == rank[yParent])
        ++rank[yParent];
}

vector<int> init(int n){
    vector<int> parent;
    for (int i = 0; i < n; ++i)
        parent.push_back(i);
    return parent;
}