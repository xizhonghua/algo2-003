/*
Question 2
In this question your task is again to run the clustering algorithm from lecture, but on a MUCH bigger graph. So big, in fact, that the distances (i.e., edge costs) are only defined implicitly, rather than being provided as an explicit list.
The data set is here. The format is:
[# of nodes] [# of bits for each node's label]
[first bit of node 1] ... [last bit of node 1]
[first bit of node 2] ... [last bit of node 2]
...
For example, the third line of the file "0 1 1 0 0 1 1 0 0 1 0 1 1 1 1 1 1 0 1 0 1 1 0 1" denotes the 24 bits associated with node #2.

The distance between two nodes u and v in this problem is defined as the Hamming distance--- the number of differing bits --- between the two nodes' labels. For example, the Hamming distance between the 24-bit label of node #2 above and the label "0 1 0 0 0 1 0 0 0 1 0 1 1 1 1 1 1 0 1 0 0 1 0 1" is 3 (since they differ in the 3rd, 7th, and 21st bits).

The question is: what is the largest value of k such that there is a k-clustering with spacing at least 3? That is, how many clusters are needed to ensure that no pair of nodes with all but 2 bits in common get split into different clusters?

NOTE: The graph implicitly defined by the data file is so big that you probably can't write it out explicitly, let alone sort the edges by cost. So you will have to be a little creative to complete this part of the question. For example, is there some way you can identify the smallest distances without explicitly looking at every pair of nodes?
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <unordered_map>
using namespace std;

const int MAXN = 200000;

unordered_map<int, int> f;

int nodes;
int v[MAXN+1];
int parent[MAXN+1];
int pop[MAXN+1];
int n;
int k;
int b;

int find(int x)
{
    if(x == parent[x]) return x;
    return find(parent[x]);
}

void Union(int p1, int p2)
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

int flip(int n, int bit)
{
    if (n & (1<<bit))
    {
        n -= (1<<bit);
    }
    else
    {
        n += (1<<bit);
    }
    return n;
}

int main()
{
    int n1,n2,c;
    cin>>n>>b;
    
    int s = clock();
    
    for(int i=0;i<n;i++)
    {
        int value = 0;
        for(int j=0;j<b;j++)
        {
            int bit;
            cin>>bit;
            value = (value << 1) | bit;
        }
    
        // remove duplicated nodes    
        if(f.count(value)) continue;
        
        v[nodes] = value;
        parent[nodes] = nodes;
        f[value] = nodes;
        pop[nodes] = 1;
        
        nodes++;
    }
        
    cout<<"read in "<<(clock() - s)/1e6<<endl;
    
    s = clock();
    
    n = nodes; // update unique nodes number
    
    k = n; // initially has k clusters  
    
    cout<<"init k = "<<k<<endl;
    
    // clustering with dist = 1
    for(int i=0;i<n;i++)
    {   
        for(int j=0;j<b;j++)
        {
            int tmp = flip(v[i], j);
            if (!f.count(tmp)) continue;
            int id = f.at(tmp);
            Union(i, id);
        }
    }
    
    // clustering with dist = 2
    for(int i=0;i<n;i++)
    {   
        for(int j=0;j<b;j++)
        {
            for(int k=j+1;k<b;k++)
            {
                int tmp = flip(flip(v[i],j), k);
                if (!f.count(tmp)) continue;
                int id = f.at(tmp);
                Union(i, id);
            }
        }
    }
    
    cout<<"clusting in "<<(clock() - s)/1e6<<endl;
    
    cout<<"k = "<<k<<endl;
}