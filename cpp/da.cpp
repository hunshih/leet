#define maxn 1000001
int wa[maxn],wb[maxn],wv[maxn],cnt[maxn];
int cmp(int *r,int a,int b,int l)
{return r[a]==r[b]&&r[a+l]==r[b+l];}
void da(int *r,int *sa,int n,int m)
{
    int i,j,p,*x=wa,*y=wb,*t;
    for(i=0;i<m;i++) cnt[i]=0;
    for(i=0;i<n;i++) cnt[x[i]=r[i]]++;
    for(i=1;i<m;i++) cnt[i]+=cnt[i-1];
    for(i=n-1;i>=0;i--) sa[--cnt[x[i]]]=i;
    for(j=1,p=1;p<n;j*=2,m=p)
    {
        for(p=0,i=n-j;i<n;i++) y[p++]=i;
        for(i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j;
        for(i=0;i<n;i++) wv[i]=x[y[i]];
        for(i=0;i<m;i++) cnt[i]=0;
        for(i=0;i<n;i++) cnt[wv[i]]++;
        for(i=1;i<m;i++) cnt[i]+=cnt[i-1];
        for(i=n-1;i>=0;i--) sa[--cnt[wv[i]]]=y[i];
        for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++)
            x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
    }
    return;
}
int rank[maxn],height[maxn];
void calheight(int *r,int *sa,int n)
{
    int i,j,k=0;
    for(i=1;i<=n;i++) rank[sa[i]]=i;
    for(i=0;i<n;height[rank[i++]]=k)
        for(k?k--:0,j=sa[rank[i]-1];r[i+k]==r[j+k];k++);
    return;
}
int RMQ[maxn];
int mm[maxn];
int best[20][maxn];
void initRMQ(int n)
{
    int i,j,a,b;
    for(mm[0]=-1,i=1;i<=n;i++)
        mm[i]=((i&(i-1))==0)?mm[i-1]+1:mm[i-1];
    for(i=1;i<=n;i++) best[0][i]=i;
    for(i=1;i<=mm[n];i++)
        for(j=1;j<=n+1-(1<<i);j++)
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
    int t;
    t=mm[b-a+1];b-=(1<<t)-1;
    a=best[t][a];b=best[t][b];
    return RMQ[a]<RMQ[b]?a:b;
}
int lcp(int a,int b)
{
    int t;
    a=rank[a];b=rank[b];
    if(a>b) {t=a;a=b;b=t;}
    return(height[askRMQ(a+1,b)]);
}

// ==================== Implementation in Stanford Notebook ====================

// SuffixArray implementation from Stanford ACM notebook.
// Complexity: O(nlog(n)^2)
namespace SuffixArray_HA_Implementation2 {
    const int maxn = 65536;
    const int maxlg = 17;
    
    struct Entry {
        int nr[2], p;
    }compArray[maxn];
    
    int cmp(const Entry& a, const Entry& b){
        if (a.nr[0] == b.nr[0])
            return a.nr[1] < b.nr[1];
        return a.nr[0] < b.nr[0];
    }
    
    int daArray[maxlg][maxn];
    int sa[maxn];
    
    void getSA(char str[]){
        int n = (int)strlen(str);
        
        // First populate the first layer of daArray. (Since we don't need any
        // comparison right now.
        for (int i = 0; i < n; ++i) {
            daArray[0][i] = str[i] - 'a';
        }
        
        // Now start to sort the array. In each iteration, we need to populate
        // compArray and do the sorting. Where do we get the data to populate?
        // from last level of daArray. Also, stp starts at 1, and increment each
        // iteration, but cnt starts at 1 and increment to twice as big each
        // iteration. The loop stops when cnt is exceeding the size of the array.
        int stp = 1, cnt = 1;
        for (; cnt <= n ; stp++, cnt <<= 1) {
            for (int i = 0; i < n; ++i) {
                compArray[i].nr[0] = daArray[stp - 1][i];
                compArray[i].nr[1] = i+cnt<n ? daArray[stp - 1][i + cnt] : -1;
                compArray[i].p = i;
            }
            sort(compArray, compArray + n, cmp);
            
            // After sorting, we have to put the information back to daArray, at
            // current level.
            for (int i = 0; i < n; ++i)
            {
                if (i > 0 && compArray[i].nr[0] == compArray[i-1].nr[0] &&
                    compArray[i].nr[1] == compArray[i-1].nr[1])
                {
                    daArray[stp][compArray[i].p] = daArray[stp][compArray[i - 1].p];
                }
                else
                    daArray[stp][compArray[i].p] = i;
            }
        }
        stp--;
        for (int i = 0; i < n; ++i) {
            sa[daArray[stp][i]] = i;
        }
    }
    
}

// ==================== Better implementation 09.02.2013 ====================

vector<int> getSA(const string &str){
    int n = (int)str.size();
    vector<vector<int>> daArray(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        daArray[0][i] = str[i] - 'a';
    }
    int stp = 1, cnt = 1;
    vector<CompStruct> compArray(n);
    for (; cnt < n; ++stp, cnt <<= 1) {
        for (int i = 0; i < n; ++i) {
            compArray[i].nr[0] = daArray[stp - 1][i];
            compArray[i].nr[1] = i + cnt < n ? daArray[stp - 1][i + cnt] : -1;
            compArray[i].position = i;
        }
        sort(compArray.begin(), compArray.end(), comp);
        for (int i = 0; i < n; ++i) {
            if (i > 0 && compArray[i].nr[0] == compArray[i - 1].nr[0]
                && compArray[i].nr[1] == compArray[i - 1].nr[1])
                daArray[stp][compArray[i].position] = daArray[stp][compArray[i - 1].position];
            else
                daArray[stp][compArray[i].position] = i;
        }
    }
    --stp;
    vector<int> sa(n);
    for (int i = 0; i < n; ++i) {
        sa[daArray[stp][i]] = i;
    }
    return sa;
}

vector<int> calcHeight(const string &str, const vector<int> &sa){
    int n = (int)sa.size();
    
    vector<int> rank(n);
    vector<int> height(n);
    for (int i = 0; i < n; ++i)
        rank[sa[i]] = i;
    
    for (int i = 0, k = 0; i < n; ++i) {
        k ? k-- : 0;
        int j = sa[rank[i] - 1];
        while (str[i + k] == str[j + k]) ++k;
        height[rank[i]] = k;
    }
    return height;
}
