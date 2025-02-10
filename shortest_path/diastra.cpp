#include<bits/stdc++.h>
using namespace std;

class Graph
{

  public:

  int v;
  vector<vector<pair<int,int>>>adj;
  vector<int>dist;
  vector<int>path;

  Graph(int n)
  {
    v=n;
    adj.resize(n+1);
    dist.resize(n+1,INT_MAX);
    path.resize(n+1,-1);
  }

  void addEdge(int u,int v,int w)
  {
    adj[u].push_back({v,w});
    adj[v].push_back({u,w});
  }

  void shortest_distance(int src)
  {
    dist[src]=0;

    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;

    pq.push({0,src});

    while(!pq.empty())
    {
      int node=pq.top().second;

      pq.pop();
       
      for(auto child:adj[node])
      {
        int weight=child.second;
        int nextNode=child.first;

        if(dist[nextNode]>(weight+dist[node]))
        {
          dist[nextNode]=weight+dist[node];
          pq.push({dist[nextNode],nextNode});
          path[nextNode]=node;
        }
      }
    }
  }
};

int main()
{
    int node,edge;  cin>>node>>edge;

    Graph g(node);

    for(int i=0;i<edge;i++)
    {
     int u,v,w; cin>>u>>v>>w;

     g.addEdge(u,v,w);
    }

    g.shortest_distance(1);

    for(int i=1;i<=node;i++)
    {
      cout<<g.dist[i]<<" ";
    }
}