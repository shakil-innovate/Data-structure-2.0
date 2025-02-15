//problem_link:https://cses.fi/problemset/task/1671/

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

class graph
{
    public:
     ll n,m;
     vector<vector<pair<ll,ll>>>edge;
     vector<ll>dist,path;

     graph(ll v)
     {
        n=v;
        edge.resize(n+1);
        dist.resize(n+1,LLONG_MAX);
        path.resize(n+1,-1);
     }


     void addEdge(ll u,ll v,ll w)
     {
        edge[u].push_back({v,w});
     }

     void shortest_path(ll src)
     {
       priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<pair<ll,ll>>>pq;
       dist[src]=0;
       pq.push({0,src});

       while(!pq.empty())
       {
         ll node=pq.top().second;
         ll current_dist=pq.top().first;
         pq.pop();

         if (current_dist > dist[node]) {
            continue;
        }

         for(auto it:edge[node])
         {
            ll nextNode=it.first;
            ll w=it.second;

            if(dist[node]!=LLONG_MAX && dist[nextNode]>(dist[node]+w))
            {
                dist[nextNode]=w+dist[node];
                pq.push({dist[nextNode],nextNode});
                path[nextNode]=node;
            }
         }
       }
     }

};


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ll n,m;    cin>>n>>m;
    graph g(n);

    for(ll i=0;i<m;i++)
    {
        ll u,v,w;  cin>>u>>v>>w;
        g.addEdge(u,v,w);
    }

    g.shortest_path(1);
    for(ll i=1;i<=n;i++)
    {
        cout<<g.dist[i]<<" ";
    }
    cout<<endl;

}