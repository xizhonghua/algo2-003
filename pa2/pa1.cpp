#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

const int MAXN = 500;

int g[MAXN+1][MAXN+1];
int parent[MAXN+1];
int pop[MAXN+1];
int n;
int k;

struct Edge
{
    Edge(int n1, int n2, int c):n1(n1), n2(n2), c(c) {}
    int n1, n2, c;
    bool operator < (const Edge& e) const
    {
        return this->c < e.c;
    }
};

vector<Edge> edges;

int find(int x)
{
    if(x == parent[x]) return x;
    return find(parent[x]);
}

// O(N) need a better O(log N) implementation...
void merge(int p1, int p2)
{
    int r1 = find(p1);
    int r2 = find(p2);
    if(r1==r2) return;
    if(pop[r1] <= pop[r2])
    {
        pop[r2] += pop[r1];
        parent[r1] = r2;
    }
    else
    {
        pop[r1] += pop[r2];
        parent[r2] = r1;
    }
    k--;
}

int main()
{
    int n1,n2,c;
    cin>>n;
    k = n; // initially has k clusters
    
    int s = clock();
    
    for(int i=0;i<n;i++)
        for(int j=i+1;j<n;j++)
        {
            cin>>n1>>n2>>c;
            g[n1][n2] = g[n2][n1] = c;
            Edge e(n1,n2,c);
            edges.push_back(e);
            parent[n1] = n1;
            parent[n2] = n2;
            pop[n1] = pop[n2] = 1;
        }
        
    cout<<"read in "<<(clock() - s)/1e6<<endl;
    
    std::sort(edges.begin(), edges.end());
    
    s = clock();
    
    for(const auto& e : edges)
    {
        // already in same group
        int r1 = find(e.n1);
        int r2 = find(e.n2);
        if( r1 == r2) continue;
        merge(r1, r2);
        if(k==4) break;
    }
    
    cout<<"clusting in "<<(clock() - s)/1e6<<endl;
    
    int max_spacing = 1e9;
    
    for(int i=1;i<=n;++i)
        for(int j=i+1;j<=n;j++)
            if(find(i)!=find(j))
                max_spacing = min(max_spacing, g[i][j]);
    
    cout<<max_spacing<<endl;
}