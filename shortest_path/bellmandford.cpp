//for directed

#include<bits/stdc++.h>
using namespace std;

class Graph
{
  public:
   
  int v;
  vector<vector<int>>edge;
  vector<int>dist;
  vector<int>path;
  bool flag=true;

  Graph(int n)
  {
    v=n;
    dist.resize(n+1,INT_MAX);
    path.resize(n+1,-1);
  }

  void addEdge(int u,int v,int w)
  {
    edge.push_back({u,v,w});
  }

  void bellman(int src)
  {
    dist[src]=0;

    for(int i=0;i<v-1;i++)
    {
        for(auto child:edge)
        {
            int u=child[0];
            int v=child[1];
            int w=child[2];

            if(dist[u]!=INT_MAX && dist[v]>(dist[u]+w))
            {
                dist[v]=dist[u]+w;    
                path[v]=u;        
            }
        }
    }

    for(auto child:edge)
    {
        int u=child[0];
        int v=child[1];
        int w=child[2];

        if(dist[u]!=INT_MAX && dist[v]>(w+dist[v]))
        {
            flag=false;
            break;
        }
    }
  }
};

int main()
{
   int node,edg;    cin>>node>>edg;

   Graph g(node);

   for(int i=0;i<edg;i++)
   {
    int u,v,w;  cin>>u>>v>>w;
    g.addEdge(u,v,w);
   }

   g.bellman(1);

   if(g.flag==false){cout<<"not possible"<<endl;return 0;}

   for(int i=1;i<=node;i++)
   {
    cout<<g.dist[i]<<" ";
   }
}