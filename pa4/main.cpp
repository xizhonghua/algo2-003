#include <iostream>
#include <cstring>
#include <limits>
using namespace std;

const int MAXN = 1002;

int g[MAXN][MAXN];
long long w[MAXN][MAXN];

int main()
{
    int n, m;
    cin>>n>>m;

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            w[i][j] = (i==j ? 0 : INT_MAX);

    for(int i=0;i<m;i++)
    {
        long long u,v,weight;
        cin>>u>>v>>weight;
        u--; v--;
        g[u][v] = 1;
        w[u][v] = weight;
    }

    long long s = INT_MAX;

    for(int k=0;k<n;k++)
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
            {
                w[i][j] = min(w[i][j], w[i][k] + w[k][j]);
                s = min(w[i][j], s);
            }

    if(s < INT_MIN*n)
        cout<<"negative cycle"<<endl;            
    else
        cout<<s<<endl;
}