#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <cstdlib>
#include <ctime>
using namespace std;

vector<int> states;
int n, v, v1, v2, max_s = 0;
map<int, int> ids;


class constraint
{
public:
    constraint(int id1, int id2, bool not1, bool not2): id1(id1), id2(id2), not1(not1), not2(not2) {} 

    int id1;
    int id2;

    bool not1;
    bool not2;

    bool ok() const
    {
        int s1 = states[id1];
        int s2 = states[id2];

        bool b1 = not1 ? !s1 : s1;
        bool b2 = not2 ? !s2 : s2;

        return b1 || b2;
    }
};

vector<constraint> cs;

void read_problem()
{
    cin>>n;
    v = 0;
    for(int i=0;i<n;i++)
    {
        cin>>v1>>v2;

        int a1 = abs(v1);
        int a2 = abs(v2);

        if(!ids.count(a1)) ids[a1] = v++; 
        if(!ids.count(a2)) ids[a2] = v++; 

        constraint c(ids[a1], ids[a2], v1<0, v2<0);

        cs.push_back(c);
    }

    cout<<"total constraints = "<<  n <<" total variables = "<<v<<endl;
}

void rand_init()
{
    states = vector<int>(v);
    for(int i=0;i<v;i++)
    {
        states[i] = 1;
    }
}

int statisfied()
{
    int s = 0;
    for(const auto& c : cs)
    {
        if (c.ok()) s++;
    }

    if(s > max_s)
    {
        max_s = s;
        cout<<" max_s = "<<max_s<<endl;
    }

    return s;
}

void dfs(vector<int>& s, set<int>& used, int step)
{
    // select a var
    if(step == 0)
    {
        for(int i=0;i<v;i++)
        {
            if(used.count(i)) continue;

            used.insert(i);

            s.push_back(i);
            dfs(s, used, 1);
            s.pop_back();

            used.erase(i);
        }
    }
    // flip the variable
    else
    {
        int cur_s = statisfied();

        int id = s.back();
        states[id] = 1 - states[id];

        int new_s = statisfied();

        if (new_s > cur_s)
        {
            dfs(s, used, 0);
        }
        states[id] = 1 - states[id];
    }
}



int main() {
    srand(time(NULL));
    read_problem();
    rand_init();
    vector<int> s;
    set<int> used;
    dfs(s, used, 0);
    cout<<max_s<<endl;
}