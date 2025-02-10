#include<bits/stdc++.h>
using namespace std;

class Graph
{
    public:

  int n;
  vector<vector<int>>adj;
  vector<int>indegree;
  vector<int>ans;

  Graph(int v)
  {
    n=v;
    adj.resize(n+1);
    indegree.resize(n+1,0);
  }

  void addEdge(int u,int v)
  {
    adj[u].push_back(v);
  }

  void toposort()
  {
  queue<int>q;

  for(int i=1;i<=n;i++)
  {
    for(auto it:adj[i])
    {
        indegree[it]++;
    }
  }

  for(int i=1;i<=n;i++)
  {
    if(indegree[i]==0)
    q.push(i);
  }

  while(!q.empty())
  {
    int x=q.front();
    ans.push_back(x);
    q.pop();

    for(auto it:adj[x])
    {
        indegree[it]--;
        if(indegree[it]==0)
          q.push(it);
    }
  }

}

  
};

int main()
{
   int n,edge;   cin>>n>>edge;

   Graph g(n);

   for(int i=0;i<edge;i++)
   {
    int u,v;    cin>>u>>v;
    g.addEdge(u,v);
   }

   g.toposort();

   if(g.ans.size()==n)
   {
    for(auto it:g.ans)
    {
      cout<<it<<" ";
    }
   }

   else cout<<"ilogical"<<endl;
} 