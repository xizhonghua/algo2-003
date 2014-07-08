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
    int key() const { return l-w; }
    bool operator < (const job& j) const
    {
        if(this->key() == j.key())
            return this->w > j.w;
        
        return this->key() < j.key();
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