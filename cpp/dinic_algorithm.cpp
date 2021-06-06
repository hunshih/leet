#include <iostream>

#define max_nodes 201
#define oo 10000000000

int n,m,source, sink;

int map[max_nodes][max_nodes];
int pi[max_nodes];
int currentArc[max_nodes];

int queue[max_nodes];
int d[max_nodes];
int numbs[max_nodes];

using namespace std;

void rev_BFS(){
    
    //memset(d, 0x00000000 + n, sizeof(d));
    for (int k = 0; k <= n; k++) {
        d[k] = n;
    }
    memset(numbs, 0, sizeof(numbs));
    memset(queue, 0, sizeof(queue));
    int head = 0, tail = 0, i;
    
    numbs[n] = n - 1;
    d[sink] = 0;
    numbs[0]++;
    
    queue[tail++] = sink;
    
    while (head < tail) {
        
        i = queue[head++];
        
        for (int j = 1; j <= n; j++) {
            if (d[j] < n || !map[j][i])
                continue;
            
            numbs[n]--;
            d[j] = d[i] + 1;
            numbs[d[j]]++;
            
            queue[tail++] = j;
            
        }
    } 
    
    return;
}

int calc_augment(){
    
    int augment = oo, i, j;
    
    for (i = sink; i != source; i = j) {
        j = pi[i];
        augment = (map[j][i] < augment) ? map[j][i] : augment;
    }
    
    for (i = sink; i != source; i = j) {
        j = pi[i];
        map[j][i] -= augment;
        map[i][j] += augment;
    }
    
    return augment;
}


bool relabel(int i){
    
    int mind = n, temp = d[i];
    
    for (int j = 1; j <= n; j++) 
        
        // if there is an edge between i and j and j is 
        // the nearest to sink in all nodes connected with i.
        if (map[i][j] > 0 && d[j] < mind){
            mind = d[j];
        }
    
    // remove i from the layer.
    numbs[d[i]]--;
    
    // set i to be 1 layer farther from the sink than i's previous sink-nearest neighour.
    d[i] = mind + 1;
    numbs[d[i]]++;
    
    return numbs[temp];
}

int find_max_flow(){
    
    int max_flow = 0, i, j;
    
    rev_BFS();
    for (int k = 1; k <= n ; k++) {
        currentArc[k] = 1;
    }
    i = source;
    
    while (d[i] < n) {
        
        for (j = currentArc[i]; j <= n; j++)
            
            if (map[i][j] > 0 && (d[i] == d[j] + 1)) 
                break;
        
        if (j <= n){
            
            pi[j] = i;
            currentArc[i] = j;
            i = j;
            
            if (j == sink){
                max_flow += calc_augment();
                i = source;
            }
        }
        
        else{
            
            if (!relabel(i)) 
                break;
            
            currentArc[i] = 1; 
            if (i != source)
                i = pi[i];  //Retreat;
        }
        
    }
    
    return max_flow;
}


int main()
{
    freopen("file1", "r", stdin);
    
    int first, second, w;
    while (scanf("%d%d", &m, &n) != EOF) {
        memset(map, 0, sizeof(map));
        source = 1;
        sink = n;
        
        for (int i = 0; i < m; i++) {
            scanf("%d%d%d", &first, &second, &w);
            map[first][second] += w;
        }
        
        printf("%d\n", find_max_flow());
    }
    
    return 0;
}