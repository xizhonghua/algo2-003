#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 500;
class Edge
{
public:
    int n1, n2;
    int cost;
};

int v[MAXN+1];

int main()
{
    int N,E;
    cin>>N>>E;
    
    vector<Edge> es;
    
    for(int i=0;i<E;i++)
    {
        Edge e;
        cin>>e.n1>>e.n2>>e.cost;
        es.push_back(e);
    }
    
    v[1] = 1;
    long long tot_cost = 0;
    for(int i=1;i<=N-1;i++)
    {
        Edge best;
        best.cost = 1e8;
        for(int j=0;j<es.size();j++)
        {
            const Edge& e = es[j];
            if((v[e.n1] && v[e.n2]) || (!v[e.n1] && !v[e.n2]) || e.cost > best.cost) continue;
            best = e;
        }
        
        tot_cost += best.cost;
        v[best.n1] = v[best.n2] = 1;
    }
    
    cout<<tot_cost<<endl;
}