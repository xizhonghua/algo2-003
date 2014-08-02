#include <iostream>
#include <cmath>
using namespace std;

const int MAXN = 25;

int n;
int v[MAXN+1];
double min_len = 1e99;

class Point
{
public:
    Point():x(0),y(0) {}
    Point(const Point& p): x(p.x), y(p.y) {}
    double dist(const Point& p)
    {
        return sqrt((x - p.x)*(x - p.x) + (y - p.y) * (y - p.y));
    }
    double x;
    double y;

    
};

Point pt[MAXN+1];


void dfs(int d, int start, int last, double len)
{
    if(d == n)
    {
        len += pt[last].dist(pt[start]);
        if (len < min_len) {
            min_len = len;
            cout<<"min_len = "<<min_len<<endl;
        }
        return;
    }
    for(int i=0;i<n;i++)
    {
        if(v[i]) continue;

        double dist = pt[last].dist(pt[i]);

        if(dist + len > min_len) continue;

        v[i] = 1;
        dfs(d+1, start, i, len + dist);
        v[i] = 0;
    }
}

int main()
{
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>pt[i].x>>pt[i].y;
    for(int i=0;i<n;i++)
    {
        cout<<"start point = "<<(i+1)<<endl;
        v[i] = 1;
        dfs(1, i, i, 0);
        v[i] = 0;
    }
    return 0;
}