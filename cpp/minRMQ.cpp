int RMQ[maxn] = {1, 7, 3, 4, 2, 5, -1, -1, -1};
int mm[maxn];
int best[20][maxn];

void initRMQ(int n)
{   // Prepare the RMQ for index of smallest element.
    // n is the number of element. Assume those elements
    // were indexed from 0 to n-1.
    
    int i,j,a,b;
    
    // Construct mm array.
    for(mm[0]=-1,i=1;i<=n;i++)
        mm[i]=((i&(i-1))==0)?mm[i-1]+1:mm[i-1];
    
    // Filling in initial values.
    for(i=1;i<=n;i++) best[0][i]=i;
    
    // DP.
    for(i=1;i<=mm[n];i++)
        for(j=1;j+(1<<i)-1<=n;j++)
            // When j = n-(1<<i), b=best[i-1][n-(1<<i)+1+(1<<(i-1))] = best[i-1][n-(1<<(i-1))+1]
            // b then covers from [i-1] to [n-(1<<(i-1))+1+(1<<(i-1))-1] = [n].
        {
            a=best[i-1][j];
            b=best[i-1][j+(1<<(i-1))];
            if(RMQ[a]<RMQ[b]) best[i][j]=a;
            else best[i][j]=b;
        }
    return;
}
int askRMQ(int a,int b)
{
    // Return the index of smallest element in [a, b].
    int t;
    t=mm[b-a+1];b-=(1<<t)-1;
    a=best[t][a];b=best[t][b];
    return RMQ[a]<RMQ[b]?a:b;
}

// ============= A better version =============
namespace RMQ {
    
    // How to select between two numbers.
    int choose(int a, int b){
        return max(a, b);
    }
    
    // Preprocess.
    void makeTable(const vector<int> &array, vector<vector<int>> &table){
        
        // Locate space;
        int logSize = int(log(array.size()) / log(2.0));
        for (int i = 0; i < array.size(); ++i) {
            table.push_back(vector<int>(logSize, 0));
        }
        
        // Initialize.
        for (int i = 0; i < array.size(); ++i) {
            table[i][0] = array[i];
        }
        
        for (int j = 1; (1 << j) <= array.size(); ++j) {
            for (int i = 0; i + (1 << j) - 1 < array.size(); ++i) {
                table[i][j] = choose(table[i][j - 1], table[i + (1<<(j-1))][j - 1]);
            }
        }
    }
    
    // Return the max/min element in the range [a, b]
    int RMQ(int a, int b, const vector<vector<int>> &table){
        int k = int(log(double(b - a + 1))/log(2.0));
        return choose(table[a][k], table[b - (1<<k) + 1][k]);
    }
}

// ============= An even simpler version =============

vector<vector<int>> makeTable(const vector<int> &array){
    int arraySize = (int)array.size();
    int logSize = log(arraySize) / log(2);
    vector<vector<int>> table(arraySize, vector<int>(logSize, 0));
    
    for (int i = 0; i < arraySize; ++i)
        table[i][0] = array[i];
    
    for (int j = 1; (1 << j) - 1 < arraySize; ++j)
        for (int i = 0; i + (1 << j) - 1 < arraySize; ++i)
            table[i][j] = std::max(table[i][j - 1],
                                   table[i + (1 << (j - 1))][j - 1]);
    
    return table;
}

int RMQ(int a, int b, const vector<vector<int>> &table){
    int k = log(b - a + 1) / log(2);
    return std::max(table[a][k], table[b - (1 << k) + 1][k]);
}

int main(){
    vector<int> array{-5, -19, -2818, 3, 1, 0, 0, -1, -19, 91};
    printIntVector(array);
    auto table = makeTable(array);
    cout << RMQ(0, 8, table);
    return 0;
}
