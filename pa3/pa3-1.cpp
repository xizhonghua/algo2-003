#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int c, n;
    vector<int> w;
    vector<int> v;

    cin>>c>>n;

    int *f = new int[c+1];
    long long *t = new long long[c+1];

    for(int i=0;i<c+1;i++)
        f[i] = t[i] = 0;

    

    for(int i=0;i<n;i++)
    {
        int weight, value;
        cin>>value>>weight;
        w.push_back(weight);
        v.push_back(value);
    }

    f[0] = 1;

    for(int j=0;j<n;j++)
    {
        int weight = w[j];
        int value = v[j];
        for(int i=c - weight;i>=0;i--)
        {
            if (f[i] && t[i+weight] < t[i] + value)
            {
                f[i+weight] = 1;
                t[i+weight] = t[i] + value;
            }
        }
    }

    long long max_value = 0;
    for(int i=c;i>=0;i--)
        max_value = std::max(max_value, t[i]);
    
    cout<<max_value<<endl;

    return 0;
}