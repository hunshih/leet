//
//  main.cpp
//  test2
//
//  Created by Shu Lin on 10/12/12.
//  Copyright (c) 2012 Shu Lin. All rights reserved.
//

#include <cstdio>
#include <cstring>

#define maxn 100050

int head[maxn]; // head[j] stores the index of one edge that start from node j.
                // Other edge that start from j can be retrieved by following
                // edge[head[j]].next.

int fa[maxn];   // Disjoint-set algorithm.

bool v[maxn];   // v[i] indicating if there is an incoming edge to node i.
                // this is for finding the root of the tree.

bool success;   // Indicates if we have found the longest common ancestor of a and b.

int a, b, from, to, ans;

struct Edge {
    int v;      // The end of the edge
    int next;   // The next edge that has the same starting node
} e[maxn];      // Total number of possible edges.

int find_fa(int x){ // Find the parent of x. Same thing from disjoing-set algorithm.
    if (x == fa[x])
        return x;
    return fa[x] = find_fa(fa[x]);
}

// Idea of tarjan: DFS, after a subtree is traversed,
// in its each level all children have their fa[x]
// pointing at their immediate parent. When we find
// both nodes of our LCA query, the parent must be one
// level above the subtree we completely traversed.
void tarjan(int x){ // Tarjan algorithm.
    int k;
    fa[x] = x;  // By setting fa[x] = x, we are also recording x has been visited.
    
    // DFS. Go through each child of current node.
    for (k = head[x]; k != -1 && !success; k = e[k].next) {
        
        tarjan(e[k].v);
        
        // After we traversed the subtrees of current node,
        // set the father of all its immediate children to be current node.
        // We can't use the usual make_union function of
        // disjoint-set algorithm here, becase the longest common ancestor
        // of current node's different children is only the current node,
        // not the father of current node.
        fa[e[k].v] = x;
    }
    
    // If we have explored both node that we are looking for, the parent of the
    // first explored node must be the longest common ancestor. 
    if (x == a && fa[b]){
        success = 1;
        ans = find_fa(b);
    }
    else if (x == b && fa[a]){
        success = 1;
        ans = find_fa(a);
    }
    
    return;
}

int main()
{
    freopen("file1", "r", stdin);
    int t;
    scanf("%d", &t);
    while (t --)
    {
        int n;
        scanf("%d", &n);
        memset(head, -1, sizeof(head));
        memset(fa, 0, sizeof(fa));
        memset(e, 0, sizeof(e));
        memset(v, 0, sizeof(v));
        
        // This is a fast and clean way to express a graph.
        // head[a] saves the first edge of all edges that start
        // from node a. The rest of the edges are linked one by one by
        // the structure Edge.next.
        for (int i = 1; i < n; ++ i)
        {
            // i is the index of current edge.
            scanf("%d %d", &from, &to);
            e[i].v = to;
            e[i].next = head[from];
            head[from] = i;
            v[to] = 1;
        }
        
        // We need to find the longest common ancestor of node a and node b.
        scanf("%d%d", &a, &b);
        success = 0;
        for (int i = 1; i <= n; ++ i)
            if (!v[i])
                tarjan(i);
        printf("%d\n", ans);
    }
    return 0;
}
