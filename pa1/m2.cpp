#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class job
{
public:
    job(){}
    job(int w, int l):w(w), l(l) {}
    int w;
    int l;
    double key() const { return (double)w/l; }
    bool operator < (const job& j) const
    {
        return this->key() > j.key();
    }
};

int main()
{
    vector<job> jobs;
    int n;
    
    cin>>n;
    for(int i=0;i<n;i++)
    {
        job j;
        cin>>j.w>>j.l;
        jobs.push_back(j);
    }
    
    std::sort(jobs.begin(), jobs.end());
    
    long long c=0;
    long long s=0;
    
    for(int i=0;i<n;i++)
    {
        const job& j = jobs[i];
        
        c += j.l;
        s += j.w*c;
    }
    
    cout<<s<<endl;
}