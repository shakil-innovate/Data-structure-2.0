#include<bits/stdc++.h>
using namespace std;

class segment
{
    public:

  vector<int>tree,seg,lazy;
  int n;

  segment(int v)
  {
    n=v;
    tree.resize(n);
    seg.resize(4*n,0);
    lazy.resize(4*n,0);
  }

  void build(int low,int high,int pos)
  {
    if(low==high)
      seg[pos]=tree[low];
    else{
        int mid=(low+high)>>1;
        build(low,mid,pos*2+1);
        build(mid+1,high,pos*2+2);

        seg[pos]=min(seg[pos*2+1],seg[pos*2+2]);
    }
  }

  void propagate(int low,int high,int pos)
  {
    if(lazy[pos]!=0)
    {
        seg[pos]+=lazy[pos];

        if(low!=high)
        {
            lazy[2*pos+1]+=lazy[pos];
            lazy[2*pos+2]+=lazy[pos];
        }
        lazy[pos]=0;
    }
  }

  void update(int qlow,int qhigh,int low,int high,int pos,int val)
  {
    propagate(low,high,pos);

    if(qlow>high || qhigh<low)
       return ;

    if(qlow<=low && qhigh>=high)
    {
        seg[pos]+=val;
        if(low!=high)
        {
            lazy[pos*2+1]+=val;
            lazy[pos*2+2]+=val;
        }

        return;
    }
    
    int mid=(low+high)>>1;

    update(qlow,qhigh,low,mid,pos*2+1,val);
    update(qlow,qhigh,mid+1,high,pos*2+2,val);

    seg[pos]=min(seg[pos*2+1],seg[pos*2+2]);
  }

  int rangeQuery(int qlow,int qhigh,int low,int high,int pos)
  {
    propagate(low,high,pos);

    if(qlow>high || qhigh<low)
      return INT_MAX;

    else if(qlow<=low && qhigh>=high)
    {
        return seg[pos];
    }
    else
    {
        int mid=(low+high)>>1;
        return min(rangeQuery(qlow,qhigh,low,mid,pos*2+1),rangeQuery(qlow,qhigh,mid+1,high,pos*2+2));
    }
  }
};

int main()
{
  int n,q;    cin>>n>>q;

  segment g(n);

  for(int i=0;i<n;i++)
  {
    cin>>g.tree[i];
  }

  g.build(0,n-1,0);

  for(int i=0;i<q;i++)
  {
    string command; cin>>command;

    if(command=="sum")
    {
        int l,r;    cin>>l>>r;
        cout<<g.rangeQuery(l,r,0,n-1,0)<<endl;
    }
    else if(command=="up")
    {
        int l,r,val;    cin>>l>>r>>val;
        g.update(l,r,0,n-1,0,val);
    }
  }
}